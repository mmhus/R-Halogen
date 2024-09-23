// Copyright 2024 10xEngineers

#include "rhal_base.h"

/**
 * @brief Performs an element-wise rounding halving addition of two 8-bit unsigned integer vectors.
 * 
 * This function performs an element-wise addition of two 8-bit unsigned integer vectors (`a` and `b`),
 * each containing eight elements. After adding the corresponding elements, it halves the sum by shifting 
 * the result to the right by 1 bit, while also performing rounding. The rounding is done by adding 1 
 * to the sum before the shift, ensuring better accuracy when the sum is an odd number. 
 * It utilizes the ARM Neon intrinsic `vrhadd_u8`. The result is a new vector where each element 
 * is the rounded and halved sum of the corresponding elements in the input vectors, 
 * with the result stored as 8-bit unsigned integers.
 * 
 * @param a The first input vector of type uint8x8_t containing 8-bit unsigned integers.
 * @param b The second input vector of type uint8x8_t containing 8-bit unsigned integers.
 * @return uint8x8_t The result of the rounding halving addition, returned as an 8-bit unsigned integer vector.
 */
uint8x8_t vrhadd_u8_rvv(uint8x8_t a, uint8x8_t b) {
    return __riscv_vaaddu_vv_u8m1(a, b, VLEN_8);
}
