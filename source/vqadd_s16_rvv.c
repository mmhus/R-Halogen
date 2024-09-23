// Copyright 2024 10xEngineers

#include "rhal_base.h"

/**
 * @brief Performs an element-wise signed saturating addition of two 64-bit vectors of 16-bit signed integers.
 * 
 * This function performs an element-wise addition of two 16-bit signed integer vectors (`a` and `b`), 
 * each containing four elements. If the result of the addition exceeds the range of an 16-bit signed integer 
 * (-32768 to 32767), the result is saturated to the nearest boundary (either -32768 or 32767). It utilizes the RISC-V 
 * Vector Extension to carry out the operation, making it analogous to the ARM Neon function `vqadd_s16`. 
 * The result is a new vector where each element is the saturating sum of the corresponding elements in the input vectors.
 * 
 * @param a The first input vector of type int16x4_t containing 16-bit signed integers.
 * @param b The second input vector of type int16x4_t containing 16-bit signed integers.
 * @return int16x4_t The result of the element-wise saturating addition, returned as an 16-bit signed integer vector.
 */
int16x4_t vqadd_s16_rvv(int16x4_t a, int16x4_t b) {
    return __riscv_vsadd_vv_i16m1(a, b, VLEN_4);
}
