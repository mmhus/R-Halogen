// Copyright 2024 10xEngineers

#include "rhal_base.h"

/**
 * @brief Performs an element-wise signed saturating addition of two 64-bit vectors of 64-bit signed integers.
 * 
 * This function performs an element-wise addition of two 64-bit signed integer vectors (`a` and `b`), 
 * each containing one elements. If the result of the addition exceeds the range of an 64-bit signed integer 
 * (-9223372036854775808 to 9223372036854775807), the result is saturated to the nearest boundary (either -9223372036854775808 or 9223372036854775807). 
 * It utilizes the RISC-V Vector Extension to carry out the operation, making it analogous to the ARM Neon function `vqadd_s64`. 
 * The result is a new vector where each element is the saturating sum of the corresponding elements in the input vectors.
 * 
 * @param a The first input vector of type int64x1_t containing 64-bit signed integers.
 * @param b The second input vector of type int64x1_t containing 64-bit signed integers.
 * @return int64x1_t The result of the element-wise saturating addition, returned as an 64-bit signed integer vector.
 */
int64x1_t vqadd_s64_rvv(int64x1_t a, int64x1_t b) {
    return __riscv_vsadd_vv_i64m1(a, b, VLEN_1);
}
