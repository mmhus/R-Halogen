// Copyright 2024 10xEngineers

#include "rhal_base.h"

/**
 * @brief Performs an element-wise halving addition of two 8-bit signed integer vectors.
 * 
 * This function performs an element-wise addition of two 8-bit signed integer vectors (`a` and `b`),
 * each containing eight elements, and then halves the result by shifting the sum of each pair of elements 
 * to the right by 1 bit. It utilizes the RISC-V Vector Extension to carry out the operation, making it 
 * analogous to the ARM Neon function `vhadd_s8`. The result is a new vector where each element is 
 * the halved sum of the corresponding elements in the input vectors, with the result stored as 
 * 8-bit signed integers.
 * 
 * @param a The first input vector of type int8x8_t containing 8-bit signed integers.
 * @param b The second input vector of type int8x8_t containing 8-bit signed integers.
 * @return int8x8_t The result of the halving addition, returned as an 8-bit signed integer vector.
 */
int8x8_t vhadd_s8_rvv(int8x8_t a, int8x8_t b) {
    return __riscv_vnsra_wx_i8m1( __riscv_vwadd_vv_i16m2(a, b, VLEN_8), 1, VLEN_8);
}
