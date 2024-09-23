// Copyright 2024 10xEngineers

#include "rhal_base.h"

/**
 * @brief Performs an element-wise halving subtraction of two 128-bit vectors of 8-bit unsigned integers.
 * 
 * This function performs an element-wise subtraction of two 128-bit vectors (`a` and `b`), 
 * each containing sixteen 8-bit unsigned integer elements, and then halves the result by shifting 
 * the difference of each pair of elements to the right by 1 bit. It utilizes the RISC-V Vector Extension 
 * to carry out the operation, making it analogous to the ARM Neon function `vhsubq_u8`. 
 * The result is a new vector where each element is the halved difference of the corresponding elements 
 * in the input vectors, with the result stored as 8-bit unsigned integers.
 * 
 * @param a The first input vector of type uint8x16_t containing sixteen 8-bit unsigned integers.
 * @param b The second input vector of type uint8x16_t containing sixteen 8-bit unsigned integers.
 * @return uint8x16_t The result of the halving subtraction, returned as a 128-bit vector of sixteen 8-bit unsigned integers.
 */
uint8x16_t vhsubq_u8_rvv(uint8x16_t a, uint8x16_t b) {
    return __riscv_vnsrl_wx_u8m1( __riscv_vwsubu_vv_u16m2(a, b, VLEN_16), 1, VLEN_16);
}
