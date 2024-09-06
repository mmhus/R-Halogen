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
void run_test_cases(void (*vect_sub)(uint8_t*, uint8_t*, int, uint8_t*)) {
    uint8_t test_cases[][8] = {
        {1, 2, 3, 4, 5, 6, 7, 8},                    // Regular positive numbers
        {0, 0, 0, 0, 0, 0, 0, 0},                    // All zeros
        {255, 254, 253, 252, 251, 250, 249, 248},    // Near maximum uint8_t values
        {255, 255, 255, 255, 255, 255, 255, 255},    // Maximum uint8_t value
        {1, 0, 255, 2, 254, 3, 253, 4},              // Mixed near boundary values
        {50, 50, 50, 50, 50, 50, 50, 50},            // Repeated positive numbers
        {200, 100, 150, 50, 250, 25, 175, 125},      // Arbitrary mixed values
        {1, 1, 1, 1, 1, 1, 1, 1}                     // All ones
    };

    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    for (int i = 0; i < num_tests; i++) {
        uint8_t *a = test_cases[i];
        uint8_t b[8] = {1, 2, 3, 4, 5, 6, 7, 8};
        uint8_t result[8];

        vect_sub(a, b, 8, result);
        print_results(result, 8, UINT8);
    }
}

#if defined(ARM_NEON)
// ARM Neon-specific implementation
void vhsub_u8_neon(uint8_t *a, uint8_t *b, int size, uint8_t *result) {
    uint8x8_t x = vld1_u8(a);
    uint8x8_t y = vld1_u8(b);
    uint8x8_t z = vhsub_u8(x, y);
    vst1_u8(result, z);
}
// Function to run tests using ARM Neon instructions/intrinsics
void run_tests_neon() {
    run_test_cases(vhsub_u8_neon);
}

#elif defined(RISCV_VECTOR)
// RISC-V Vector-specific implementation
void vhsub_u8_rvvector(uint8_t *a, uint8_t *b, int size, uint8_t *result) {
    uint8x8_t x = __riscv_vle8_v_u8m1(a, size);
    uint8x8_t y = __riscv_vle8_v_u8m1(b, size);
    uint8x8_t z = vhsub_u8_rvv(x, y);
    __riscv_vse8_v_u8m1(result, z, size);
}
// Function to run tests using RISC-V Vector instructions/intrinsics
void run_tests_rvv() {
    run_test_cases(vhsub_u8_rvvector);
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
