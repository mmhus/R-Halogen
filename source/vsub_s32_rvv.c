// Copyright 2024 10xEngineers

#include "rhal_base.h"

/**
 * @brief Subtracts two 64-bit vectors of 32-bit signed integers element-wise.
 * 
 * This function performs an element-wise subtraction of two 32-bit signed integer vectors (`a` and `b`), 
 * each containing two elements. It utilizes the RISC-V Vector Extension to carry out the operation, 
 * making it analogous to the ARM Neon function `vsub_s32`. The result is a new vector where each element 
 * is the difference of the corresponding elements in the input vectors.
 * 
 * @param a The first input vector of type int32x2_t containing 32-bit signed integers.
 * @param b The second input vector of type int32x2_t containing 32-bit signed integers.
 * @return int32x2_t The result of the element-wise subtraction, returned as an 32-bit signed integer vector.
 */
int32x2_t vsub_s32_rvv(int32x2_t a, int32x2_t b) {
    return __riscv_vsub_vv_i32m1(a, b, VLEN_2);
}
