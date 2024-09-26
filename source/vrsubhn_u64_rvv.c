// Copyright 2024 10xEngineers

#include "rhal_base.h"

/**
 * @brief Performs an element-wise rounding subtraction of two 128-bit vectors of 64-bit unsigned integers and returns the high half of each rounded difference.
 * 
 * This function performs an element-wise subtraction of two 64-bit unsigned integer vectors (`a` and `b`), each containing two elements. After the 
 * subtraction, a rounding constant is subed to the result to ensure proper rounding before narrowing. The most significant 32 bits (high half) of 
 * each 64-bit rounded difference are extracted to form the output vector. This process is referred to as a "rounding narrowing" operation, as it reduces 
 * the 64-bit result to 32 bits while ensuring the result is properly rounded. The function is analogous to the ARM Neon function `vrsubhn_s64`, 
 * where the result is a new vector containing the higher 32 bits of the rounded difference of each pair of elements from the input vectors.
 * 
 * @param a The first input vector of type int64x2_t containing 64-bit unsigned integers.
 * @param b The second input vector of type int64x2_t containing 64-bit unsigned integers.
 * @return int32x2_t The narrowed result of the element-wise rounding subtraction, where each element is an 32-bit unsigned integer extracted from the 
 * most significant half of the corresponding 64-bit rounded difference.
 */
uint32x2_t vrsubhn_u64_rvv(uint64x2_t a, uint64x2_t b) {
    return __riscv_vlmul_ext_v_u32mf2_u32m1(__riscv_vnsrl_wx_u32mf2(__riscv_vadd_vx_u64m1(__riscv_vsub_vv_u64m1(a, b, VLEN_2),(uint64_t)1<<31,VLEN_2), 32, VLEN_2));
}
