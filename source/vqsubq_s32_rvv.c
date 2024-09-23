// Copyright 2024 10xEngineers

#include "rhal_base.h"

/**
 * @brief Performs an element-wise signed saturating subtraction of two 128-bit vectors of 32-bit signed integers.
 * 
 * This function performs an element-wise subtraction of two 32-bit signed integer vectors (`a` and `b`), 
 * each containing four elements. If the result of the subtraction exceeds the range of an 32-bit signed integer 
 * (-2147483648 to 2147483647), the result is saturated to the nearest boundary (either -2147483648 or 2147483647). It utilizes 
 * the RISC-V Vector Extension to carry out the operation, making it analogous to the ARM Neon function `vqsubq_s32`. 
 * The result is a new vector where each element is the saturating difference of the corresponding elements in the input vectors.
 * 
 * @param a The first input vector of type int32x4_t containing 32-bit signed integers.
 * @param b The second input vector of type int32x4_t containing 32-bit signed integers.
 * @return int32x4_t The result of the element-wise saturating subtraction, returned as an 32-bit signed integer vector.
 */
int32x4_t vqsubq_s32_rvv(int32x4_t a, int32x4_t b) {
    return __riscv_vssub_vv_i32m1(a, b, VLEN_4);
}
