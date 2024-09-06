// Copyright 2024 10xEngineers

#include "rhal_base.h"

/**
 * @brief Performs an element-wise halving subtraction of two 8-bit unsigned integer vectors.
 * 
 * This function performs an element-wise subtraction of two 8-bit unsigned integer vectors (`a` and `b`),
 * each containing eight elements, and then halves the result by shifting the difference of each pair of elements 
 * to the right by 1 bit. It utilizes the RISC-V Vector Extension to carry out the operation, making it 
 * analogous to the ARM Neon function `vhsub_u8`. The result is a new vector where each element is 
 * the halved difference of the corresponding elements in the input vectors, with the result stored as 
 * 8-bit unsigned integers.
 * 
 * @param a The first input vector of type uint8x8_t containing 8-bit unsigned integers.
 * @param b The second input vector of type uint8x8_t containing 8-bit unsigned integers.
 * @return uint8x8_t The result of the halving subtraction, returned as an 8-bit unsigned integer vector.
 */
uint8x8_t vhsub_u8_rvv(uint8x8_t a, uint8x8_t b) {
    return __riscv_vnsrl_wx_u8m1( __riscv_vwsubu_vv_u16m2(a, b, VLEN_8), 1, VLEN_8);
}
