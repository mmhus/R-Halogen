// Copyright 2024 10xEngineers

#include "rhal_base.h"

/**
 * @brief Performs a widening element-wise addition of an 8-bit unsigned integer vector to a 16-bit unsigned integer vector.
 * 
 * This function adds an 8-bit unsigned integer vector (`b`) to a 16-bit unsigned integer vector (`a`), where the elements
 * of the 8-bit vector are sign-extended (widened) to 16-bit before performing the addition. It utilizes the ARM NEON
 * intrinsic `vaddw_u8` to carry out the operation. The result is a new vector where each 16-bit element in the input 
 * vector `a` is incremented by the corresponding 8-bit element from vector `b`, which is first widened to 16-bit.
 * 
 * This function is useful in scenarios where precision is needed, as it prevents overflow by widening the 8-bit values 
 * before addition.
 * 
 * @param a The first input vector of type uint16x8_t containing 16-bit unsigned integers.
 * @param b The second input vector of type uint8x8_t containing 8-bit unsigned integers.
 * @return int16x8_t The result of the element-wise addition, returned as a vector of 16-bit unsigned integers.
 */
uint16x8_t vaddw_u8_rvv(uint16x8_t a, uint8x8_t b) {
    return __riscv_vadd_vv_u16m1(a , __riscv_vlmul_trunc_v_u16m2_u16m1(__riscv_vwaddu_vx_u16m2(b, 0, VLEN_8)), VLEN_8);
}
