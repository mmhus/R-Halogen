// Copyright 2024 10xEngineers

#include "rhal_base.h"

/**
 * @brief Performs an element-wise addition of two 128-bit vectors of 32-bit unsigned integers and returns the high half of each sum.
 * 
 * This function performs an element-wise addition of two 32-bit unsigned integer vectors (`a` and `b`), 
 * each containing eight elements. After the addition, the most significant 16 bits (high half) of each 
 * 32-bit result are extracted to form the output vector. This process is referred to as a "narrowing" operation, 
 * as it reduces the 32-bit result to 16 bits. The function is analogous to the ARM Neon function `vaddhn_u32`, 
 * where the result is a new vector containing the higher 16 bits of the sum of each pair of elements from the input vectors.
 * 
 * @param a The first input vector of type uint32x4_t containing 32-bit unsigned integers.
 * @param b The second input vector of type uint32x4_t containing 32-bit unsigned integers.
 * @return uint16x4_t The narrowed result of the element-wise addition, where each element is an 16-bit unsigned integer 
 * extracted from the most significant half of the corresponding 32-bit sum.
 */
uint16x4_t vaddhn_u32_rvv(uint32x4_t a, uint32x4_t b) {
    return __riscv_vlmul_ext_v_u16mf2_u16m1(__riscv_vnsrl_wx_u16mf2(__riscv_vadd_vv_u32m1(a, b, VLEN_4), 16, VLEN_4));
}
