// Copyright 2024 10xEngineers

#include "rhal_base.h"

/**
 * @brief Performs an element-wise signed saturating subtraction of two 128-bit vectors of 16-bit signed integers.
 * 
 * This function performs an element-wise subtraction of two 16-bit signed integer vectors (`a` and `b`), 
 * each containing eight elements. If the result of the subtraction exceeds the range of an 16-bit signed integer 
 * (-32768 to 32767), the result is saturated to the nearest boundary (either -32768 or 32767). It utilizes the RISC-V 
 * Vector Extension to carry out the operation, making it analogous to the ARM Neon function `vqsubq_s16`. 
 * The result is a new vector where each element is the saturating difference of the corresponding elements in the input vectors.
 * 
 * @param a The first input vector of type int16x8_t containing 16-bit signed integers.
 * @param b The second input vector of type int16x8_t containing 16-bit signed integers.
 * @return int16x8_t The result of the element-wise saturating subtraction, returned as an 16-bit signed integer vector.
 */
int16x8_t vqsubq_s16_rvv(int16x8_t a, int16x8_t b) {
    return __riscv_vssub_vv_i16m1(a, b, VLEN_8);
}
