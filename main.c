#include <stdio.h>
#include "pico/stdlib.h"

#define RED_LED 13
#define GREEN_LED 11

void setup_gpio(){
    gpio_init(RED_LED);
    gpio_init(GREEN_LED);
    gpio_set_dir(RED_LED, GPIO_OUT);
    gpio_set_dir(GREEN_LED, GPIO_OUT);
}

int main()
{
    stdio_init_all();
    setup_gpio();

    while (true) {
        gpio_put(RED_LED, 1);
        sleep_ms(1000);
        gpio_put(RED_LED, 0);
        sleep_ms(1000);
        gpio_put(GREEN_LED, 1);
        sleep_ms(1000);
        gpio_put(GREEN_LED, 0);
        sleep_ms(1000);
    }
}