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
void run_test_cases(void (*vect_add)(uint64_t*, uint64_t*, int, uint64_t*)) {
    uint64_t test_cases[][2] = {
        {1, 2},                        // Regular positive numbers
        {0, 0},                        // All zeros
        {18446744073709551615ULL, 18446744073709551614ULL}, // High positive numbers (near max uint64_t)
        {18446744073709551615ULL, 18446744073709551615ULL},  // Maximum uint64_t value
        {0, 0},                        // Minimum uint64_t value (all zeros)
        {18446744073709551615ULL, 0},  // Max and Min uint64_t values
        {5000, 18446744073709551606ULL}, // Mixed positive numbers
        {1, 1}                         // All ones
    };

    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    for (int i = 0; i < num_tests; i++) {
        uint64_t *a = test_cases[i];
        uint64_t b[2] = {1, 2};
        uint64_t result[2];

        vect_add(a, b, 2, result);
        print_results(result, 2, UINT64);
    }
}

#if defined(ARM_NEON)
// ARM Neon-specific implementation
void vqaddq_u64_neon(uint64_t *a, uint64_t *b, int size, uint64_t *result) {
    uint64x2_t x = vld1q_u64(a);
    uint64x2_t y = vld1q_u64(b);
    uint64x2_t z = vqaddq_u64(x, y);
    vst1q_u64(result, z);
}
// Function to run tests using ARM Neon instructions/intrinsics
void run_tests_neon() {
    run_test_cases(vqaddq_u64_neon);
}

#elif defined(RISCV_VECTOR)
// RISC-V Vector-specific implementation
void vqaddq_u64_rvvector(uint64_t *a, uint64_t *b, int size, uint64_t *result) {
    uint64x2_t x = __riscv_vle64_v_u64m1(a, size);
    uint64x2_t y = __riscv_vle64_v_u64m1(b, size);
    uint64x2_t z = vqaddq_u64_rvv(x, y);
    __riscv_vse64_v_u64m1(result, z, size);
}
// Function to run tests using RISC-V Vector instructions/intrinsics
void run_tests_rvv() {
    run_test_cases(vqaddq_u64_rvvector);
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
