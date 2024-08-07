// Copyright 2024 10xEngineers

#include "rhal_base.h"

/**
 * @brief Subtracts two 64-bit vectors of 64-bit signed integer element-wise.
 * 
 * This function performs an element-wise subtraction of two 64-bit signed integer vectors (`a` and `b`), 
 * each containing one element. It utilizes the RISC-V Vector Extension to carry out the operation, 
 * making it analogous to the ARM Neon function `vsub_s64`. The result is a new vector where each element 
 * is the difference of the corresponding elements in the input vectors.
 * 
 * @param a The first input vector of type int64x1_t containing 64-bit signed integers.
 * @param b The second input vector of type int64x1_t containing 64-bit signed integers.
 * @return int64x1_t The result of the element-wise subtraction, returned as an 64-bit signed integer vector.
 */
int64x1_t vsub_s64_rvv(int64x1_t a, int64x1_t b) {
    return __riscv_vsub_vv_i64m1(a, b, VLEN_1);
}
