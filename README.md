## ESPHome configuration & custom component for the Xiaomi Mi Air Purifier 3H (and similar devices using the same protocol)

There are two separate microcontrollers inside the device: one STM32F4 which actually controls the device, and one ESP32 which only acts as a gateway to the internet/local network. This config replaces the firmware running on the ESP32 and implements the proprietary serial protocol used to communicate with the STM32.

### Features:
- turning the purifier on/off using a switch component
- exposing PM2.5, humidity, temperature, remaining filter life, and current mode as sensor values
- switching modes by calling the `esphome.mipurifier_set_mode` service using one of the following values `auto, night, manual, low, medium, high`
- controlling speed in manual mode by calling the `esphome.mipurifier_set_manualspeed` service with a value between 0 and 14
- sending custom commands using the `esphome.mipurifier_send_command` service

### FAQ
#### Does this remove the `Filter remaining 0%` warning?
Flashing this firware does NOT change anything about how the remaining filter life is read/managed. However you can easily reset your filter to continue using it by following [this video](https://www.youtube.com/watch?v=usiX_J9Yy2o) for example.
