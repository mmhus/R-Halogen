// Copyright 2024 10xEngineers

#include "rhal_base.h"

/**
 * @brief Performs an element-wise subtraction of two 8-bit unsigned integer vectors with widening.
 * 
 * This function subs two vectors of 8-bit unsigned integers (`a` and `b`), each containing eight elements, 
 * and widens the result to 16-bit unsigned integers. It utilizes the RISC-V Vector Extension to carry out 
 * the operation, making it analogous to the ARM Neon function `vsubl_u8`. The result is a new vector 
 * where each element is the difference of the corresponding elements in the input vectors, with the results 
 * stored in a 16-bit unsigned integer vector to handle potential overflow from the subtraction.
 * 
 * @param a The first input vector of type uint8x8_t containing 8-bit unsigned integers.
 * @param b The second input vector of type uint8x8_t containing 8-bit unsigned integers.
 * @return uint16x8_t The result of the element-wise subtraction, returned as a vector of 16-bit unsigned integers.
 */
uint16x8_t vsubl_u8_rvv(uint8x8_t a, uint8x8_t b) {
    return __riscv_vlmul_trunc_v_u16m2_u16m1(__riscv_vwsubu_vv_u16m2(a, b, VLEN_8));
}
