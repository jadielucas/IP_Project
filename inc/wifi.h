#ifndef WIFI_H
#define WIFI_H

#include "pico/cyw43_arch.h"

#define WIFI_SSID "Galaxy"
#define WIFI_PASSWORD "12345678"

int wifi_init();
bool is_wifi_connected();
void check_wifi_connection();

#endif