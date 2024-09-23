// Copyright 2024 10xEngineers

#include "rhal_base.h"

/**
 * @brief Performs an element-wise subtraction of two 128-bit vectors of 64-bit signed integers and returns the high half of each difference.
 * 
 * This function performs an element-wise subtraction of two 64-bit signed integer vectors (`a` and `b`), 
 * each containing eight elements. After the subtraction, the most significant 32 bits (high half) of each 
 * 64-bit result are extracted to form the output vector. This process is referred to as a "narrowing" operation, 
 * as it reduces the 64-bit result to 32 bits. The function is analogous to the ARM Neon function `vsubhn_s64`, 
 * where the result is a new vector containing the higher 32 bits of the difference of each pair of elements from the input vectors.
 * 
 * @param a The first input vector of type int64x2_t containing 64-bit signed integers.
 * @param b The second input vector of type int64x2_t containing 64-bit signed integers.
 * @return int32x2_t The narrowed result of the element-wise subtraction, where each element is an 32-bit signed integer 
 * extracted from the most significant half of the corresponding 64-bit difference.
 */
int32x2_t vsubhn_s64_rvv(int64x2_t a, int64x2_t b) {
    return __riscv_vlmul_ext_v_i32mf2_i32m1(__riscv_vnsra_wx_i32mf2(__riscv_vsub_vv_i64m1(a, b, VLEN_2), 32, VLEN_2));
}
