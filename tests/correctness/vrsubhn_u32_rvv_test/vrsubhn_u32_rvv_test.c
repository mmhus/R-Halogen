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
void run_test_cases(void (*vect_sub)(uint32_t*, uint32_t*, int, uint16_t*)) {
    uint32_t test_cases[][4] = {
        {1, 2, 3, 4},                        // Regular positive numbers
        {0, 0, 0, 0},                        // All zeros
        {4294967295, 4294967294, 4294967293, 4294967292}, // High positive numbers (near max uint32_t)
        {4294967295, 4294967295, 4294967295, 4294967295},  // Maximum uint32_t value
        {0, 0, 0, 0},                        // Minimum uint32_t value (all zeros)
        {4294967295, 0, 4294967295, 0},      // Max and Min uint32_t values
        {5000, 4294962296, 10000, 4294957296}, // Mixed positive numbers
        {1, 1, 1, 1}                         // All ones
    };

    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    for (int i = 0; i < num_tests; i++) {
        uint32_t *a = test_cases[i];
        uint32_t b[4] = {1, 2, 3, 4};
        uint16_t result[4];

        vect_sub(a, b, 4, result);
        print_results(result, 4, UINT16);
    }
}

#if defined(ARM_NEON)
// ARM Neon-specific implementation
void vrsubhn_u32_neon(uint32_t *a, uint32_t *b, int size, uint16_t *result) {
    uint32x4_t x = vld1q_u32(a);
    uint32x4_t y = vld1q_u32(b);
    uint16x4_t z = vrsubhn_u32(x, y);
    vst1_u16(result, z);
}
// Function to run tests using ARM Neon instructions/intrinsics
void run_tests_neon() {
    run_test_cases(vrsubhn_u32_neon);
}

#elif defined(RISCV_VECTOR)
// RISC-V Vector-specific implementation
void vrsubhn_u32_rvvector(uint32_t *a, uint32_t *b, int size, uint16_t *result) {
    uint32x4_t x = __riscv_vle32_v_u32m1(a, size);
    uint32x4_t y = __riscv_vle32_v_u32m1(b, size);
    uint16x4_t z = vrsubhn_u32_rvv(x, y);
    __riscv_vse16_v_u16m1(result, z, size);
}
// Function to run tests using RISC-V Vector instructions/intrinsics
void run_tests_rvv() {
    run_test_cases(vrsubhn_u32_rvvector);
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
