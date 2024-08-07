// Copyright 2024 10xEngineers

#include "rhal_base.h"

/**
 * @brief Subtracts two 64-bit vectors of 8-bit signed integers element-wise.
 * 
 * This function performs an element-wise subtraction of two 8-bit signed integer vectors (`a` and `b`), 
 * each containing four elements. It utilizes the RISC-V Vector Extension to carry out the operation, 
 * making it analogous to the ARM Neon function `vsub_s8`. The result is a new vector where each element 
 * is the difference of the corresponding elements in the input vectors.
 * 
 * @param a The first input vector of type int16x4_t containing 8-bit signed integers.
 * @param b The second input vector of type int16x4_t containing 8-bit signed integers.
 * @return int8x8_t The result of the element-wise subtraction, returned as an 8-bit signed integer vector.
 */

int8x8_t vsub_s8_rvv(int8x8_t a, int8x8_t b) {
    return __riscv_vsub_vv_i8m1(a, b, VLEN_8);
}
