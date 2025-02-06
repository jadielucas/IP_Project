#ifndef DISPLAY_H
#define DISPLAY_H

extern ssd1306_t disp;
extern char buffer[20];

void setup_i2c_ssd1306();

#endif