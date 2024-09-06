// Copyright 2024 10xEngineers

#include "rhal_base.h"

/**
 * @brief Performs an element-wise addition of two 16-bit signed integer vectors with widening.
 * 
 * This function adds two vectors of 16-bit signed integers (`a` and `b`), each containing four elements, 
 * and widens the result to 32-bit signed integers. It utilizes the RISC-V Vector Extension to carry out 
 * the operation, making it analogous to the ARM Neon function `vaddl_s16`. The result is a new vector 
 * where each element is the sum of the corresponding elements in the input vectors, with the results 
 * stored in a 32-bit signed integer vector to handle potential overflow from the addition.
 * 
 * @param a The first input vector of type int16x4_t containing 16-bit signed integers.
 * @param b The second input vector of type int16x4_t containing 16-bit signed integers.
 * @return int32x4_t The result of the element-wise addition, returned as a vector of 32-bit signed integers.
 */
int32x4_t vaddl_s16_rvv(int16x4_t a, int16x4_t b) {
    return __riscv_vlmul_trunc_v_i32m2_i32m1(__riscv_vwadd_vv_i32m2(a, b, VLEN_4));
}