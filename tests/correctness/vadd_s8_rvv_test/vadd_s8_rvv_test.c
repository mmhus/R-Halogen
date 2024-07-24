// Copyright 2024 10xEngineers

#include "../../../common/print.h"

#ifdef ARM_NEON
    #include <arm_neon.h>
#else
#ifdef RISCV_VECTOR
    #include "../../../common/rhal_base.h"
#endif
#endif

// Function to run test cases with a given func_ptr
void run_test_cases(void (*func_ptr)(int8_t*, int8_t*, int, int8_t*)) {
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
        int8_t result[8];

        func_ptr(a, b, 8, result);
        print_results(result, 8, "int8_t");
    }
}

#ifdef ARM_NEON
// ARM Neon-specific implementation
void vadd_s8_neon(int8_t *a, int8_t *b, int size, int8_t *result) {
    int8x8_t x = vld1_s8(a);
    int8x8_t y = vld1_s8(b);
    int8x8_t z = vadd_s8(x, y);
    vst1_s8(result, z);
}
// Function to run tests using ARM Neon instructions/intrinsics
void run_tests_neon() {
    run_test_cases(vadd_s8_neon);
}
#endif

#ifdef RISCV_VECTOR
// RISC-V Vector-specific implementation
void vadd_s8_rvvector(int8_t *a, int8_t *b, int size, int8_t *result) {
    int8x8_t x = __riscv_vle8_v_i8m1(a, size);
    int8x8_t y = __riscv_vle8_v_i8m1(b, size);
    int8x8_t z = vadd_s8_rvv(x, y);
    __riscv_vse8_v_i8m1(result, z, size);
}
// Function to run tests using RISC-V Vector instructions/intrinsics
void run_tests_rvv() {
    run_test_cases(vadd_s8_rvvector);
}
#endif

int main() {
    #ifdef RISCV_VECTOR
        run_tests_rvv();
    #endif
    #ifdef ARM_NEON
        run_tests_neon();
    #endif
    return 0;
}
