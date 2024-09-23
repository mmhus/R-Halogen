// Copyright 2024 10xEngineers

#include "rhal_base.h"

/**
 * @brief Performs an element-wise halving subtraction of two 128-bit vectors of 16-bit unsigned integers.
 * 
 * This function performs an element-wise subtraction of two 128-bit vectors (`a` and `b`), 
 * each containing eight 16-bit unsigned integer elements, and then halves the result by shifting 
 * the difference of each pair of elements to the right by 1 bit. It utilizes the RISC-V Vector Extension 
 * to carry out the operation, making it analogous to the ARM Neon function `vhsubq_u16`. 
 * The result is a new vector where each element is the halved difference of the corresponding elements 
 * in the input vectors, with the result stored as 16-bit unsigned integers.
 * 
 * @param a The first input vector of type uint16x8_t containing eight 16-bit unsigned integers.
 * @param b The second input vector of type uint16x8_t containing eight 16-bit unsigned integers.
 * @return uint16x8_t The result of the halving subtraction, returned as a 128-bit vector of eight 16-bit unsigned integers.
 */
uint16x8_t vhsubq_u16_rvv(uint16x8_t a, uint16x8_t b) {
    return __riscv_vnsrl_wx_u16m1( __riscv_vwsubu_vv_u32m2(a, b, VLEN_8), 1, VLEN_8);
}
