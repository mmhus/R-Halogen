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
void run_test_cases(void (*vect_add)(uint16_t*, uint16_t*, int, uint16_t*)) {
    uint16_t test_cases[][8] = {
        {1, 2, 3, 4, 5, 6, 7, 8},                   // Regular positive numbers
        {0, 0, 0, 0, 0, 0, 0, 0},                   // All zeros
        {65535, 65534, 65533, 65532, 65531, 65530, 65529, 65528}, // High positive numbers (near max uint16_t)
        {65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535},   // Maximum uint16_t value
        {0, 0, 0, 0, 0, 0, 0, 0},                   // Minimum uint16_t value (all zeros)
        {65535, 0, 65535, 0, 65535, 0, 65535, 0},   // Max and Min uint16_t values
        {5000, 60535, 10000, 55535, 2500, 63035, 7500, 58035},     // Mixed positive numbers
        {1, 1, 1, 1, 1, 1, 1, 1}                    // All ones
    };

    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    for (int i = 0; i < num_tests; i++) {
        uint16_t *a = test_cases[i];
        uint16_t b[8] = {1, 2, 3, 4, 5, 6, 7, 8};
        uint16_t result[8];

        vect_add(a, b, 8, result);
        print_results(result, 8, UINT16);
    }
}

#if defined(ARM_NEON)
// ARM Neon-specific implementation
void vhaddq_u16_neon(uint16_t *a, uint16_t *b, int size, uint16_t *result) {
    uint16x8_t x = vld1q_u16(a);
    uint16x8_t y = vld1q_u16(b);
    uint16x8_t z = vhaddq_u16(x, y);
    vst1q_u16(result, z);
}
// Function to run tests using ARM Neon instructions/intrinsics
void run_tests_neon() {
    run_test_cases(vhaddq_u16_neon);
}

#elif defined(RISCV_VECTOR)
// RISC-V Vector-specific implementation
void vhaddq_u16_rvvector(uint16_t *a, uint16_t *b, int size, uint16_t *result) {
    uint16x8_t x = __riscv_vle16_v_u16m1(a, size);
    uint16x8_t y = __riscv_vle16_v_u16m1(b, size);
    uint16x8_t z = vhaddq_u16_rvv(x, y);
    __riscv_vse16_v_u16m1(result, z, size);
}
// Function to run tests using RISC-V Vector instructions/intrinsics
void run_tests_rvv() {
    run_test_cases(vhaddq_u16_rvvector);
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
