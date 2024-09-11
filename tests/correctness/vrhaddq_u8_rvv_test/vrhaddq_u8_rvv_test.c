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
void run_test_cases(void (*vect_add)(uint8_t*, uint8_t*, int, uint8_t*)) {
    uint8_t test_cases[][16] = {
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16},          // Regular positive numbers
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},                  // All zeros
        {255, 254, 253, 252, 251, 250, 249, 248, 247, 246, 245, 244, 243, 242, 241, 240}, // High positive numbers (near max uint8_t)
        {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255}, // Maximum uint8_t value
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},                  // Minimum uint8_t value (all zeros)
        {255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0},  // Max and Min uint8_t values
        {50, 205, 100, 155, 25, 230, 75, 180, 50, 205, 100, 155, 25, 230, 75, 180}, // Mixed positive numbers
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}                    // All ones
    };

    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    for (int i = 0; i < num_tests; i++) {
        uint8_t *a = test_cases[i];
        uint8_t b[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
        uint8_t result[16];

        vect_add(a, b, 16, result);
        print_results(result, 16, UINT8);
    }
}

#if defined(ARM_NEON)
// ARM Neon-specific implementation
void vrhaddq_u8_neon(uint8_t *a, uint8_t *b, int size, uint8_t *result) {
    uint8x16_t x = vld1q_u8(a);
    uint8x16_t y = vld1q_u8(b);
    uint8x16_t z = vrhaddq_u8(x, y);
    vst1q_u8(result, z);
}
// Function to run tests using ARM Neon instructions/intrinsics
void run_tests_neon() {
    run_test_cases(vrhaddq_u8_neon);
}

#elif defined(RISCV_VECTOR)
// RISC-V Vector-specific implementation
void vrhaddq_u8_rvvector(uint8_t *a, uint8_t *b, int size, uint8_t *result) {
    uint8x16_t x = __riscv_vle8_v_u8m1(a, size);
    uint8x16_t y = __riscv_vle8_v_u8m1(b, size);
    uint8x16_t z = vrhaddq_u8_rvv(x, y);
    __riscv_vse8_v_u8m1(result, z, size);
}
// Function to run tests using RISC-V Vector instructions/intrinsics
void run_tests_rvv() {
    run_test_cases(vrhaddq_u8_rvvector);
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
