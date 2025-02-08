#ifndef DISPLAY_H
#define DISPLAY_H

#include "inc/mic.h"

extern ssd1306_t disp;
extern char buffer[20];

void setup_i2c_ssd1306();
void update_display_db_value(micdata_t *micdata);

#endif