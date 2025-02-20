#include <math.h>
#include "inc/mic.h"

// Structure to store microphone data
micdata_t micdata;

/**
 * @brief Initializes the ADC for microphone input.
 *
 * This function initializes the ADC module, configures the GPIO pin
 * for the microphone input, and selects the appropriate ADC channel.
 */

void setup_mic(){
    adc_init();                  // Initialize the ADC module
    adc_gpio_init(MIC_PIN);       // Configure the microphone pin for ADC
    adc_select_input(2);          // Select ADC channel 2 for input
}

/**
 * @brief Collects microphone samples and stores them in the micdata structure.
 *
 * This function reads ADC values and stores them in the micdata.samples array.
 * A small delay is added between each sample to control the sampling rate.
 */

void collect_samples(){
    for(int i = 0; i < SAMPLE_COUNT; i++){
        micdata.samples[i] = adc_read(); // Read ADC value and store it
        sleep_us(100);                   // Delay for sampling rate control
    }
}

/**
 * @brief Converts digital ADC values to decibels (dB).
 *
 * @param micdata Pointer to the microphone data structure containing samples.
 * @param n_samples Number of samples to process.
 * @return The calculated sound level in decibels (dB).
 *
 * This function computes the Root Mean Square (RMS) value of the sampled data,
 * applies a logarithmic transformation, and returns the result in decibels.
 */

float digital_to_dB(micdata_t *micdata, uint8_t n_samples){

    float sum = 0.0;

    // Compute the sum of squared differences from the offset
    for(int i = 0; i < n_samples; i++){
        float value = micdata->samples[i] - OFFSET;
        sum += value * value;
    }

    // Calculate the RMS value
    float rms = sqrt(sum / n_samples);
    
    // Convert RMS value to decibels (dB)
    return 20 * log10(rms / RMS_REFERENCE);
}