#ifndef LED_H
#define LED_H

#include "pico/stdlib.h"  // Standard library for Raspberry Pi Pico

// External declaration of a repeating timer used for LED control
extern struct repeating_timer timer;

/**
 * @brief Initializes the LEDs.
 *
 * This function sets up the GPIO pins and configurations required 
 * to control the LEDs.
 */
void setup_leds();

/**
 * @brief Callback function to update the LED status.
 *
 * This function is triggered by the repeating timer to change the LED state,
 * allowing for effects like blinking or status indication.
 *
 * @param t Pointer to the repeating_timer structure triggering the callback.
 * @return true if the timer should continue running, false to stop.
 */
bool update_led_status(struct repeating_timer *t);

#endif