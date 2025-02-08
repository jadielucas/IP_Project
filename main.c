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

        update_display_db_value(&micdata);

        sleep_ms(100);
    }
    return 0;
}