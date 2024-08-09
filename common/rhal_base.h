// Copyright 2024 10xEngineers

#ifndef COMMON_RHAL_BASE_H_
#define COMMON_RHAL_BASE_H_

#ifdef __cplusplus
extern "C" {
#endif

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
typedef vuint16m1_t uint16x4_t;
typedef vuint32m1_t uint32x2_t;
typedef vuint64m1_t uint64x1_t;

/* 128-bit vector register length */
typedef vint8m1_t int8x16_t;
typedef vint16m1_t int16x8_t;
typedef vint32m1_t int32x4_t;
typedef vint64m1_t int64x2_t;
typedef vuint8m1_t uint8x16_t;
typedef vuint16m1_t uint16x8_t;
typedef vuint32m1_t uint32x4_t;
typedef vuint64m1_t uint64x2_t;


/* vadd */
int8x8_t vadd_s8_rvv(int8x8_t a, int8x8_t b);
int16x4_t vadd_s16_rvv(int16x4_t a, int16x4_t b);
int32x2_t vadd_s32_rvv(int32x2_t a, int32x2_t b);
int64x1_t vadd_s64_rvv(int64x1_t a, int64x1_t b);

int8x16_t vaddq_s8_rvv(int8x16_t a, int8x16_t b);
int16x8_t vaddq_s16_rvv(int16x8_t a, int16x8_t b);
int32x4_t vaddq_s32_rvv(int32x4_t a, int32x4_t b);
int64x2_t vaddq_s64_rvv(int64x2_t a, int64x2_t b);

uint8x8_t vadd_u8_rvv(uint8x8_t a, uint8x8_t b);
uint16x4_t vadd_u16_rvv(uint16x4_t a, uint16x4_t b);
uint32x2_t vadd_u32_rvv(uint32x2_t a, uint32x2_t b);
uint64x1_t vadd_u64_rvv(uint64x1_t a, uint64x1_t b);

uint8x16_t vaddq_u8_rvv(uint8x16_t a, uint8x16_t b);
uint16x8_t vaddq_u16_rvv(uint16x8_t a, uint16x8_t b);
uint32x4_t vaddq_u32_rvv(uint32x4_t a, uint32x4_t b);
uint64x2_t vaddq_u64_rvv(uint64x2_t a, uint64x2_t b);

#ifdef __cplusplus
}
#endif

#endif  // COMMON_RHAL_BASE_H_
