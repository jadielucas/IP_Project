#ifndef MIC_H
#define MIC_H

#define SAMPLE_COUNT 100
#define OFFSET 2048
#define RMS_REFERENCE 1.0
#define MIC_PIN 28

typedef struct{
    uint16_t samples[SAMPLE_COUNT];
    float dB;
} micdata_t;

extern micdata_t micdata;

void setup_adc();

#endif