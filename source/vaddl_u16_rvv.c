// Copyright 2024 10xEngineers

#include "rhal_base.h"

/**
 * @brief Performs an element-wise addition of two 16-bit unsigned integer vectors with widening.
 * 
 * This function adds two vectors of 16-bit unsigned integers (`a` and `b`), each containing four elements, 
 * and widens the result to 32-bit unsigned integers. It utilizes the RISC-V Vector Extension to carry out 
 * the operation, making it analogous to the ARM Neon function `vaddl_u16`. The result is a new vector 
 * where each element is the sum of the corresponding elements in the input vectors, with the results 
 * stored in a 32-bit unsigned integer vector to handle potential overflow from the addition.
 * 
 * @param a The first input vector of type uint16x4_t containing 16-bit unsigned integers.
 * @param b The second input vector of type uint16x4_t containing 16-bit unsigned integers.
 * @return uint32x4_t The result of the element-wise addition, returned as a vector of 32-bit unsigned integers.
 */
uint32x4_t vaddl_u16_rvv(uint16x4_t a, uint16x4_t b) {
    return __riscv_vlmul_trunc_v_u32m2_u32m1(__riscv_vwaddu_vv_u32m2(a, b, VLEN_4));
}
