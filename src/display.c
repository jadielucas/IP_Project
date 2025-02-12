#include "inc/display.h"

ssd1306_t disp;
char buffer[20];

// Function to setup I2C and SSD1306
void setup_display()
{
    i2c_init(i2c1, 400000);
    gpio_set_function(14, GPIO_FUNC_I2C);
    gpio_set_function(15, GPIO_FUNC_I2C);
    gpio_pull_up(14);
    gpio_pull_up(15);
    disp.external_vcc = false;
    ssd1306_init(&disp, 128, 64, 0x3C, i2c1);
    ssd1306_clear(&disp);
    ssd1306_draw_string(&disp, 5, 28, 2, "SilentPico");
    ssd1306_show(&disp);
    ssd1306_clear(&disp);
}

void update_display_db_value(micdata_t *micdata){
    sprintf(buffer, "dB: %.2f", micdata->dB);
    ssd1306_draw_string(&disp, 0, 0, 2, buffer);
    ssd1306_show(&disp);
    ssd1306_clear_area(&disp, 0, 0, 128, 32);
}