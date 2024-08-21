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
void run_test_cases(void (*vect_sub)(uint32_t*, uint32_t*, int, uint32_t*)) {
    uint32_t test_cases[][2] = {
        {1, 2},                                  // Regular positive numbers
        {0, 0},                                  // All zeros
        {4294967295U, 4294967294U},              // Near maximum uint32_t values
        {4294967295U, 4294967295U},              // Maximum uint32_t value
        {1, 0},                                  // Mixed near boundary values
        {500000, 500000},                        // Repeated positive numbers
        {4000000000U, 1000000000U},              // Arbitrary mixed values
        {1, 1}                                   // All ones
    };

    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    for (int i = 0; i < num_tests; i++) {
        uint32_t *a = test_cases[i];
        uint32_t b[2] = {1, 2};
        uint32_t result[2];

        // Measure the time taken for the vector addition operation
        struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC, &start);
        vect_sub(a, b, 2, result);
        clock_gettime(CLOCK_MONOTONIC, &end);
        double time_taken = (end.tv_sec - start.tv_sec) * 1e6 + (end.tv_nsec - start.tv_nsec) / 1e3; // time in microseconds
        printf("Test case %d {Vector load, Vector function, Vector store} took %.2f microseconds\n",i + 1, time_taken);
        // print_results(result, 2, "uint32_t");
    }
}

#if defined(ARM_NEON)
// ARM Neon-specific implementation
void vsub_u32_neon(uint32_t *a, uint32_t *b, int size, uint32_t *result) {
    uint32x2_t x = vld1_u32(a);
    uint32x2_t y = vld1_u32(b);
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    uint32x2_t z = vsub_u32(x, y);
    clock_gettime(CLOCK_MONOTONIC, &end);
    double time_taken = (end.tv_sec - start.tv_sec) * 1e6 + (end.tv_nsec - start.tv_nsec) / 1e3; // time in microseconds
    printf("ARM-Neon vector function 'vsub_u32' took %.2f microseconds\n", time_taken);
    vst1_u32(result, z);
}
// Function to run tests using ARM Neon instructions/intrinsics
void run_tests_neon() {
    run_test_cases(vsub_u32_neon);
}

#elif defined(RISCV_VECTOR)
// RISC-V Vector-specific implementation
void vsub_u32_rvvector(uint32_t *a, uint32_t *b, int size, uint32_t *result) {
    uint32x2_t x = __riscv_vle32_v_u32m1(a, size);
    uint32x2_t y = __riscv_vle32_v_u32m1(b, size);
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    uint32x2_t z = vsub_u32_rvv(x, y);
    clock_gettime(CLOCK_MONOTONIC, &end);
    double time_taken = (end.tv_sec - start.tv_sec) * 1e6 + (end.tv_nsec - start.tv_nsec) / 1e3; // time in microseconds
    printf("RISC-V vector function 'vsub_u32_rvv' took %.2f microseconds\n", time_taken);
    __riscv_vse32_v_u32m1(result, z, size);
}
// Function to run tests using RISC-V Vector instructions/intrinsics
void run_tests_rvv() {
    run_test_cases(vsub_u32_rvvector);
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
