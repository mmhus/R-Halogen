// Copyright 2024 10xEngineers

#include "rhal_base.h"

/**
 * @brief Performs an element-wise rounding subtraction of two 128-bit vectors of 32-bit unsigned integers and returns the high half of each rounded difference.
 * 
 * This function performs an element-wise subtraction of two 32-bit unsigned integer vectors (`a` and `b`), each containing four elements. After the 
 * subtraction, a rounding constant is subed to the result to ensure proper rounding before narrowing. The most significant 16 bits (high half) of 
 * each 32-bit rounded difference are extracted to form the output vector. This process is referred to as a "rounding narrowing" operation, as it reduces 
 * the 32-bit result to 16 bits while ensuring the result is properly rounded. The function is analogous to the ARM Neon function `vrsubhn_s32`, 
 * where the result is a new vector containing the higher 16 bits of the rounded difference of each pair of elements from the input vectors.
 * 
 * @param a The first input vector of type int32x4_t containing 32-bit unsigned integers.
 * @param b The second input vector of type int32x4_t containing 32-bit unsigned integers.
 * @return int16x4_t The narrowed result of the element-wise rounding subtraction, where each element is an 16-bit unsigned integer extracted from the 
 * most significant half of the corresponding 32-bit rounded difference.
 */
uint16x4_t vrsubhn_u32_rvv(uint32x4_t a, uint32x4_t b) {
    return __riscv_vlmul_ext_v_u16mf2_u16m1(__riscv_vnsrl_wx_u16mf2(__riscv_vadd_vx_u32m1(__riscv_vsub_vv_u32m1(a, b, VLEN_4),1<<15,VLEN_4), 16, VLEN_4));
}
