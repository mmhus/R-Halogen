// Copyright 2024 10xEngineers

#include "rhal_base.h"

/**
 * @brief Performs an element-wise unsigned saturating subtraction of two 64-bit vectors of 8-bit unsigned integers.
 * 
 * This function performs an element-wise subtraction of two 8-bit unsigned integer vectors (`a` and `b`), 
 * each containing eight elements. If the result of the subtraction exceeds the range of an 8-bit unsigned integer 
 * (0 to 255), the result is saturated to the nearest boundary (either 0 or 255). It utilizes the RISC-V 
 * Vector Extension to carry out the operation, making it analogous to the ARM Neon function `vqsub_u8`. 
 * The result is a new vector where each element is the saturating difference of the corresponding elements in the input vectors.
 * 
 * @param a The first input vector of type uint8x8_t containing 8-bit unsigned integers.
 * @param b The second input vector of type uint8x8_t containing 8-bit unsigned integers.
 * @return uint8x8_t The result of the element-wise saturating subtraction, returned as an 8-bit unsigned integer vector.
 */
uint8x8_t vqsub_u8_rvv(uint8x8_t a, uint8x8_t b) {
    return __riscv_vssubu_vv_u8m1(a, b, VLEN_8);
}
