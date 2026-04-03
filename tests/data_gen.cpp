#include <cstdio>
#include <cassert>
#include <cmath>
#include <cstring>
#include <stdlib.h>

#include "utils.h"
#include "modulator.h"
#include "channel.h"

void data_gen(double eb_n0_db) {
    const uint8_t  sps       = 16;
    const uint32_t bit_count = 4096;

    cf32_t  *symbol_buffer = (cf32_t *)calloc(bit_count * sps, sizeof(cf32_t));
    uint8_t *byte_buffer   = (uint8_t *)calloc(bit_count / 8,  sizeof(uint8_t));
    uint8_t *rx_buffer     = (uint8_t *)calloc(bit_count / 8,  sizeof(uint8_t));

    if (!symbol_buffer || !byte_buffer || !rx_buffer) {
        free(symbol_buffer);
        free(byte_buffer);
        free(rx_buffer);
        return;
    }

    prbs31_bit_gen(byte_buffer, bit_count, 0x7FFFFFFF);
    modulate_bpsk(symbol_buffer, byte_buffer, bit_count, sps);
    awgn_channel(symbol_buffer, bit_count * sps, eb_n0_db, sps);

    for (size_t i = 0; i < bit_count; i++) {
        size_t sample_idx = i * sps + (sps / 2); // center of symbol period ?
        uint8_t bit = (symbol_buffer[sample_idx].re > 0.0f) ? 0 : 1;
        if (bit) {
            rx_buffer[i / 8] |= (1 << (7 - (i % 8)));
        }
    }

    for (size_t i = 0; i < bit_count * sps; i++) {
        printf("%f, %f\n", symbol_buffer[i].re, symbol_buffer[i].im);
    }

    free(symbol_buffer);
    free(byte_buffer);
    free(rx_buffer);
}

int main(int argc, char *argv[]) {
    double eb_n0_db = 10.0;

    if (argc > 1) {
        eb_n0_db = atof(argv[1]);
    } else {
        fprintf(stderr, "Usage: data_gen <eb_n0_db>\n");
        fprintf(stderr, "Using default: %.1f dB\n", eb_n0_db);
    }

    data_gen(eb_n0_db);
    return 0;
}