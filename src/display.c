#include "inc/display.h"

ssd1306_t disp;  // Structure to handle the SSD1306 display
char buffer[20]; // Buffer to store the string to be displayed

/**
 * @brief Sets up I2C communication and initializes the SSD1306 display.
 *
 * This function initializes the I2C1 interface with a 400 kHz rate and configures
 * GPIO pins 14 and 15 for I2C communication. It also initializes the SSD1306 OLED display
 * with a resolution of 128x64 pixels and I2C address 0x3C.
 *
 * The display is cleared, and an initial string "SilentPico" is displayed temporarily.
 */

void setup_display()
{
    i2c_init(i2c1, 400000);               // Initialize I2C1 interface with 400 kHz frequency
    gpio_set_function(14, GPIO_FUNC_I2C); // Set GPIO 14 as I2C function
    gpio_set_function(15, GPIO_FUNC_I2C); // Set GPIO 15 as I2C function
    gpio_pull_up(14);                     // Enable pull-up on pin 14
    gpio_pull_up(15);                     // Enable pull-up on pin 15

    disp.external_vcc = false;                // Set to use internal power supply for the display
    ssd1306_init(&disp, 128, 64, 0x3C, i2c1); // Initialize SSD1306 display

    ssd1306_clear(&disp);                               // Clear the display
    ssd1306_draw_string(&disp, 5, 28, 2, "SilentPico"); // Display "SilentPico" on screen
    ssd1306_show(&disp);                                // Update the screen to show content
    ssd1306_clear(&disp);                               // Clear the screen after initial display
}

/**
 * @brief Updates the display with the decibel (dB) level captured by the microphone.
 *
 * @param micdata Pointer to the micdata_t structure containing the dB value to be displayed.
 *
 * The dB value is formatted as a string and displayed on the screen. After updating,
 * the area where the information was written is cleared to prevent text overlapping.
 */

void update_display_db_value(micdata_t *micdata)
{
    sprintf(buffer, "dB: %.2f", micdata->dB);

    ssd1306_draw_string(&disp, 0, 0, 2, buffer);
    ssd1306_show(&disp);
    ssd1306_clear_area(&disp, 0, 0, 128, 28);
}