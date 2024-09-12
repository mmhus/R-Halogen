// Copyright 2024 10xEngineers

#include "rhal_base.h"

/**
 * @brief Performs an element-wise signed saturating addition of two 64-bit vectors of 32-bit signed integers.
 * 
 * This function performs an element-wise addition of two 32-bit signed integer vectors (`a` and `b`), 
 * each containing two elements. If the result of the addition exceeds the range of an 32-bit signed integer 
 * (-2147483648 to 2147483647), the result is saturated to the nearest boundary (either -2147483648 or 2147483647). It utilizes 
 * the RISC-V Vector Extension to carry out the operation, making it analogous to the ARM Neon function `vqadd_s32`. 
 * The result is a new vector where each element is the saturating sum of the corresponding elements in the input vectors.
 * 
 * @param a The first input vector of type int32x2_t containing 32-bit signed integers.
 * @param b The second input vector of type int32x2_t containing 32-bit signed integers.
 * @return int32x2_t The result of the element-wise saturating addition, returned as an 32-bit signed integer vector.
 */
int32x2_t vqadd_s32_rvv(int32x2_t a, int32x2_t b) {
    return __riscv_vsadd_vv_i32m1(a, b, VLEN_2);
}
