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
void run_test_cases(void (*vect_sub)(uint64_t*, uint64_t*, int, uint64_t*)) {
    uint64_t test_cases[][1] = {
        {6},                                   // Regular positive number
        {0},                                   // All zeros
        {18446744073709551615ULL},             // Maximum uint64_t value
        {5000000000000000000ULL},              // Large positive number
        {1},                                   // All ones
    };

    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    for (int i = 0; i < num_tests; i++) {
        uint64_t *a = test_cases[i];
        uint64_t b[1] = {1};
        uint64_t result[1];

        // Measure the time taken for the vector addition operation
        struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC, &start);
        vect_sub(a, b, 1, result);
        clock_gettime(CLOCK_MONOTONIC, &end);
        double time_taken = (end.tv_sec - start.tv_sec) * 1e6 + (end.tv_nsec - start.tv_nsec) / 1e3; // time in microseconds
        printf("Test case %d {Vector load, Vector function, Vector store} took %.2f microseconds\n",i + 1, time_taken);
        // print_results(result, 1, "uint64_t");
    }
}

#if defined(ARM_NEON)
// ARM Neon-specific implementation
void vsub_u64_neon(uint64_t *a, uint64_t *b, int size, uint64_t *result) {
    uint64x1_t x = vld1_u64(a);
    uint64x1_t y = vld1_u64(b);
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    uint64x1_t z = vsub_u64(x, y);
    clock_gettime(CLOCK_MONOTONIC, &end);
    double time_taken = (end.tv_sec - start.tv_sec) * 1e6 + (end.tv_nsec - start.tv_nsec) / 1e3; // time in microseconds
    printf("ARM-Neon vector function 'vsub_u64' took %.2f microseconds\n", time_taken);
    vst1_u64(result, z);
}
// Function to run tests using ARM Neon instructions/intrinsics
void run_tests_neon() {
    run_test_cases(vsub_u64_neon);
}

#elif defined(RISCV_VECTOR)
// RISC-V Vector-specific implementation
void vsub_u64_rvvector(uint64_t *a, uint64_t *b, int size, uint64_t *result) {
    uint64x1_t x = __riscv_vle64_v_u64m1(a, size);
    uint64x1_t y = __riscv_vle64_v_u64m1(b, size);
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    uint64x1_t z = vsub_u64_rvv(x, y);
    clock_gettime(CLOCK_MONOTONIC, &end);
    double time_taken = (end.tv_sec - start.tv_sec) * 1e6 + (end.tv_nsec - start.tv_nsec) / 1e3; // time in microseconds
    printf("RISC-V vector function 'vsub_u64_rvv' took %.2f microseconds\n", time_taken);
    __riscv_vse64_v_u64m1(result, z, size);
}
// Function to run tests using RISC-V Vector instructions/intrinsics
void run_tests_rvv() {
    run_test_cases(vsub_u64_rvvector);
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
