#include "pico/stdlib.h"
#include "inc/led.h"

#define RED_LED 13
#define GREEN_LED 11

// Function to setup GPIO pins
void setup_gpio(){
    gpio_init(RED_LED);
    gpio_init(GREEN_LED);
    gpio_set_dir(RED_LED, GPIO_OUT);
    gpio_set_dir(GREEN_LED, GPIO_OUT);
}