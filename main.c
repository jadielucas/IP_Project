#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"

#define RED_LED 13
#define GREEN_LED 11
#define MIC_PIN 28

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

int main()
{
    stdio_init_all();
    setup_gpio();
    setup_adc();

    while (true) {
        uint16_t samples = adc_read();
        printf("ADC Value: %d\n", samples);
        sleep_ms(1000);
    }
}