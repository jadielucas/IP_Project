#include "inc/led.h"

// Structure to store a repeating timer
struct repeating_timer timer;

/**
 * @brief Configures GPIO pins for the LEDs.
 *
 * Initializes and sets the direction of GPIO pins used for the red and green LEDs.
 */

void setup_leds()
{
    gpio_init(RED_LED);                // Initialize the red LED pin
    gpio_init(GREEN_LED);              // Initialize the green LED pin
    gpio_set_dir(RED_LED, GPIO_OUT);   // Set the red LED as output
    gpio_set_dir(GREEN_LED, GPIO_OUT); // Set the green LED as output
}

/**
 * @brief Updates the LED status based on the dB level detected by the microphone.
 *
 * @param t Pointer to the repeating timer structure.
 * @return true Always returns true to keep the timer running.
 *
 * The function checks the dB level contained in the micdata_t structure and controls
 * the LEDs based on a predefined threshold (DB_THRESHOLD). If the dB level exceeds the threshold,
 * the red LED turns on and the green LED turns off; otherwise, the green LED turns on and the red LED turns off.
 */

bool update_led_status(struct repeating_timer *t)
{
    // Cast the timer user data to the micdata_t structure
    micdata_t *micdata = (micdata_t *)t->user_data;

    // Check if the dB level exceeds the defined threshold
    if (micdata->dB > DB_THRESHOLD)
    {
        gpio_put(RED_LED, 1);   // Turn on the red LED
        gpio_put(GREEN_LED, 0); // Turn off the green LED
    }
    else
    {
        gpio_put(RED_LED, 0);   // Turn off the red LED
        gpio_put(GREEN_LED, 1); // Turn on the green LED
    }

    return true; // Return true to keep the timer running continuously
}