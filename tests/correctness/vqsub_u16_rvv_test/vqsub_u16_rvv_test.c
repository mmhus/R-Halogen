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
void run_test_cases(void (*vect_sub)(uint16_t*, uint16_t*, int, uint16_t*)) {
    uint16_t test_cases[][4] = {
        {1, 2, 3, 4},                      // Regular positive numbers
        {0, 0, 0, 0},                      // All zeros
        {65535, 65534, 65533, 65532},      // Near maximum uint16_t values
        {65535, 65535, 65535, 65535},      // Maximum uint16_t value
        {1, 0, 65535, 2},                  // Mixed near boundary values
        {5000, 5000, 5000, 5000},          // Repeated positive numbers
        {50000, 10000, 60000, 15000},      // Arbitrary mixed values
        {1, 1, 1, 1}                       // All ones
    };

    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    for (int i = 0; i < num_tests; i++) {
        uint16_t *a = test_cases[i];
        uint16_t b[4] = {1, 2, 3, 4};
        uint16_t result[4];

        vect_sub(a, b, 4, result);
        print_results(result, 4, UINT16);
    }
}

#if defined(ARM_NEON)
// ARM Neon-specific implementation
void vqsub_u16_neon(uint16_t *a, uint16_t *b, int size, uint16_t *result) {
    uint16x4_t x = vld1_u16(a);
    uint16x4_t y = vld1_u16(b);
    uint16x4_t z = vqsub_u16(x, y);
    vst1_u16(result, z);
}
// Function to run tests using ARM Neon instructions/intrinsics
void run_tests_neon() {
    run_test_cases(vqsub_u16_neon);
}

#elif defined(RISCV_VECTOR)
// RISC-V Vector-specific implementation
void vqsub_u16_rvvector(uint16_t *a, uint16_t *b, int size, uint16_t *result) {
    uint16x4_t x = __riscv_vle16_v_u16m1(a, size);
    uint16x4_t y = __riscv_vle16_v_u16m1(b, size);
    uint16x4_t z = vqsub_u16_rvv(x, y);
    __riscv_vse16_v_u16m1(result, z, size);
}
// Function to run tests using RISC-V Vector instructions/intrinsics
void run_tests_rvv() {
    run_test_cases(vqsub_u16_rvvector);
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
