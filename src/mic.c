#include <math.h>
#include "hardware/adc.h"
#include "inc/mic.h"

#define OFFSET 2048       // Offset value for the ADC
#define RMS_REFERENCE 1.0 // Reference value for RMS calculation
#define MIC_PIN 28        // GPIO pin for the microphone input
#define ADC_CHANNEL 2     // ADC channel for the microphone input

// Structure to store microphone data
micdata_t micdata;

/**
 * @brief Initializes the ADC for microphone input.
 *
 * This function initializes the ADC module, configures the GPIO pin
 * for the microphone input, and selects the appropriate ADC channel.
 */

void setup_mic()
{
    adc_init();                    // Initialize the ADC module
    adc_gpio_init(MIC_PIN);        // Configure the microphone pin for ADC
    adc_select_input(ADC_CHANNEL); // Select ADC channel 2 for input
}

/**
 * @brief Collects microphone samples and stores them in the micdata structure.
 *
 * This function reads ADC values and stores them in the micdata.samples array.
 * A small delay is added between each sample to control the sampling rate.
 */

void collect_samples()
{
    // Read SAMPLE_COUNT samples from the ADC
    for (int i = 0; i < SAMPLE_COUNT; i++)
    {
        micdata.samples[i] = adc_read(); // Read ADC value and store it
        sleep_us(100);                   // Delay for sampling rate control
    }
}

/**
 * @brief Converts digital ADC values to decibels (dB).
 *
 * @param micdata Pointer to the microphone data structure containing samples.
 * @param n_samples Number of samples to process.
 * @return nothing
 *
 * This function computes the Root Mean Square (RMS) value of the sampled data,
 * applies a logarithmic transformation, and store in dB variable the result in decibels.
 */

void digital_to_dB(micdata_t *micdata, uint8_t n_samples)
{

    float sum = 0.0; // Variable to store the sum of squared differences

    // Compute the sum of squared differences from the offset
    for (int i = 0; i < n_samples; i++)
    {
        float value = micdata->samples[i] - OFFSET; // Calculate the difference from the offset
        sum += value * value;                       // Add the squared difference to the sum
    }

    // Calculate the RMS value
    float rms = sqrt(sum / n_samples);

    // Convert RMS value to decibels (dB)
    micdata->dB = 20 * log10(rms / RMS_REFERENCE);
}