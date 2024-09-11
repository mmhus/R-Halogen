// Copyright 2024 10xEngineers

#include "rhal_base.h"

/**
 * @brief Performs an element-wise rounding halving addition of two 128-bit vectors of 16-bit unsigned integers.
 * 
 * This function performs an element-wise addition of two 128-bit vectors (`a` and `b`), each containing 
 * sixteen 16-bit unsigned integer elements. After adding the corresponding elements from both vectors, 
 * it halves the result by shifting the sum of each pair of elements to the right by 1 bit. Before halving, 
 * rounding is applied by adding 1 to the sum, ensuring that the result is more accurate when the sum 
 * is an odd number. The function is analogous to the ARM Neon intrinsic `vrhaddq_u16`. The result is a new 
 * 128-bit vector where each element is the rounded and halved sum of the corresponding elements in the input
 * vectors, stored as 16-bit unsigned integers.
 * 
 * @param a The first input vector of type uint16x8_t containing 16 elements of 16-bit unsigned integers.
 * @param b The second input vector of type uint16x8_t containing 16 elements of 16-bit unsigned integers.
 * @return uint16x8_t The result of the rounding halving addition, returned as a 128-bit vector of 16-bit unsigned integers.
 */
uint16x8_t vrhaddq_u16_rvv(uint16x8_t a, uint16x8_t b) {
    return __riscv_vaaddu_vv_u16m1(a, b, VLEN_8);
}
