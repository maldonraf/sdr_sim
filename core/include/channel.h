#pragma once

#ifndef MODULATOR_H
#define MODULATOR_H

#include "utils.h"
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

static void box_muller(float *n0, float *n1, uint32_t *seed);
void awgn_channel(cf32_t *samples, size_t n_samples, double eb_n0_db, int sps);

#ifdef __cplusplus
}
#endif

#endif