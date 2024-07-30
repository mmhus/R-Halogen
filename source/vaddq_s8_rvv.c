// Copyright 2024 10xEngineers

#include "rhal_base.h"

/**
 * @brief Adds two 128-bit vectors of 8-bit signed integers element-wise.
 * 
 * This function performs an element-wise addition of two 8-bit signed integer vectors (`a` and `b`), 
 * each containing sixteen elements. It utilizes the RISC-V Vector Extension to carry out the operation, 
 * making it analogous to the ARM Neon function `vaddq_s8`. The result is a new vector where each element 
 * is the sum of the corresponding elements in the input vectors.
 * 
 * @param a The first input vector of type int8x16_t containing 8-bit signed integers.
 * @param b The second input vector of type int8x16_t containing 8-bit signed integers.
 * @return int8x16_t The result of the element-wise addition, returned as an 8-bit signed integer vector.
 */
int8x16_t vaddq_s8_rvv(int8x16_t a, int8x16_t b) {
    return __riscv_vadd_vv_i8m1(a, b, VLEN_16);
}
