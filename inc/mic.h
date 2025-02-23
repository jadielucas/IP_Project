#ifndef MIC_H
#define MIC_H

#define SAMPLE_COUNT 100   // Number of samples to collect from the microphone
#define DB_THRESHOLD 36    // Decibel threshold for signal processing or triggering events

#include "pico/stdlib.h"   // Standard library for Raspberry Pi Pico

/**
 * @brief Structure to hold microphone data.
 *
 * This structure stores raw samples from the microphone and the calculated
 * decibel (dB) value.
 */
typedef struct {
    uint16_t samples[SAMPLE_COUNT];  ///< Array to store raw microphone samples
    volatile float dB;               ///< Calculated decibel level from the samples
} micdata_t;

// External declaration of the microphone data instance
extern micdata_t micdata;

/**
 * @brief Initializes the microphone.
 *
 * This function configures the necessary hardware and settings to start
 * collecting data from the microphone.
 */
void setup_mic();

/**
 * @brief Collects samples from the microphone.
 *
 * This function reads SAMPLE_COUNT values from the microphone and stores
 * them in the micdata structure for further processing.
 */
void collect_samples();

/**
 * @brief Converts raw microphone samples to decibel (dB) values.
 *
 * @param micdata Pointer to the micdata_t structure containing the samples.
 * @param n_samples Number of samples to process for dB calculation.
 */
void digital_to_dB(micdata_t *micdata, uint8_t n_samples);

#endif
