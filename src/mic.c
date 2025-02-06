#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "inc/mic.h"

micdata_t micdata;

// Function to setup ADC
void setup_adc(){
    adc_init();
    adc_gpio_init(MIC_PIN);
    adc_select_input(2);
}