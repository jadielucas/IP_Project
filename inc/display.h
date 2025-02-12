#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "libs/ssd1306.h"
#include "inc/mic.h"

extern ssd1306_t disp;
extern char buffer[20];

void setup_display();
void update_display_db_value(micdata_t *micdata);

#endif