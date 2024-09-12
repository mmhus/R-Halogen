// Copyright 2024 10xEngineers

#include "rhal_base.h"

/**
 * @brief Performs an element-wise unsigned saturating addition of two 64-bit vectors of 64-bit unsigned integers.
 * 
 * This function performs an element-wise addition of two 64-bit unsigned integer vectors (`a` and `b`), 
 * each containing one elements. If the result of the addition exceeds the range of an 64-bit unsigned integer 
 * (0 to 18446744073709551615), the result is saturated to the nearest boundary (either 0 or 18446744073709551615). It 
 * utilizes the RISC-V Vector Extension to carry out the operation, making it analogous to the ARM Neon function `vqadd_u64`. 
 * The result is a new vector where each element is the saturating sum of the corresponding elements in the input vectors.
 * 
 * @param a The first input vector of type uint64x1_t containing 64-bit unsigned integers.
 * @param b The second input vector of type uint64x1_t containing 64-bit unsigned integers.
 * @return uint64x1_t The result of the element-wise saturating addition, returned as an 64-bit unsigned integer vector.
 */
uint64x1_t vqadd_u64_rvv(uint64x1_t a, uint64x1_t b) {
    return __riscv_vsaddu_vv_u64m1(a, b, VLEN_1);
}
