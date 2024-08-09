// Copyright 2024 10xEngineers

#include "rhal_base.h"

/**
 * @brief Adds two 128-bit vectors of 32-bit signed integers element-wise.
 * 
 * This function performs an element-wise addition of two 32-bit signed integer vectors (`a` and `b`), 
 * each containing four elements. It utilizes the RISC-V Vector Extension to carry out the operation, 
 * making it analogous to the ARM Neon function `vaddq_s32`. The result is a new vector where each element 
 * is the sum of the corresponding elements in the input vectors.
 * 
 * @param a The first input vector of type int32x4_t containing 32-bit signed integers.
 * @param b The second input vector of type int32x4_t containing 32-bit signed integers.
 * @return int32x4_t The result of the element-wise addition, returned as an 32-bit signed integer vector.
 */
int32x4_t vaddq_s32_rvv(int32x4_t a, int32x4_t b) {
    return __riscv_vadd_vv_i32m1(a, b, VLEN_4);
}
