// Copyright 2024 10xEngineers

#ifndef COMMON_RHAL_BASE_H_
#define COMMON_RHAL_BASE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <riscv_vector.h>

/* Define macros for different vector length (vl) */
#define VLEN_1  1
#define VLEN_2  2
#define VLEN_4  4
#define VLEN_8  8
#define VLEN_16 16

/* 64-bit vector register length */
typedef vint8m1_t int8x8_t;
typedef vint16m1_t int16x4_t;
typedef vint32m1_t int32x2_t;
typedef vint64m1_t int64x1_t;
typedef vuint8m1_t uint8x8_t;


/* vadd */
int8x8_t vadd_s8_rvv(int8x8_t a, int8x8_t b);
int16x4_t vadd_s16_rvv(int16x4_t a, int16x4_t b);
int32x2_t vadd_s32_rvv(int32x2_t a, int32x2_t b);
int64x1_t vadd_s64_rvv(int64x1_t a, int64x1_t b);

/* vsub* */
int8x8_t vsub_s8_rvv(int8x8_t a, int8x8_t b);
int16x4_t vsub_s16_rvv(int16x4_t a, int16x4_t b);
int32x2_t vsub_s32_rvv(int32x2_t a, int32x2_t b);
int64x1_t vsub_s64_rvv(int64x1_t a, int64x1_t b);

uint8x8_t vsub_u8_rvv(uint8x8_t a, uint8x8_t b);

#ifdef __cplusplus
}
#endif

#endif  // COMMON_RHAL_BASE_H_
