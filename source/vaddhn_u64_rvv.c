// Copyright 2024 10xEngineers

#include "rhal_base.h"

/**
 * @brief Performs an element-wise addition of two 128-bit vectors of 64-bit unsigned integers and returns the high half of each sum.
 * 
 * This function performs an element-wise addition of two 64-bit unsigned integer vectors (`a` and `b`), 
 * each containing eight elements. After the addition, the most significant 32 bits (high half) of each 
 * 64-bit result are extracted to form the output vector. This process is referred to as a "narrowing" operation, 
 * as it reduces the 64-bit result to 32 bits. The function is analogous to the ARM Neon function `vaddhn_u64`, 
 * where the result is a new vector containing the higher 32 bits of the sum of each pair of elements from the input vectors.
 * 
 * @param a The first input vector of type uint64x2_t containing 64-bit unsigned integers.
 * @param b The second input vector of type uint64x2_t containing 64-bit unsigned integers.
 * @return uint32x2_t The narrowed result of the element-wise addition, where each element is an 32-bit unsigned integer 
 * extracted from the most significant half of the corresponding 64-bit sum.
 */
uint32x2_t vaddhn_u64_rvv(uint64x2_t a, uint64x2_t b) {
    return __riscv_vlmul_ext_v_u32mf2_u32m1(__riscv_vnsrl_wx_u32mf2(__riscv_vadd_vv_u64m1(a, b, VLEN_2), 32, VLEN_2));
}
