#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/i2c.h"
#include "inc/ssd1306.h"

#define RED_LED 13
#define GREEN_LED 11
#define MIC_PIN 28

ssd1306_t disp;

// Function to setup GPIO pins
void setup_gpio(){
    gpio_init(RED_LED);
    gpio_init(GREEN_LED);
    gpio_set_dir(RED_LED, GPIO_OUT);
    gpio_set_dir(GREEN_LED, GPIO_OUT);
}

// Function to setup ADC
void setup_adc(){
    adc_init();
    adc_gpio_init(MIC_PIN);
    adc_select_input(2);
}

void setup_i2c_ssd1306()
{
    i2c_init(i2c1, 400000);
    gpio_set_function(14, GPIO_FUNC_I2C);
    gpio_set_function(15, GPIO_FUNC_I2C);
    gpio_pull_up(14);
    gpio_pull_up(15);
    disp.external_vcc = false;
    ssd1306_init(&disp, 128, 64, 0x3C, i2c1);
    ssd1306_clear(&disp);
    ssd1306_show(&disp);
}

int main()
{
    stdio_init_all();
    setup_gpio();
    setup_adc();
    setup_i2c_ssd1306();

    char buffer[20];

    while (true) {

        uint16_t samples = adc_read();
        
        
        printf("ADC Value: %d\n", samples);
        sprintf(buffer, "ADC Value: %d", samples);
        ssd1306_draw_string(&disp, 0, 0, 1, buffer);
        ssd1306_show(&disp);
        ssd1306_clear_area(&disp, 0, 0, 128, 32);
        sleep_ms(1000);
    }
}