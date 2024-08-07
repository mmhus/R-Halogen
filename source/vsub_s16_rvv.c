// Copyright 2024 10xEngineers

#include "rhal_base.h"

/**
 * @brief Subtracts two 64-bit vectors of 16-bit signed integers element-wise.
 * 
 * This function performs an element-wise subtraction of two 16-bit signed integer vectors (`a` and `b`), 
 * each containing four elements. It utilizes the RISC-V Vector Extension to carry out the operation, 
 * making it analogous to the ARM Neon function `vsub_s16`. The result is a new vector where each element 
 * is the difference of the corresponding elements in the input vectors.
 * 
 * @param a The first input vector of type int16x4_t containing 16-bit signed integers.
 * @param b The second input vector of type int16x4_t containing 16-bit signed integers.
 * @return int16x4_t The result of the element-wise subtraction, returned as an 16-bit signed integer vector.
 */
int16x4_t vsub_s16_rvv(int16x4_t a, int16x4_t b) {
    return __riscv_vsub_vv_i16m1(a, b, VLEN_4);
}
