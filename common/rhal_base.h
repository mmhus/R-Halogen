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

int16x8_t vaddl_s8_rvv(int8x8_t a, int8x8_t b);
int32x4_t vaddl_s16_rvv(int16x4_t a, int16x4_t b);
int64x2_t vaddl_s32_rvv(int32x2_t a, int32x2_t b);

uint16x8_t vaddl_u8_rvv(uint8x8_t a, uint8x8_t b);
uint32x4_t vaddl_u16_rvv(uint16x4_t a, uint16x4_t b);
uint64x2_t vaddl_u32_rvv(uint32x2_t a, uint32x2_t b);

int16x8_t vaddw_s8_rvv(int16x8_t a, int8x8_t b);
int32x4_t vaddw_s16_rvv(int32x4_t a, int16x4_t b);
int64x2_t vaddw_s32_rvv(int64x2_t a, int32x2_t b);

uint16x8_t vaddw_u8_rvv(uint16x8_t a, uint8x8_t b);
uint32x4_t vaddw_u16_rvv(uint32x4_t a, uint16x4_t b);
uint64x2_t vaddw_u32_rvv(uint64x2_t a, uint32x2_t b);

int8x8_t vhadd_s8_rvv(int8x8_t a, int8x8_t b);
int16x4_t vhadd_s16_rvv(int16x4_t a, int16x4_t b);
int32x2_t vhadd_s32_rvv(int32x2_t a, int32x2_t b);

int8x16_t vhaddq_s8_rvv(int8x16_t a, int8x16_t b);
int16x8_t vhaddq_s16_rvv(int16x8_t a, int16x8_t b);
int32x4_t vhaddq_s32_rvv(int32x4_t a, int32x4_t b);

uint8x8_t vhadd_u8_rvv(uint8x8_t a, uint8x8_t b);
uint16x4_t vhadd_u16_rvv(uint16x4_t a, uint16x4_t b);
uint32x2_t vhadd_u32_rvv(uint32x2_t a, uint32x2_t b);

uint8x16_t vhaddq_u8_rvv(uint8x16_t a, uint8x16_t b);
uint16x8_t vhaddq_u16_rvv(uint16x8_t a, uint16x8_t b);
uint32x4_t vhaddq_u32_rvv(uint32x4_t a, uint32x4_t b);

int8x8_t vrhadd_s8_rvv(int8x8_t a, int8x8_t b);
int16x4_t vrhadd_s16_rvv(int16x4_t a, int16x4_t b);
int32x2_t vrhadd_s32_rvv(int32x2_t a, int32x2_t b);

int8x16_t vrhaddq_s8_rvv(int8x16_t a, int8x16_t b);
int16x8_t vrhaddq_s16_rvv(int16x8_t a, int16x8_t b);
int32x4_t vrhaddq_s32_rvv(int32x4_t a, int32x4_t b);

uint8x8_t vrhadd_u8_rvv(uint8x8_t a, uint8x8_t b);
uint16x4_t vrhadd_u16_rvv(uint16x4_t a, uint16x4_t b);
uint32x2_t vrhadd_u32_rvv(uint32x2_t a, uint32x2_t b);

uint8x16_t vrhaddq_u8_rvv(uint8x16_t a, uint8x16_t b);
uint16x8_t vrhaddq_u16_rvv(uint16x8_t a, uint16x8_t b);
uint32x4_t vrhaddq_u32_rvv(uint32x4_t a, uint32x4_t b);

int8x8_t vqadd_s8_rvv(int8x8_t a, int8x8_t b);
int16x4_t vqadd_s16_rvv(int16x4_t a, int16x4_t b);
int32x2_t vqadd_s32_rvv(int32x2_t a, int32x2_t b);
int64x1_t vqadd_s64_rvv(int64x1_t a, int64x1_t b);

int8x16_t vqaddq_s8_rvv(int8x16_t a, int8x16_t b);
int16x8_t vqaddq_s16_rvv(int16x8_t a, int16x8_t b);
int32x4_t vqaddq_s32_rvv(int32x4_t a, int32x4_t b);
int64x2_t vqaddq_s64_rvv(int64x2_t a, int64x2_t b);

uint8x8_t vqadd_u8_rvv(uint8x8_t a, uint8x8_t b);
uint16x4_t vqadd_u16_rvv(uint16x4_t a, uint16x4_t b);
uint32x2_t vqadd_u32_rvv(uint32x2_t a, uint32x2_t b);
uint64x1_t vqadd_u64_rvv(uint64x1_t a, uint64x1_t b);

