#include "inc/led.h"

struct repeating_timer timer;

// Function to setup GPIO pins
void setup_leds()
{
    gpio_init(RED_LED);
    gpio_init(GREEN_LED);
    gpio_set_dir(RED_LED, GPIO_OUT);
    gpio_set_dir(GREEN_LED, GPIO_OUT);
}

bool update_led_status(struct repeating_timer *t)
{

    micdata_t *micdata = (micdata_t *)t->user_data;

    if (micdata->dB > DB_THRESHOLD)
    {
        gpio_put(RED_LED, 1);
        gpio_put(GREEN_LED, 0);
        return true;
    }
    else
    {
        gpio_put(RED_LED, 0);
        gpio_put(GREEN_LED, 1);
        return true;
    }
}