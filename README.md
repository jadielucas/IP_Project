# SilentPico

> Project with Raspberry Pi Pico W, destined to maintance noise on the context of traditional libraries.

### TODO

The project is still under development, some upgrades are planned to be out very soon:

- [ ] DNS Resolve
- [ ] Better way to edit Wi-Fi SSID and PASSWORD
- [ ] Option for alternate Local and MQTT running mode
- [x] Wi-Fi and MQTT: auto reconnection
- [x] auto Local Running mode after 1 minute of attempts to reconnect

## Requisites

- Raspberry Pi Pico W
- Cmake
- VS Code

## Installation

Install SilentPico involves flashing a UF2 (USB Flashing Format) file onto your Raspberry Pi Pico W. Follow these steps:

**Windows:**

1. Install GCC arm
2. Install Pico SDK 1.5.1
3. Install VS code
4. Install these VS code extensions: cmake/cmaketools, C/C++, Raspberry Pi.
5. import SilentPico Project on Raspberry Pi extension
6. Change WIFI_SSID and WIFI_PASS on <wifi.h> for your Wi-Fi ssid and password, change IP address and MQTT_TOPIC on mqtt.h for your broker ip and topic.
7. Compile Project with Raspberry Pi extension
8. Connect your Pico W on bootsel mode
9. Run project with Raspberry Pi extension

## Usage

For usage <SilentPico>, follow these steps:
