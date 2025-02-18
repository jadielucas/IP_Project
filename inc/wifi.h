#ifndef WIFI_H
#define WIFI_H

#include <stdio.h>
#include "pico/cyw43_arch.h"
#include "libs/lwipopts.h"
#include "libs/ssd1306.h"
#include "inc/display.h"

#define WIFI_SSID "Galaxy"
#define WIFI_PASSWORD "12345678"

extern uint8_t reconnection_attempts;

int wifi_init();
bool is_wifi_connected();
void check_wifi_connection();

#endif