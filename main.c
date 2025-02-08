#include <stdio.h>
#include "pico/stdlib.h"
#include "libs/ssd1306.h"
#include "inc/led.h"
#include "inc/mic.h"
#include "inc/display.h"
#include "inc/wifi.h"
#include "inc/mqtt.h"

int main()
{
    stdio_init_all();
    setup_gpio();
    setup_adc();
    setup_i2c_ssd1306();
    wifi_init();
    start_mqtt_client();

    while (true) {
        
        collect_samples();

        micdata.dB = digital_to_dB(&micdata, SAMPLE_COUNT);
        
        sprintf(buffer, "dB: %.2f", micdata.dB);
        ssd1306_draw_string(&disp, 0, 0, 2, buffer);
        ssd1306_show(&disp);
        ssd1306_clear_area(&disp, 0, 0, 128, 32);

        sleep_ms(100);
    }
}