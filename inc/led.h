#ifndef LED_H
#define LED_H

#define RED_LED 13
#define GREEN_LED 11

#include "pico/stdlib.h"

extern struct repeating_timer timer;

void setup_leds();
bool update_led_status(struct repeating_timer *t);

#endif