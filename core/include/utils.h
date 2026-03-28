#pragma once

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

double q_function(double x);
void prbs31_bit_gen(uint8_t *buf, size_t n_bits, uint32_t seed);
double calc_real_ber(const uint8_t *a, const uint8_t *b, size_t n_bits);

// === Complex 32-bit Float Arithmatic ===
typedef struct {
    float re;
    float im;
} cf32_t;

static inline cf32_t cf32_mul(cf32_t a, cf32_t b) {
    // (a + jb)(c + jd) = (ac - bd) + j(ad + bc)
    cf32_t result;
    result.re = a.re * b.re - a.im * b.im;
    result.im = a.re * b.im + a.im * b.re;
    return result;
}

static inline float cf32_mag_sq(cf32_t a) {
    return (a.re * a.re) + (a.im * a.im);
}
// ===

#ifdef __cplusplus
}
#endif