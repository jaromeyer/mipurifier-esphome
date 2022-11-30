## ESPHome configuration & custom component for Xiaomi Mi Air Purifier 3H (and probably similar Mi Purifiers)

There are two separate microcontrollers inside the device: one STM32F4 which actually controls the device, and one ESP32 which only acts as a gateway to the internet/local network. This config replaces the firmware running on the ESP32 and implements the proprietary serial protocol used to communicate with the STM32.

### Currently supported features (more will hopefully follow):
- PM2.5, Humidity, and Temperature sensor
- Controlling speed in manual mode
- Turning the purifier on/off
