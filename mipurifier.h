#include "esphome.h"

class MiPurifierSensor :
  public Component,
  public UARTDevice,
  public FloatOutput {

 private:
  static const int max_line_length = 80;
  bool turn_on = false;
  char recv_buffer[max_line_length];
  char cmd_buffer[max_line_length];
  
  MiPurifierSensor(UARTComponent *parent) : UARTDevice(parent) {}

  int readline(int readch, char *buffer, int len) {
    static int pos = 0;
    int rpos;
    
    if (readch > 0) {
      switch (readch) {
        case '\r': // Return on CR
          rpos = pos;
          pos = 0;  // Reset position index ready for next time
          return rpos;
        default:
          if (pos < len-1) {
            buffer[pos++] = readch;
            buffer[pos] = 0;
          }
      }
    }
    // No end of line has been found, so return -1.
    return -1;
  }

 public:
  Sensor *airquality_sensor = new Sensor();
  Sensor *humidity_sensor = new Sensor();
  Sensor *temperature_sensor = new Sensor();
  
  static MiPurifierSensor* getInstance(UARTComponent *parent) {
    static MiPurifierSensor* instance = new MiPurifierSensor(parent);
    return instance;
  }
  
  void write_state(float state) override {
    if (state == 0.0) {
      strcpy(cmd_buffer, "down set_properties 2 2 false");
    } else {
      int level = (int) (state*14);
      sprintf(cmd_buffer, "down set_properties 10 10 %i", level);
      turn_on = true;
    }
  }
 
  void setup() override {
    // TODO: read initial sensor values
  }
  
  void loop() override {
    while (available()) {
      if(readline(read(), recv_buffer, max_line_length) > 0) {
        char *token = strtok(recv_buffer, " ");
        if (strcmp(token, "net") == 0) {
          write_str("local");
        } else if (strcmp(token, "time") == 0) {
          write_str("1669758543");
        } else if (strcmp(token, "get_down") == 0) {
          if (turn_on) {
            write_str("down set_properties 2 2 true");
            turn_on = false;
          } else if (strlen(cmd_buffer) > 0) {
            ESP_LOGD("custom", cmd_buffer);
            write_str(cmd_buffer);
            cmd_buffer[0] = '\0';
          } else {
            write_str("down none");
          }
        } else if (strcmp(token, "properties_changed") == 0) {
          char *id1 = strtok(NULL, " ");
          char *id2 = strtok(NULL, " ");
          char *id = strcat(id1, id2);
          double val = atof(strtok(NULL, ""));
          if (strcmp(id, "36") == 0) {
            airquality_sensor->publish_state(val);
          } else if (strcmp(id, "37") == 0) {
            humidity_sensor->publish_state(val);
          } else if (strcmp(id, "38") == 0) {
            temperature_sensor->publish_state(val);
          }
          write_str("ok");
        } else {
          write_str("ok");
        }
      }
    }
  }
};