uint8x16_t vqaddq_u8_rvv(uint8x16_t a, uint8x16_t b);
uint16x8_t vqaddq_u16_rvv(uint16x8_t a, uint16x8_t b);
uint32x4_t vqaddq_u32_rvv(uint32x4_t a, uint32x4_t b);
uint64x2_t vqaddq_u64_rvv(uint64x2_t a, uint64x2_t b);

/* vsub* */
int8x8_t vsub_s8_rvv(int8x8_t a, int8x8_t b);
int16x4_t vsub_s16_rvv(int16x4_t a, int16x4_t b);
int32x2_t vsub_s32_rvv(int32x2_t a, int32x2_t b);
int64x1_t vsub_s64_rvv(int64x1_t a, int64x1_t b);

int8x16_t vsubq_s8_rvv(int8x16_t a, int8x16_t b);
int16x8_t vsubq_s16_rvv(int16x8_t a, int16x8_t b);
int32x4_t vsubq_s32_rvv(int32x4_t a, int32x4_t b);
int64x2_t vsubq_s64_rvv(int64x2_t a, int64x2_t b);

uint8x8_t vsub_u8_rvv(uint8x8_t a, uint8x8_t b);
uint16x4_t vsub_u16_rvv(uint16x4_t a, uint16x4_t b);
uint32x2_t vsub_u32_rvv(uint32x2_t a, uint32x2_t b);
uint64x1_t vsub_u64_rvv(uint64x1_t a, uint64x1_t b);

uint8x16_t vsubq_u8_rvv(uint8x16_t a, uint8x16_t b);
uint16x8_t vsubq_u16_rvv(uint16x8_t a, uint16x8_t b);
uint32x4_t vsubq_u32_rvv(uint32x4_t a, uint32x4_t b);
uint64x2_t vsubq_u64_rvv(uint64x2_t a, uint64x2_t b);

int16x8_t vsubl_s8_rvv(int8x8_t a, int8x8_t b);
int32x4_t vsubl_s16_rvv(int16x4_t a, int16x4_t b);
int64x2_t vsubl_s32_rvv(int32x2_t a, int32x2_t b);

uint16x8_t vsubl_u8_rvv(uint8x8_t a, uint8x8_t b);
uint32x4_t vsubl_u16_rvv(uint16x4_t a, uint16x4_t b);
uint64x2_t vsubl_u32_rvv(uint32x2_t a, uint32x2_t b);

int16x8_t vsubw_s8_rvv(int16x8_t a, int8x8_t b);
int32x4_t vsubw_s16_rvv(int32x4_t a, int16x4_t b);
int64x2_t vsubw_s32_rvv(int64x2_t a, int32x2_t b);

uint16x8_t vsubw_u8_rvv(uint16x8_t a, uint8x8_t b);
uint32x4_t vsubw_u16_rvv(uint32x4_t a, uint16x4_t b);
uint64x2_t vsubw_u32_rvv(uint64x2_t a, uint32x2_t b);

int8x8_t vhsub_s8_rvv(int8x8_t a, int8x8_t b);
int16x4_t vhsub_s16_rvv(int16x4_t a, int16x4_t b);
int32x2_t vhsub_s32_rvv(int32x2_t a, int32x2_t b);

int8x16_t vhsubq_s8_rvv(int8x16_t a, int8x16_t b);
int16x8_t vhsubq_s16_rvv(int16x8_t a, int16x8_t b);
int32x4_t vhsubq_s32_rvv(int32x4_t a, int32x4_t b);

uint8x8_t vhsub_u8_rvv(uint8x8_t a, uint8x8_t b);
uint16x4_t vhsub_u16_rvv(uint16x4_t a, uint16x4_t b);
uint32x2_t vhsub_u32_rvv(uint32x2_t a, uint32x2_t b);

uint8x16_t vhsubq_u8_rvv(uint8x16_t a, uint8x16_t b);
uint16x8_t vhsubq_u16_rvv(uint16x8_t a, uint16x8_t b);
uint32x4_t vhsubq_u32_rvv(uint32x4_t a, uint32x4_t b);

#ifdef __cplusplus
}
#endif

#endif  // COMMON_RHAL_BASE_H_
