#ifndef WIFI_H
#define WIFI_H

#include "pico/cyw43_arch.h"

int wifi_init();
bool is_wifi_connected();
void check_wifi_connection();

#endif