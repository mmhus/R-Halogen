// Copyright 2024 10xEngineers

#include "common_utilities.h"

#if defined(ARM_NEON)
    #include <arm_neon.h>
#elif defined(RISCV_VECTOR)
    #include "rhal_base.h"
#else
    #error "Unsupported architecture. Please define either ARM_NEON or RISCV_VECTOR."
#endif

// Function to run test cases with a given vect_add
void run_test_cases(void (*vect_add)(int8_t*, int8_t*, int, int16_t*)) {
    int8_t test_cases[][8] = {
        {1, 2, 3, 4, 5, 6, 7, 8},                   // Regular positive numbers
        {0, 0, 0, 0, 0, 0, 0, 0},                   // All zeros
        {-1, -2, -3, -4, -5, -6, -7, -8},           // Negative numbers
        {127, 127, 127, 127, 127, 127, 127, 127},   // Maximum int8_t value
        {-128, -128, -128, -128, -128, -128, -128, -128},   // Minimum int8_t value
        {127, -128, 127, -128, 127, -128, 127, -128},   // Max and Min int8_t values
        {50, -50, 100, -100, 25, -25, 75, -75},     // Mixed positive and negative numbers
        {1, 1, 1, 1, 1, 1, 1, 1}                    // All ones
    };

    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    for (int i = 0; i < num_tests; i++) {
        int8_t *a = test_cases[i];
        int8_t b[8] = {1, 2, 3, 4, 5, 6, 7, 8};
        int16_t result[8];

        vect_add(a, b, 8, result);
        print_results(result, 8, INT16);
    }
}

#if defined(ARM_NEON)
// ARM Neon-specific implementation
void vaddl_s8_neon(int8_t *a, int8_t *b, int size, int16_t *result) {
    int8x8_t x = vld1_s8(a);
    int8x8_t y = vld1_s8(b);
    int16x8_t z = vaddl_s8(x, y);
    vst1q_s16(result, z);
}
// Function to run tests using ARM Neon instructions/intrinsics
void run_tests_neon() {
    run_test_cases(vaddl_s8_neon);
}

#elif defined(RISCV_VECTOR)
// RISC-V Vector-specific implementation
void vaddl_s8_rvvector(int8_t *a, int8_t *b, int size, int16_t *result) {
    int8x8_t x = __riscv_vle8_v_i8m1(a, size);
    int8x8_t y = __riscv_vle8_v_i8m1(b, size);
    int16x8_t z = vaddl_s8_rvv(x, y);
    __riscv_vse16_v_i16m1(result, z, size);
}
// Function to run tests using RISC-V Vector instructions/intrinsics
void run_tests_rvv() {
    run_test_cases(vaddl_s8_rvvector);
}
#endif

int main() {
    #if defined(RISCV_VECTOR)
        run_tests_rvv();
    #elif defined(ARM_NEON)
        run_tests_neon();
    #else
        #error "Unsupported architecture. Please define either ARM_NEON or RISCV_VECTOR."
    #endif
    return 0;
}
