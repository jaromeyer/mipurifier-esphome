## ESPHome for various Xiaomi Air Purification Devices

<p align="center"><img src="https://user-images.githubusercontent.com/36965186/219659691-6d8e733f-ae2f-4480-80ee-f5e90c9bd8f8.jpeg" width="400"></p>

There are two separate microcontrollers inside the device: one STM32F4 which actually controls the device, and one ESP32 which only acts as a gateway to the internet/local network. This config replaces the firmware running on the ESP32 and implements the proprietary serial protocol used to communicate with the STM32.

### Features:
- turning the purifier on/off
- exposing PM2.5, humidity, temperature, and remaining filter life as sensor values
- switching modes
- controlling speed in manual mode
- changing various settings (display brightness, beeper, lock)
- sending custom commands using the `esphome.mipurifier_send_command` service (e.g. sending `down set_properties 5 1 false` disables beeping)

### FAQ
#### Does this remove the `Filter remaining 0%` warning?
Flashing this firmware does NOT change anything about how the remaining filter life is read/managed. However you can easily reset your filter to continue using it by following [this video](https://www.youtube.com/watch?v=usiX_J9Yy2o) for example.

#### Is my air purifier supported?
The following devices are known to work with this library (this list is not exhaustive)
- Air Purifier 3 (2019) (zhimi.airpurifier.ma4)
- Air Purifier 3H (2019) (zhimi.airpurifier.mb3)

Please don't hesitate to expand this list by opening a pull request if your device also works with this library! Make sure to backup the original firmware on your device's ESP32 before flashing ESPHome.

### Flashing
Connect any USB-to-serial adapter and power on the ESP32 while `GPIO0` and `GPIO2` are pulled low.

The following steps have been tested with the AC-M6-B01 Board (REV3-BDR) by using the ESPHome Add-on within Home Assistant:
- Prepare an usb-to-serial adapter (a CP2102 chip has been used here) by installing the required drivers on the computer you will flash the board
- Pull GPIO0 low by bridging soldering spot 1 (GPIO0) and 2 (GND) 
  - No need to solder here if you have a wire that fits more or less tight into the soldering spot
- Pull GPIO2 low by soldering Pin 24 (GPIO2) and 15 (GND) together with a thin wire
- Open Home Assistant on any client machine via Web Browser using https
  - A Windows 10 client was used here while Home Assistant was running on a different machine
  - Your browser must support WebSerial to flash from a different client than the ESPHome Server. Chrome do support WebSerial.
- Open the ESPHome Web Interface 
  - If not done before, enter your Wi-Fi settings in secrets.yaml
- Select "NEW DEVICE" 
- Name your device, e.g. with "Air Purifier Livingroom"
- Select the device type, ESP32 in this case
- Do not install the device in the next step, instead, press Skip
- Use "EDIT" on the device tile to overwrite the device settings with the content of mipurifier.yaml
- Copy the mipurifier.h file into the same directory where the <your-device>.yaml (Air-Purifier-Livingroom.yaml if you have named the device as written above) file is located
  - Default path is /Config/esphome/. 
- Connect the usb-to-serial adapter with the board as shown on the image
- Plug in the usb-to-serial adapter on the client machine
  - The board will beep two times on powering up
- Use "Install" on the device tile within the 3 dots and select "Plug into this computer" and follow the further instructions
- After the install process has been finished, detach the usb-to-serial adapter from the client
- Remove the bridges both for GPIO0 and GPIO1
- Reassemble your Purifier
- Power on the device
- Wait for the device to connect to your WiFi
- Test the device by using the control panel in Home Assistant


Typical problems:
- ESPHome is unable to find the usb-to-serial adapter
  - Make sure that you have installed the latest drivers for the adapter matching your client OS
- ESPHome is unable to connect to the AC-M6-B01 board
  - Check all connections between the adapter and the board
  - Exchange RX and TX if the problem remains
- Compiling/Installing takes a very long time
  - Compiling on an Raspi 4 might take more than 10 minutes
  - If this step takes more time, you can try to restart the ESPHome AddOn and restart the install process
- The device will not join your WiFi
  - Make sure that your router allows new unknown devices to join
  - Power off the device and power on the device again

<image src="https://user-images.githubusercontent.com/36965186/218741519-1f2bf1ba-cb44-488f-9ee8-803aed071dc3.jpeg" width=500>
