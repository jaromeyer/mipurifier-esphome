## ESPHome configuration & custom component for the Xiaomi Mi Air Purifier 3H (and similar devices using the same protocol)

There are two separate microcontrollers inside the device: one STM32F4 which actually controls the device, and one ESP32 which only acts as a gateway to the internet/local network. This config replaces the firmware running on the ESP32 and implements the proprietary serial protocol used to communicate with the STM32.

### Features:
- turning the purifier on/off
- exposing PM2.5, humidity, temperature, and remaining filter life as sensor values
- switching modes
- controlling speed in manual mode
- sending custom commands using the `esphome.mipurifier_send_command` service

### FAQ
#### Does this remove the `Filter remaining 0%` warning?
Flashing this firware does NOT change anything about how the remaining filter life is read/managed. However you can easily reset your filter to continue using it by following [this video](https://www.youtube.com/watch?v=usiX_J9Yy2o) for example.

### Flashing
Connect any USB-to-serial adapter and power on the ESP32 while `GPIO0` and `GPIO2` are pulled low.
![image](https://user-images.githubusercontent.com/36965186/218741519-1f2bf1ba-cb44-488f-9ee8-803aed071dc3.jpeg)
