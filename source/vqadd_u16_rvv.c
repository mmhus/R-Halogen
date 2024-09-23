// Copyright 2024 10xEngineers

#include "rhal_base.h"

/**
 * @brief Performs an element-wise unsigned saturating addition of two 64-bit vectors of 16-bit unsigned integers.
 * 
 * This function performs an element-wise addition of two 16-bit unsigned integer vectors (`a` and `b`), 
 * each containing four elements. If the result of the addition exceeds the range of an 16-bit unsigned integer 
 * (0 to 65535), the result is saturated to the nearest boundary (either 0 or 65535). It utilizes the RISC-V 
 * Vector Extension to carry out the operation, making it analogous to the ARM Neon function `vqadd_u16`. 
 * The result is a new vector where each element is the saturating sum of the corresponding elements in the input vectors.
 * 
 * @param a The first input vector of type uint16x4_t containing 16-bit unsigned integers.
 * @param b The second input vector of type uint16x4_t containing 16-bit unsigned integers.
 * @return uint16x4_t The result of the element-wise saturating addition, returned as an 16-bit unsigned integer vector.
 */
uint16x4_t vqadd_u16_rvv(uint16x4_t a, uint16x4_t b) {
    return __riscv_vsaddu_vv_u16m1(a, b, VLEN_4);
}
