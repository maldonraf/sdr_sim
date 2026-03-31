/*
This file contains functions for symbol mapping, up-sampling, pulse shaping.

Includes:
    - TBD
*/

#include "modulator.h"

void modulate_bpsk(cf32_t *samples, const uint8_t *bits, size_t n_bits, int sps) {
    /*
    * For BPSK, I am treating 1 as (1 + j0) and 0 as (0 + j0).
    */
    
    for (size_t i; i < n_bits; i++) {
        uint8_t byte = bits[i / 8];
        uint8_t bit = (byte >> (7 - (i % 8))) & 0x1;

        cf32_t symbol;
        symbol.re = bit ? -1.0f : 1.0f;
        symbol.im = 0.0f;

        // repeat bits sps times, fill into samples array
        for (int s = 0; s < sps; s++) {
            samples[(i * sps) + s] = symbol;
        }
    }
}