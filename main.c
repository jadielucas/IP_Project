#include "pico/stdlib.h"               // Standard library for Raspberry Pi Pico
#include "libs/ssd1306.h"              // Library for controlling the SSD1306 OLED display
#include "inc/led.h"                   // Library for LED control
#include "inc/mic.h"                   // Library for microphone data collection
#include "inc/display.h"               // Library for display manipulation
#include "inc/wifi.h"                  // Library for Wi-Fi connection
#include "inc/mqtt.h"                  // Library for MQTT protocol communication

// Main function of the program
int main()
{
    stdio_init_all();                  // Initialize standard serial communication
    setup_leds();                      // Configure LEDs
    setup_mic();                       // Initialize the microphone
    setup_display();                   // Configure the display
    wifi_init();                       // Initialize the Wi-Fi module
    start_mqtt_client();               // Start the MQTT client for remote communication

    // Add a timer that calls the LED status update function every 100ms
    add_repeating_timer_ms(200, update_led_status, &micdata, &timer);

    while (true) {
        
        collect_samples();             // Collect samples from the microphone

        micdata.dB = digital_to_dB(&micdata, SAMPLE_COUNT);    // Convert digital microphone values to dB

        update_display_db_value(&micdata);                     // Update the dB value on the display

        publish_db_to_mqtt(&micdata);                          // Publish the dB value to the MQTT broker

        sleep_ms(200);                 // Wait 100ms before the next iteration

    }
    return 0;
}