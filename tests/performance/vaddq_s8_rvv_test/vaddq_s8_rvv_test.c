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
void run_test_cases(void (*vect_add)(int8_t*, int8_t*, int, int8_t*)) {
    int8_t test_cases[][16] = {
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16},   // Regular positive numbers
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},          // All zeros
        {-1, -2, -3, -4, -5, -6, -7, -8, -9, -10, -11, -12, -13, -14, -15, -16}, // Negative numbers
        {127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127}, // Maximum int8_t value
        {-128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128}, // Minimum int8_t value
        {127, -128, 127, -128, 127, -128, 127, -128, 127, -128, 127, -128, 127, -128, 127, -128}, // Max and Min int8_t values
        {50, -50, 100, -100, 25, -25, 75, -75, 50, -50, 100, -100, 25, -25, 75, -75}, // Mixed positive and negative numbers
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}            // All ones
    };

    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    for (int i = 0; i < num_tests; i++) {
        int8_t *a = test_cases[i];
        int8_t b[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
        int8_t result[16];

        // Measure the time taken for the vector addition operation
        struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC, &start);
        vect_add(a, b, 16, result);
        clock_gettime(CLOCK_MONOTONIC, &end);
        double time_taken = (end.tv_sec - start.tv_sec) * 1e6 + (end.tv_nsec - start.tv_nsec) / 1e3; // time in microseconds
        printf("Test case %d {Vector load, Vector function, Vector store} took %.2f microseconds\n",i + 1, time_taken);
        // print_results(result, 16, "int8_t");
    }
}

#if defined(ARM_NEON)
// ARM Neon-specific implementation
void vaddq_s8_neon(int8_t *a, int8_t *b, int size, int8_t *result) {
    int8x16_t x = vld1q_s8(a);
    int8x16_t y = vld1q_s8(b);
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    int8x16_t z = vaddq_s8(x, y);
    clock_gettime(CLOCK_MONOTONIC, &end);
    double time_taken = (end.tv_sec - start.tv_sec) * 1e6 + (end.tv_nsec - start.tv_nsec) / 1e3; // time in microseconds
    printf("ARM-Neon vector function 'vaddq_s8' took %.2f microseconds\n", time_taken);
    vst1q_s8(result, z);
}
// Function to run tests using ARM Neon instructions/intrinsics
void run_tests_neon() {
    run_test_cases(vaddq_s8_neon);
}

#elif defined(RISCV_VECTOR)
// RISC-V Vector-specific implementation
void vaddq_s8_rvvector(int8_t *a, int8_t *b, int size, int8_t *result) {
    int8x16_t x = __riscv_vle8_v_i8m1(a, size);
    int8x16_t y = __riscv_vle8_v_i8m1(b, size);
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    int8x16_t z = vaddq_s8_rvv(x, y);
    clock_gettime(CLOCK_MONOTONIC, &end);
    double time_taken = (end.tv_sec - start.tv_sec) * 1e6 + (end.tv_nsec - start.tv_nsec) / 1e3; // time in microseconds
    printf("RISC-V vector function 'vaddq_s8_rvv' took %.2f microseconds\n", time_taken);
    __riscv_vse8_v_i8m1(result, z, size);
}
// Function to run tests using RISC-V Vector instructions/intrinsics
void run_tests_rvv() {
    run_test_cases(vaddq_s8_rvvector);
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
