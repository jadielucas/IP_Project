#include <math.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "inc/mic.h"

micdata_t micdata;

// Function to setup ADC
void setup_mic(){
    adc_init();
    adc_gpio_init(MIC_PIN);
    adc_select_input(2);
}

void collect_samples(){
    for(int i = 0; i < SAMPLE_COUNT; i++){
        micdata.samples[i] = adc_read();
        sleep_us(100);
    }
}

float digital_to_dB(micdata_t *micdata, uint8_t n_samples){

    float sum = 0.0;

    for(int i = 0; i<n_samples; i++){
        float value = micdata->samples[i] - OFFSET;
        sum += value * value;
    }

    float rms = sqrt(sum/n_samples);
    
    return 20 * log10(rms/RMS_REFERENCE);
}