#ifndef LED_H
#define LED_H

#include "pico/stdlib.h"

#define RED_LED 13
#define GREEN_LED 11

extern struct repeating_timer timer;

void setup_leds();
bool update_led_status(struct repeating_timer *t);

#endif