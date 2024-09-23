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
void run_test_cases(void (*vect_add)(int32_t*, int32_t*, int, int32_t*)) {
    int32_t test_cases[][2] = {
        {1, 2},                          // Regular positive numbers
        {0, 0},                          // All zeros
        {-1, -2},                        // Negative numbers
        {2147483647, 2147483647},        // Maximum int32_t value
        {-2147483648, -2147483648},      // Minimum int32_t value
        {2147483647, -2147483648},       // Max and Min int32_t values
        {5000, -5000},                   // Mixed positive and negative numbers
        {1, 1}                           // All ones
    };

    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    for (int i = 0; i < num_tests; i++) {
        int32_t *a = test_cases[i];
        int32_t b[2] = {1, 2};
        int32_t result[2];

        vect_add(a, b, 2, result);
        print_results(result, 2, INT32);
    }
}

#if defined(ARM_NEON)
// ARM Neon-specific implementation
void vqadd_s32_neon(int32_t *a, int32_t *b, int size, int32_t *result) {
    int32x2_t x = vld1_s32(a);
    int32x2_t y = vld1_s32(b);
    int32x2_t z = vqadd_s32(x, y);
    vst1_s32(result, z);
}
// Function to run tests using ARM Neon instructions/intrinsics
void run_tests_neon() {
    run_test_cases(vqadd_s32_neon);
}

#elif defined(RISCV_VECTOR)
// RISC-V Vector-specific implementation
void vqadd_s32_rvvector(int32_t *a, int32_t *b, int size, int32_t *result) {
    int32x2_t x = __riscv_vle32_v_i32m1(a, size);
    int32x2_t y = __riscv_vle32_v_i32m1(b, size);
    int32x2_t z = vqadd_s32_rvv(x, y);
    __riscv_vse32_v_i32m1(result, z, size);
}
// Function to run tests using RISC-V Vector instructions/intrinsics
void run_tests_rvv() {
    run_test_cases(vqadd_s32_rvvector);
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
