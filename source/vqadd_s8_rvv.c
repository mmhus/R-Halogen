// Copyright 2024 10xEngineers

#include "rhal_base.h"

/**
 * @brief Performs an element-wise signed saturating addition of two 64-bit vectors of 8-bit signed integers.
 * 
 * This function performs an element-wise addition of two 8-bit signed integer vectors (`a` and `b`), 
 * each containing eight elements. If the result of the addition exceeds the range of an 8-bit signed integer 
 * (-128 to 127), the result is saturated to the nearest boundary (either -128 or 127). It utilizes the RISC-V 
 * Vector Extension to carry out the operation, making it analogous to the ARM Neon function `vqadd_s8`. 
 * The result is a new vector where each element is the saturating sum of the corresponding elements in the input vectors.
 * 
 * @param a The first input vector of type int8x8_t containing 8-bit signed integers.
 * @param b The second input vector of type int8x8_t containing 8-bit signed integers.
 * @return int8x8_t The result of the element-wise saturating addition, returned as an 8-bit signed integer vector.
 */
int8x8_t vqadd_s8_rvv(int8x8_t a, int8x8_t b) {
    return __riscv_vsadd_vv_i8m1(a, b, VLEN_8);
}
