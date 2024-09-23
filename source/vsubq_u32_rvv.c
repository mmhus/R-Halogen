// Copyright 2024 10xEngineers

#include "rhal_base.h"

/**
 * @brief Subtracts two 128-bit vectors of 32-bit unsigned integers element-wise.
 * 
 * This function performs an element-wise subtraction of two 32-bit unsigned integer vectors (`a` and `b`), 
 * each containing four elements. It utilizes the RISC-V Vector Extension to carry out the operation, 
 * making it analogous to the ARM Neon function `vsubq_u32`. The result is a new vector where each element 
 * is the difference of the corresponding elements in the input vectors.
 * 
 * @param a The first input vector of type uint32x4_t containing 32-bit unsigned integers.
 * @param b The second input vector of type uint32x4_t containing 32-bit unsigned integers.
 * @return uint32x4_t The result of the element-wise subtraction, returned as an 32-bit unsigned integer vector.
 */
uint32x4_t vsubq_u32_rvv(uint32x4_t a, uint32x4_t b) {
    return __riscv_vsub_vv_u32m1(a, b, VLEN_4);
}
