// Copyright 2024 10xEngineers

#include "rhal_base.h"

/**
 * @brief Performs an element-wise addition of two 32-bit signed integer vectors with widening.
 * 
 * This function adds two vectors of 32-bit signed integers (`a` and `b`), each containing two elements, 
 * and widens the result to 64-bit signed integers. It utilizes the RISC-V Vector Extension to carry out 
 * the operation, making it analogous to the ARM Neon function `vaddl_s32`. The result is a new vector 
 * where each element is the sum of the corresponding elements in the input vectors, with the results 
 * stored in a 64-bit signed integer vector to handle potential overflow from the addition.
 * 
 * @param a The first input vector of type int32x2_t containing 32-bit signed integers.
 * @param b The second input vector of type int32x2_t containing 32-bit signed integers.
 * @return int64x2_t The result of the element-wise addition, returned as a vector of 64-bit signed integers.
 */
int64x2_t vaddl_s32_rvv(int32x2_t a, int32x2_t b) {
    return __riscv_vlmul_trunc_v_i64m2_i64m1(__riscv_vwadd_vv_i64m2(a, b, VLEN_2));
}
