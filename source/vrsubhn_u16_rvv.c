// Copyright 2024 10xEngineers

#include "rhal_base.h"

/**
 * @brief Performs an element-wise rounding subtraction of two 128-bit vectors of 16-bit unsigned integers and returns the high half of each rounded difference.
 * 
 * This function performs an element-wise subtraction of two 16-bit unsigned integer vectors (`a` and `b`), each containing eight elements. After the 
 * subtraction, a rounding constant is subed to the result to ensure proper rounding before narrowing. The most significant 8 bits (high half) of 
 * each 16-bit rounded difference are extracted to form the output vector. This process is referred to as a "rounding narrowing" operation, as it reduces 
 * the 16-bit result to 8 bits while ensuring the result is properly rounded. The function is analogous to the ARM Neon function `vrsubhn_s16`, 
 * where the result is a new vector containing the higher 8 bits of the rounded difference of each pair of elements from the input vectors.
 * 
 * @param a The first input vector of type int16x8_t containing 16-bit unsigned integers.
 * @param b The second input vector of type int16x8_t containing 16-bit unsigned integers.
 * @return int8x8_t The narrowed result of the element-wise rounding subtraction, where each element is an 8-bit unsigned integer extracted from the 
 * most significant half of the corresponding 16-bit rounded difference.
 */
uint8x8_t vrsubhn_u16_rvv(uint16x8_t a, uint16x8_t b) {
    return __riscv_vlmul_ext_v_u8mf2_u8m1(__riscv_vnsrl_wx_u8mf2(__riscv_vadd_vx_u16m1(__riscv_vsub_vv_u16m1(a, b, VLEN_8),1<<7,VLEN_8), 8, VLEN_8));
}
