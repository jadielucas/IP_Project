#ifndef DISPLAY_H
#define DISPLAY_H

#include "libs/ssd1306.h"
#include "inc/mic.h"

extern ssd1306_t disp;

void setup_display();
void update_display_db_value(micdata_t *micdata);

#endif