// Copyright 2024 10xEngineers

#include "rhal_base.h"

/**
 * @brief Performs an element-wise addition of two 8-bit signed integer vectors with widening.
 * 
 * This function adds two vectors of 8-bit signed integers (`a` and `b`), each containing eight elements, 
 * and widens the result to 16-bit signed integers. It utilizes the RISC-V Vector Extension to carry out 
 * the operation, making it analogous to the ARM Neon function `vaddl_s8`. The result is a new vector 
 * where each element is the sum of the corresponding elements in the input vectors, with the results 
 * stored in a 16-bit signed integer vector to handle potential overflow from the addition.
 * 
 * @param a The first input vector of type int8x8_t containing 8-bit signed integers.
 * @param b The second input vector of type int8x8_t containing 8-bit signed integers.
 * @return int16x8_t The result of the element-wise addition, returned as a vector of 16-bit signed integers.
 */
int16x8_t vaddl_s8_rvv(int8x8_t a, int8x8_t b) {
    return __riscv_vlmul_trunc_v_i16m2_i16m1(__riscv_vwadd_vv_i16m2(a, b, VLEN_8));
}