// Copyright 2024 10xEngineers

#include "rhal_base.h"

/**
 * @brief Performs an element-wise halving addition of two 128-bit vectors of 8-bit signed integers.
 * 
 * This function performs an element-wise addition of two 128-bit vectors (`a` and `b`), 
 * each containing sixteen 8-bit signed integer elements, and then halves the result by shifting 
 * the sum of each pair of elements to the right by 1 bit. It utilizes the RISC-V Vector Extension 
 * to carry out the operation, making it analogous to the ARM Neon function `vhaddq_s8`. 
 * The result is a new vector where each element is the halved sum of the corresponding elements 
 * in the input vectors, with the result stored as 8-bit signed integers.
 * 
 * @param a The first input vector of type int8x16_t containing sixteen 8-bit signed integers.
 * @param b The second input vector of type int8x16_t containing sixteen 8-bit signed integers.
 * @return int8x16_t The result of the halving addition, returned as a 128-bit vector of sixteen 8-bit signed integers.
 */
int8x16_t vhaddq_s8_rvv(int8x16_t a, int8x16_t b) {
    return __riscv_vnsra_wx_i8m1( __riscv_vwadd_vv_i16m2(a, b, VLEN_16), 1, VLEN_16);
}
