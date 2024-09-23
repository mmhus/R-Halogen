// Copyright 2024 10xEngineers

#include "rhal_base.h"

/**
 * @brief Performs an element-wise signed saturating subtraction of two 128-bit vectors of 64-bit signed integers.
 * 
 * This function performs an element-wise subtraction of two 64-bit signed integer vectors (`a` and `b`), 
 * each containing two elements. If the result of the subtraction exceeds the range of an 64-bit signed integer 
 * (-9223372036854775808 to 9223372036854775807), the result is saturated to the nearest boundary (either -9223372036854775808 or 9223372036854775807). 
 * It utilizes the RISC-V Vector Extension to carry out the operation, making it analogous to the ARM Neon function `vqsubq_s64`. 
 * The result is a new vector where each element is the saturating difference of the corresponding elements in the input vectors.
 * 
 * @param a The first input vector of type int64x2_t containing 64-bit signed integers.
 * @param b The second input vector of type int64x2_t containing 64-bit signed integers.
 * @return int64x2_t The result of the element-wise saturating subtraction, returned as an 64-bit signed integer vector.
 */
int64x2_t vqsubq_s64_rvv(int64x2_t a, int64x2_t b) {
    return __riscv_vssub_vv_i64m1(a, b, VLEN_2);
}
