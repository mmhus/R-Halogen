// Copyright 2024 10xEngineers

#include "rhal_base.h"

/**
 * @brief Performs an element-wise subtraction of two 128-bit vectors of 32-bit signed integers and returns the high half of each difference.
 * 
 * This function performs an element-wise subtraction of two 32-bit signed integer vectors (`a` and `b`), 
 * each containing eight elements. After the subtraction, the most significant 16 bits (high half) of each 
 * 32-bit result are extracted to form the output vector. This process is referred to as a "narrowing" operation, 
 * as it reduces the 32-bit result to 16 bits. The function is analogous to the ARM Neon function `vsubhn_s32`, 
 * where the result is a new vector containing the higher 16 bits of the difference of each pair of elements from the input vectors.
 * 
 * @param a The first input vector of type int32x4_t containing 32-bit signed integers.
 * @param b The second input vector of type int32x4_t containing 32-bit signed integers.
 * @return int16x4_t The narrowed result of the element-wise subtraction, where each element is an 16-bit signed integer 
 * extracted from the most significant half of the corresponding 32-bit difference.
 */
int16x4_t vsubhn_s32_rvv(int32x4_t a, int32x4_t b) {
    return __riscv_vlmul_ext_v_i16mf2_i16m1(__riscv_vnsra_wx_i16mf2(__riscv_vsub_vv_i32m1(a, b, VLEN_4), 16, VLEN_4));
}
