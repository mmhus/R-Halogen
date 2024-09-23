// Copyright 2024 10xEngineers

#include "rhal_base.h"

/**
 * @brief Performs a widening element-wise subtraction of an 32-bit signed integer vector to a 64-bit signed integer vector.
 * 
 * This function subs an 32-bit signed integer vector (`b`) to a 64-bit signed integer vector (`a`), where the elements
 * of the 32-bit vector are sign-extended (widened) to 64-bit before performing the subtraction. It utilizes the ARM NEON
 * intrinsic `vsubw_s32` to carry out the operation. The result is a new vector where each 64-bit element in the input 
 * vector `a` is incremented by the corresponding 32-bit element from vector `b`, which is first widened to 64-bit.
 * 
 * This function is useful in scenarios where precision is needed, as it prevents overflow by widening the 32-bit values 
 * before subtraction.
 * 
 * @param a The first input vector of type int64x2_t containing 64-bit signed integers.
 * @param b The second input vector of type int32x2_t containing 32-bit signed integers.
 * @return int64x2_t The result of the element-wise subtraction, returned as a vector of 64-bit signed integers.
 */
int64x2_t vsubw_s32_rvv(int64x2_t a, int32x2_t b) {
    return __riscv_vsub_vv_i64m1(a , __riscv_vlmul_trunc_v_i64m2_i64m1(__riscv_vwsub_vx_i64m2(b, 0, VLEN_2)), VLEN_2);
}
