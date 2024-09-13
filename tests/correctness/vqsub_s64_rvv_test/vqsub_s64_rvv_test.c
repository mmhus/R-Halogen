// Copyright 2024 10xEngineers

#include "common_utilities.h"

#if defined(ARM_NEON)
    #include <arm_neon.h>
#elif defined(RISCV_VECTOR)
    #include "rhal_base.h"
#else
    #error "Unsupported architecture. Please define either ARM_NEON or RISCV_VECTOR."
#endif

// Function to run test cases with a given vect_sub
void run_test_cases(void (*vect_sub)(int64_t*, int64_t*, int, int64_t*)) {
    int64_t test_cases[][1] = {
        {1},                        // Regular positive numbers
        {0},                        // All zeros
        {-1},                       // Negative numbers
        {9223372036854775807LL},        // Maximum int64_t value
        {-9223372036854775807LL - 1},   // Minimum int64_t value
        {5000},                     // Mixed positive number
        {-5000},                    // Mixed negative number
        {1}                         // All ones
    };

    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    for (int i = 0; i < num_tests; i++) {
        int64_t *a = test_cases[i];
        int64_t b[1] = {1};
        int64_t result[1];

        vect_sub(a, b, 1, result);
        print_results(result, 1, INT64);
    }
}

#if defined(ARM_NEON)
// ARM Neon-specific implementation
void vqsub_s64_neon(int64_t *a, int64_t *b, int size, int64_t *result) {
    int64x1_t x = vld1_s64(a);
    int64x1_t y = vld1_s64(b);
    int64x1_t z = vqsub_s64(x, y);
    vst1_s64(result, z);
}
// Function to run tests using ARM Neon instructions/intrinsics
void run_tests_neon() {
    run_test_cases(vqsub_s64_neon);
}

#elif defined(RISCV_VECTOR)
// RISC-V Vector-specific implementation
void vqsub_s64_rvvector(int64_t *a, int64_t *b, int size, int64_t *result) {
    int64x1_t x = __riscv_vle64_v_i64m1(a, size);
    int64x1_t y = __riscv_vle64_v_i64m1(b, size);
    int64x1_t z = vqsub_s64_rvv(x, y);
    __riscv_vse64_v_i64m1(result, z, size);
}
// Function to run tests using RISC-V Vector instructions/intrinsics
void run_tests_rvv() {
    run_test_cases(vqsub_s64_rvvector);
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
