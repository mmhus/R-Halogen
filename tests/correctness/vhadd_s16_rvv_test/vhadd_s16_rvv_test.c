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
void run_test_cases(void (*vect_add)(int16_t*, int16_t*, int, int16_t*)) {
    int16_t test_cases[][4] = {
        {1, 2, 3, 4},                    // Regular positive numbers
        {0, 0, 0, 0},                    // All zeros
        {-1, -2, -3, -4},                // Negative numbers
        {32767, 32767, 32767, 32767},    // Maximum int16_t value
        {-32768, -32768, -32768, -32768},   // Minimum int16_t value
        {32767, -32768, 32767, -32768},  // Max and Min int16_t values
        {5000, -5000, 10000, -10000},    // Mixed positive and negative numbers
        {1, 1, 1, 1}                     // All ones
    };

    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    for (int i = 0; i < num_tests; i++) {
        int16_t *a = test_cases[i];
        int16_t b[4] = {1, 2, 3, 4};
        int16_t result[4];

        vect_add(a, b, 4, result);
        print_results(result, 4, INT16);
    }
}

#if defined(ARM_NEON)
// ARM Neon-specific implementation
void vhadd_s16_neon(int16_t *a, int16_t *b, int size, int16_t *result) {
    int16x4_t x = vld1_s16(a);
    int16x4_t y = vld1_s16(b);
    int16x4_t z = vhadd_s16(x, y);
    vst1_s16(result, z);
}
// Function to run tests using ARM Neon instructions/intrinsics
void run_tests_neon() {
    run_test_cases(vhadd_s16_neon);
}

#elif defined(RISCV_VECTOR)
// RISC-V Vector-specific implementation
void vhadd_s16_rvvector(int16_t *a, int16_t *b, int size, int16_t *result) {
    int16x4_t x = __riscv_vle16_v_i16m1(a, size);
    int16x4_t y = __riscv_vle16_v_i16m1(b, size);
    int16x4_t z = vhadd_s16_rvv(x, y);
    __riscv_vse16_v_i16m1(result, z, size);
}
// Function to run tests using RISC-V Vector instructions/intrinsics
void run_tests_rvv() {
    run_test_cases(vhadd_s16_rvvector);
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
