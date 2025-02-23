#ifndef WIFI_H
#define WIFI_H

#include "pico/cyw43_arch.h"  // Library for Wi-Fi functionality on Raspberry Pi Pico W

/**
 * @brief Initializes the Wi-Fi module.
 *
 * This function sets up the Wi-Fi hardware and attempts to connect to the 
 * configured network.
 *
 * @return int Returns 0 on successful initialization, or a negative value on failure.
 */
int wifi_init();

/**
 * @brief Checks the current Wi-Fi connection status.
 *
 * @return true if the device is connected to a Wi-Fi network, false otherwise.
 */
bool is_wifi_connected();

/**
 * @brief Monitors and manages the Wi-Fi connection.
 *
 * This function checks the Wi-Fi connection status and can attempt to reconnect
 * if the connection is lost.
 */
void check_wifi_connection();

#endif
