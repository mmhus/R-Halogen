// Copyright 2024 10xEngineers

#include "rhal_base.h"

/**
 * @brief Performs an element-wise halving subtraction of two 128-bit vectors of 32-bit signed integers.
 * 
 * This function performs an element-wise subtraction of two 128-bit vectors (`a` and `b`), 
 * each containing four 32-bit signed integer elements, and then halves the result by shifting 
 * the difference of each pair of elements to the right by 1 bit. It utilizes the RISC-V Vector Extension 
 * to carry out the operation, making it analogous to the ARM Neon function `vhsubq_s32`. 
 * The result is a new vector where each element is the halved difference of the corresponding elements 
 * in the input vectors, with the result stored as 32-bit signed integers.
 * 
 * @param a The first input vector of type int32x4_t containing four 32-bit signed integers.
 * @param b The second input vector of type int32x4_t containing four 32-bit signed integers.
 * @return int32x4_t The result of the halving subtraction, returned as a 128-bit vector of four 32-bit signed integers.
 */
int32x4_t vhsubq_s32_rvv(int32x4_t a, int32x4_t b) {
    return __riscv_vnsra_wx_i32m1( __riscv_vwsub_vv_i64m2(a, b, VLEN_4), 1, VLEN_4);
}
