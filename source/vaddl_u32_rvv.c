// Copyright 2024 10xEngineers

#include "rhal_base.h"

/**
 * @brief Performs an element-wise addition of two 32-bit unsigned integer vectors with widening.
 * 
 * This function adds two vectors of 32-bit unsigned integers (`a` and `b`), each containing two elements, 
 * and widens the result to 64-bit unsigned integers. It utilizes the RISC-V Vector Extension to carry out 
 * the operation, making it analogous to the ARM Neon function `vaddl_u32`. The result is a new vector 
 * where each element is the sum of the corresponding elements in the input vectors, with the results 
 * stored in a 64-bit unsigned integer vector to handle potential overflow from the addition.
 * 
 * @param a The first input vector of type uint32x2_t containing 32-bit unsigned integers.
 * @param b The second input vector of type uint32x2_t containing 32-bit unsigned integers.
 * @return uint64x2_t The result of the element-wise addition, returned as a vector of 64-bit unsigned integers.
 */
uint64x2_t vaddl_u32_rvv(uint32x2_t a, uint32x2_t b) {
    return __riscv_vlmul_trunc_v_u64m2_u64m1(__riscv_vwaddu_vv_u64m2(a, b, VLEN_2));
}
