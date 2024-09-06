// Copyright 2024 10xEngineers

#include "rhal_base.h"

/**
 * @brief Performs an element-wise halving subtraction of two 128-bit vectors of 16-bit signed integers.
 * 
 * This function performs an element-wise subtraction of two 128-bit vectors (`a` and `b`), 
 * each containing eight 16-bit signed integer elements, and then halves the result by shifting 
 * the difference of each pair of elements to the right by 1 bit. It utilizes the RISC-V Vector Extension 
 * to carry out the operation, making it analogous to the ARM Neon function `vhsubq_s16`. 
 * The result is a new vector where each element is the halved difference of the corresponding elements 
 * in the input vectors, with the result stored as 16-bit signed integers.
 * 
 * @param a The first input vector of type int16x8_t containing eight 16-bit signed integers.
 * @param b The second input vector of type int16x8_t containing eight 16-bit signed integers.
 * @return int16x8_t The result of the halving subtraction, returned as a 128-bit vector of eight 16-bit signed integers.
 */
int16x8_t vhsubq_s16_rvv(int16x8_t a, int16x8_t b) {
    return __riscv_vnsra_wx_i16m1( __riscv_vwsub_vv_i32m2(a, b, VLEN_8), 1, VLEN_8);
}
