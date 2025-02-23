#ifndef DISPLAY_H
#define DISPLAY_H

#include "libs/ssd1306.h"  // Library for controlling the SSD1306 OLED display
#include "inc/mic.h"       // Header file for microphone data structures

// External declaration of the SSD1306 display instance
extern ssd1306_t disp;

/**
 * @brief Initializes the OLED display.
 *
 * This function sets up the SSD1306 display, configuring the necessary
 * parameters for proper operation.
 */
void setup_display();

/**
 * @brief Updates the OLED display with the microphone's dB value.
 *
 * @param micdata Pointer to a micdata_t structure containing the current
 *                microphone data, including the decibel value to display.
 */
void update_display_db_value(micdata_t *micdata);

#endif