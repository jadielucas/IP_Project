# SilentPico

SilentPico offers a simple and innovative solution to automate the process of maintaining silence. The system not only helps users themselves notice when they are being noisy, but also keeps librarians informed about the noise level at each desk, ensuring a quieter and more organized environment for everyone.

## Funcionalities

1. Noise detect
2. Digital to dB conversion
3. Noise notify with LEDs
4. Wi-Fi and MQTT Connection
5. dB value and connection status on OLED Display
6. Auto Reconnect Wi-Fi and MQTT
7. Local running if Wi-Fi is not able to connect

## Requirements

* Raspberry Pi Pico W
* Analog Microphone connected on GPIO 28 port (if you are not using Pico W with BITDOGLAB board)
* Green and Red led connected on GPIO 11 and 13 (if you are not using Pico W with BITDOGLAB board)
* Oled Display (Optional) connected on GPIO 14 (SDA) 15 (SCL) (if you are not using Pico W with BITDOGLAB board)
* Cmake
* VS Code

## Installation

Since SilentPico does not yet have the functionality to edit the wifi SSID/PASSWORD, MQTT topic/Broker IP Addres and dB threshold, you will need to install the IDE to edit the code and compile, follow these steps:

### Windows:

1. Install GCC arm 13.3.Rel1
2. Install Pico SDK 1.5.1
3. Make sure you have it on your environment variables:
   
**On Path:**
```
C:\Program Files (x86)\Arm GNU Toolchain arm-none-eabi\13.3 rel1\bin
C:\Program Files\Raspberry Pi\Pico SDK v1.5.1\pico-sdk\toolchain\13.2 Rel1\bin
```
**On system variables:**
```
**name:** PICO_SDK_PATH

**value:** C:\Program Files\Raspberry Pi\Pico SDK v1.5.1

**name:** PICO_TOOLCHAIN_PATH

**value:** C:\Program Files\Raspberry Pi\Pico SDK v1.5.1\pico-sdk\toolchain
```
5. Install VS code
6. Install these VS code extensions: cmake/cmaketools, C/C++, Raspberry Pi.
7. import SilentPico Project on Raspberry Pi extension choosing Pico SDK Version 1.5.1
8. Change WIFI_SSID and WIFI_PASS on <inc/wifi.h> for your Wi-Fi ssid and password, change IP address and MQTT_TOPIC on <inc/mqtt.h> for your broker ip and topic.
9. Compile Project with Raspberry Pi extension
10. Install RP2040 drivers for Windows using zadig, choose 1 of the 2 interfaces and install a WinUSB driver (if you want see debug logs, install usbCDC on another interface).
11. Connect your Pico W on bootsel mode
12. Run project with Raspberry Pi extension

See that [tutorial](https://www.youtube.com/watch?v=cMtbuvkkF5c&t=194s) for more detailed steps.

## Usage

### Libraries:

1. Make sure you have a good control of extern noises
2. Put SilentPico on the center of your table
3. Make sure the tables are on a great distance of each other (2mt recommended)
4. Connect SilentPico to Wi-Fi or wait 1 minute for Local Running
5. Now, if the users noise be louder than threshold, SilentPico will notify them and librarians about the noise.

**SilentPico runs better on quite places, if you need to apply SilentPico on another context, make sure you had a good noise control.**

## TODO

The project is still under development, some upgrades are planned to be out very soon:

- [ ] DNS Resolve
- [ ] Better way to edit Wi-Fi SSID and PASSWORD
- [ ] Option to alternate Local and MQTT running mode
- [x] Wi-Fi and MQTT: auto reconnection
- [x] auto Local Running mode after 1 minute of attempts to reconnect
