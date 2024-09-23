// Copyright 2024 10xEngineers

#include "rhal_base.h"

/**
 * @brief Performs an element-wise subtraction of two 128-bit vectors of 16-bit signed integers and returns the high half of each difference.
 * 
 * This function performs an element-wise subtraction of two 16-bit signed integer vectors (`a` and `b`), 
 * each containing eight elements. After the subtraction, the most significant 8 bits (high half) of each 
 * 16-bit result are extracted to form the output vector. This process is referred to as a "narrowing" operation, 
 * as it reduces the 16-bit result to 8 bits. The function is analogous to the ARM Neon function `vsubhn_s16`, 
 * where the result is a new vector containing the higher 8 bits of the difference of each pair of elements from the input vectors.
 * 
 * @param a The first input vector of type int16x8_t containing 16-bit signed integers.
 * @param b The second input vector of type int16x8_t containing 16-bit signed integers.
 * @return int8x8_t The narrowed result of the element-wise subtraction, where each element is an 8-bit signed integer 
 * extracted from the most significant half of the corresponding 16-bit difference.
 */
int8x8_t vsubhn_s16_rvv(int16x8_t a, int16x8_t b) {
    return __riscv_vlmul_ext_v_i8mf2_i8m1(__riscv_vnsra_wx_i8mf2(__riscv_vsub_vv_i16m1(a, b, VLEN_8), 8, VLEN_8));
}
