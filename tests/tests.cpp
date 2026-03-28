#include <cstdio>
#include <cassert>
#include <cmath>
#include <cstring>

#include "utils.h"

void test_q_function() {
    // === Test value outputs ===
    assert(fabs(q_function(0.0) - 0.5) < 1e-12);
    assert(fabs(q_function(1.0) - 0.15865525393145707) < 1e-9);
    assert(fabs(q_function(2.0) - 0.02275013194817921) < 1e-9);
    assert(fabs(q_function(3.0) - 0.00134989803163009) < 1e-9);

    // === Test range (-10 - 10) ===
    for (double x = -10; x <= 10; x += 0.5) {
        double q = q_function(x);
        assert(q >= 0.0 && q <= 1.0);
    }
}

void test_prbs31_bit_gen() {
    // === Test Known Sequence ===
    // use seed: 0x7FFFFFFF
    uint8_t buf[8] = {0};
    prbs31_bit_gen(buf, 64, 0x7FFFFFFF);

    // known sequence of first 64 bits
    uint8_t expected[8] = {
        0xFF, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x1C
    };

    assert(memcmp(buf, expected, 8) == 0);
}

void test_real_ber() {
    const uint8_t byte_array_0[8] = {
        0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00
    };

    const uint8_t byte_array_1[8] = {
        0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF
    };

    // 0 BER: identical arrays
    double ber_0 = calc_real_ber(byte_array_0, byte_array_0, 8 * 8);
    // 0.25 BER: 2 bytes out of 8 mismatched
    double ber_1 = calc_real_ber(byte_array_0, byte_array_1, 8 * 8);

    assert(ber_0 == 0);
    assert(ber_1 == 0.25);
}

int main() {
    test_q_function();
    printf("Check PASS: Q function.\n");
    test_prbs31_bit_gen();
    printf("Check PASS: PRBS-31 bit gen.\n");
    test_real_ber();
    printf("Check PASS: BER calculation.\n");

    return 0;
}