# SilentPico

<img src="SilentPico.png" alt="SilentPico" width="400">

SilentPico offers a simple and innovative solution to automate the process of maintaining silence on the context of traditional libraries. The system not only helps users themselves notice when they are being noisy, but also keeps librarians informed about the noise level at each desk, ensuring a quieter and more organized environment for everyone.

## Features

1. Noise detection
2. Digital-to-dB conversion
3. Noise notification using LEDs
4. Wi-Fi and MQTT connectivity
5. Display of dB values and connection status on the OLED screen
6. Auto Wi-Fi and MQTT reconnection
7. Local mode if Wi-Fi connection fails

## Requirements

* Raspberry Pi Pico W
* Analog Microphone connected on GPIO 28 port (if you are not using Pico W with BITDOGLAB board)
* Green and Red led connected on GPIO 11 and 13 (if you are not using Pico W with BITDOGLAB board)
* Oled Display (Optional) connected on GPIO 14 (SDA) 15 (SCL) (if you are not using Pico W with BITDOGLAB board)
* Cmake
* VS Code

## Installation

Currently, SilentPico does not yet have the functionality to edit the wifi SSID/PASSWORD, MQTT topic/Broker IP Addres and dB threshold, you will need to install a IDE to edit the code and compile, follow these steps:

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
name: PICO_SDK_PATH

value: C:\Program Files\Raspberry Pi\Pico SDK v1.5.1

name: PICO_TOOLCHAIN_PATH

value: C:\Program Files\Raspberry Pi\Pico SDK v1.5.1\pico-sdk\toolchain
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

1. Minimize external noise interference

2. Place SilentPico at the center of the table

3. Ensure tables are spaced adequately (2 meters recommended)

4. Connect SilentPico to Wi-Fi or wait 1 minute for Local Mode

5. SilentPico will notify users and librarians if noise exceeds the threshold

**Note:** SilentPico performs best in quiet environments. For other contexts, ensure proper noise control.

## TODO

The project is still under development, some upgrades are planned to be out very soon:

- [ ] Release .uf2 file
- [ ] DNS Resolve
- [ ] Better way to edit Wi-Fi SSID and PASSWORD
- [ ] Option to alternate Local and MQTT running mode
- [x] Wi-Fi and MQTT: auto reconnection
- [x] auto Local Running mode after 1 minute of attempts to reconnect

## Autors

* **jadielucas** (Jadiel Lucas) - *Microphone reading, Wi-Fi and MQTT connection programming*
* **argus86** (Alex Neto) - *Microphone reading, I2C reading and OLED Display programming*
* **WessTinho** (Pedro Lucas) - *LED programming and documentation*

## License

This project is licensed under the MIT License - see [LICENSE.md](https://github.com/jadielucas/IP_Project/blob/main/LICENSE) for more details.
