/*
This file contains utilities for bit generation, BER calculations, etc.

Includes:
    - TBD
*/

#include "utils.h"
#include <math.h>

double q_function(double x) {
    /*
    * @brief Computes Q-function.
    * @sa https://en.wikipedia.org/wiki/Q-function
    * 
    * Q(x) = 0.5 * erfc(x / sqrt(2)).
    * For x < 0: Q(-x) = 1 - Q(x).
    *
    * @param x  Input value.
    * @return q  Probability that a gaussian random variable is larger than x STD.
    */

    double q;
    double q_posx = 0.5 * erfc(abs(x) / sqrt(2));

    q = (x < 0) ? 1 - q_posx : q_posx;

    return q;
}

void prbs31_bit_gen(uint8_t *buf, size_t n_bits, uint32_t seed) {
    /*
    * @brief Fills buf with psuedo-random bitstream.
    * @param buf
    * @return No return.
    */

    // TODO: Add support for other PRBS types.
    
    // 0 is an invalid seed
    if (seed == 0) seed = 0x7FFFFFFF;

    // trim seed to 31 bits
    uint32_t lfsr = seed & 0x7FFFFFFF;

    size_t byte_idx = 0;
    uint8_t current_byte = 0;
    int bit_pos = 0;

    for (size_t i = 0; i < n_bits; i++)
    {
        // output bit (MSB of LFSR)
        uint8_t out_bit = (lfsr >> 30) & 0x1;

        // pack into byte (MSB first)
        current_byte |= (out_bit << (7 - bit_pos));
        bit_pos++;

        if (bit_pos == 8)
        {
            buf[byte_idx++] = current_byte;
            current_byte = 0;
            bit_pos = 0;
        }

        // feedback: XOR of taps (bit 30 and 27 for PRBS-31)
        uint32_t new_bit = ((lfsr >> 30) ^ (lfsr >> 27)) & 0x1;

        // shift left and insert new bit at LSB
        lfsr = ((lfsr << 1) | new_bit) & 0x7FFFFFFF;
    }

    if (bit_pos != 0)
    {
        buf[byte_idx] = current_byte;
    }
}

double calc_real_ber(const uint8_t *a, const uint8_t *b, size_t n_bits) {
    // TODO: Make this work with partial bytes.
    // Currently requires bitstreams in lengths of multiples of 8.

    size_t total_errors = 0;
    size_t n_bytes = n_bits / 8;

    for (size_t i = 0; i < n_bytes; i++) {
        total_errors += __builtin_popcount(a[i] ^ b[i]);
    }

    return (double)total_errors / (double)n_bits;
}