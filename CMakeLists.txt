# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 1.5.1)
set(toolchainVersion 13_2_Rel1)
set(picotoolVersion 2.0.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(Silent_Pico_IP C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(Silent_Pico_IP main.c libs/ssd1306.c src/led.c
src/mic.c src/display.c src/wifi.c src/mqtt.c)

pico_set_program_name(Silent_Pico_IP "Silent_Pico_IP")
pico_set_program_version(Silent_Pico_IP "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(Silent_Pico_IP 0)
pico_enable_stdio_usb(Silent_Pico_IP 1)

# Add the standard library to the build
target_link_libraries(Silent_Pico_IP
        pico_stdlib)

# Add the standard include files to the build
target_include_directories(Silent_Pico_IP PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

# Add any user requested libraries
target_link_libraries(Silent_Pico_IP 
        hardware_adc
        hardware_i2c
        pico_cyw43_arch_lwip_threadsafe_background
        pico_lwip_mqtt
        )

pico_add_extra_outputs(Silent_Pico_IP)

