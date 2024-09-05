// Copyright 2024 10xEngineers

#include "rhal_base.h"

/**
 * @brief Performs a widening element-wise addition of an 16-bit signed integer vector to a 32-bit signed integer vector.
 * 
 * This function adds an 16-bit signed integer vector (`b`) to a 32-bit signed integer vector (`a`), where the elements
 * of the 16-bit vector are sign-extended (widened) to 32-bit before performing the addition. It utilizes the ARM NEON
 * intrinsic `vaddw_s16` to carry out the operation. The result is a new vector where each 32-bit element in the input 
 * vector `a` is incremented by the corresponding 16-bit element from vector `b`, which is first widened to 32-bit.
 * 
 * This function is useful in scenarios where precision is needed, as it prevents overflow by widening the 16-bit values 
 * before addition.
 * 
 * @param a The first input vector of type int32x4_t containing 32-bit signed integers.
 * @param b The second input vector of type int16x4_t containing 16-bit signed integers.
 * @return int32x4_t The result of the element-wise addition, returned as a vector of 32-bit signed integers.
 */
int32x4_t vaddw_s16_rvv(int32x4_t a, int16x4_t b) {
    return __riscv_vadd_vv_i32m1(a , __riscv_vlmul_trunc_v_i32m2_i32m1(__riscv_vwadd_vx_i32m2(b, 0, VLEN_4)), VLEN_4);
}
