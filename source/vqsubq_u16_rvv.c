// Copyright 2024 10xEngineers

#include "rhal_base.h"

/**
 * @brief Performs an element-wise unsigned saturating subtraction of two 128-bit vectors of 16-bit unsigned integers.
 * 
 * This function performs an element-wise subtraction of two 16-bit unsigned integer vectors (`a` and `b`), 
 * each containing eight elements. If the result of the subtraction exceeds the range of an 16-bit unsigned integer 
 * (0 to 65535), the result is saturated to the nearest boundary (either 0 or 65535). It utilizes the RISC-V 
 * Vector Extension to carry out the operation, making it analogous to the ARM Neon function `vqsubq_u16`. 
 * The result is a new vector where each element is the saturating difference of the corresponding elements in the input vectors.
 * 
 * @param a The first input vector of type uint16x8_t containing 16-bit unsigned integers.
 * @param b The second input vector of type uint16x8_t containing 16-bit unsigned integers.
 * @return uint16x8_t The result of the element-wise saturating subtraction, returned as an 16-bit unsigned integer vector.
 */
uint16x8_t vqsubq_u16_rvv(uint16x8_t a, uint16x8_t b) {
    return __riscv_vssubu_vv_u16m1(a, b, VLEN_8);
}
