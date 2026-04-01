#pragma once

#include "utils.h"
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void modulate_bpsk(cf32_t *samples, const uint8_t *bits, size_t n_bits, int sps);

#ifdef __cplusplus
}
#endif