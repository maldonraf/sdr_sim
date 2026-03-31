/*
This file contains functions for noise generation, channel impairments.

Includes:
    - TBD
*/

#include "channel.h"
#include <math.h>

static void box_muller(float *n0, float *n1, uint32_t *seed) {
    // Implementation TBD

    *n0 = 0;
    *n1 = 1;
}

void awgn_channel(cf32_t *samples, size_t n_samples, double eb_n0_db, int sps) {
    double eb_n0_linear = db_to_linear(eb_n0_db);
    double noise_variance = 1.0 / (2.0 * eb_n0_linear * sps);
    float noise_std = (float)sqrt(noise_variance);

    uint32_t seed = 1234567891u;

    for (size_t i = 0; i < n_samples; i += 2) {
        float z0, z1;
        box_muller(&z0, &z1, &seed);
        samples[i].re += (float)(z0 * noise_std);
        samples[i].im += (float)(z1 * noise_std);
    }
}