// Copyright 2024 10xEngineers

#include "rhal_base.h"

/**
 * @brief Performs an element-wise signed saturating subtraction of two 128-bit vectors of 8-bit signed integers.
 * 
 * This function performs an element-wise subtraction of two 8-bit signed integer vectors (`a` and `b`), 
 * each containing sixteen elements. If the result of the subtraction exceeds the range of an 8-bit signed integer 
 * (-128 to 127), the result is saturated to the nearest boundary (either -128 or 127). It utilizes the RISC-V 
 * Vector Extension to carry out the operation, making it analogous to the ARM Neon function `vqsubq_s8`. 
 * The result is a new vector where each element is the saturating difference of the corresponding elements in the input vectors.
 * 
 * @param a The first input vector of type int8x16_t containing 8-bit signed integers.
 * @param b The second input vector of type int8x16_t containing 8-bit signed integers.
 * @return int8x16_t The result of the element-wise saturating subtraction, returned as an 8-bit signed integer vector.
 */
int8x16_t vqsubq_s8_rvv(int8x16_t a, int8x16_t b) {
    return __riscv_vssub_vv_i8m1(a, b, VLEN_16);
}
