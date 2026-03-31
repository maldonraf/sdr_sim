#pragma once

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    MOD_BPSK = 0,
    MOD_QPSK = 1,
} Modulation;

typedef struct {
    float re;
    float im;
} cf32_t;

double db_to_linear(double db);
double q_function(double x);
void prbs31_bit_gen(uint8_t *buf, size_t n_bits, uint32_t seed);
double calc_real_ber(const uint8_t *a, const uint8_t *b, size_t n_bits);
double calc_theoretical_ber(Modulation modulation, double eb_n0_db);

// === Complex 32-bit Float Arithmatic ===
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