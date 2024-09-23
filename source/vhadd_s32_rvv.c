// Copyright 2024 10xEngineers

#include "rhal_base.h"

/**
 * @brief Performs an element-wise halving addition of two 32-bit signed integer vectors.
 * 
 * This function performs an element-wise addition of two 32-bit signed integer vectors (`a` and `b`),
 * each containing two elements, and then halves the result by shifting the sum of each pair of elements 
 * to the right by 1 bit. It utilizes the RISC-V Vector Extension to carry out the operation, making it 
 * analogous to the ARM Neon function `vhadd_s32`. The result is a new vector where each element is 
 * the halved sum of the corresponding elements in the input vectors, with the result stored as 
 * 32-bit signed integers.
 * 
 * @param a The first input vector of type int32x2_t containing 32-bit signed integers.
 * @param b The second input vector of type int32x2_t containing 32-bit signed integers.
 * @return int32x2_t The result of the halving addition, returned as an 32-bit signed integer vector.
 */
int32x2_t vhadd_s32_rvv(int32x2_t a, int32x2_t b) {
    return __riscv_vnsra_wx_i32m1( __riscv_vwadd_vv_i64m2(a, b, VLEN_2), 1, VLEN_2);
}