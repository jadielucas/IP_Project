#include <stdio.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/i2c.h"
#include "inc/ssd1306.h"
#include "inc/led.h"
#include "inc/mic.h"
#include "inc/display.h"

float digital_to_dB(micdata_t *micdata, uint8_t n_samples){

    float sum = 0.0;

    for(int i = 0; i<n_samples; i++){
        float value = micdata->samples[i] - OFFSET;
        sum += value * value;
    }

    float rms = sqrt(sum/n_samples);
    
    return 20 * log10(rms/RMS_REFERENCE);
}

int main()
{
    stdio_init_all();
    setup_gpio();
    setup_adc();
    setup_i2c_ssd1306();

    while (true) {
        
        for(int i = 0; i<SAMPLE_COUNT; i++){
            micdata.samples[i] = adc_read();
            sleep_us(100);
        }

        micdata.dB = digital_to_dB(&micdata, SAMPLE_COUNT);
        
        sprintf(buffer, "dB: %.2f", micdata.dB);
        ssd1306_draw_string(&disp, 0, 0, 2, buffer);
        ssd1306_show(&disp);
        ssd1306_clear_area(&disp, 0, 0, 128, 32);
        sleep_ms(100);
    }
}