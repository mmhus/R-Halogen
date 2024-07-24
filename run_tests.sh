# Copyright 2024 10xEngineers

#!/bin/bash

# Define the list of tests
tests=(
    "vadd_s8_rvv_test"
    "vadd_s16_rvv_test"
    "vadd_s32_rvv_test"
    "vadd_s64_rvv_test"
    "vaddq_s8_rvv_test"
    "vaddq_s16_rvv_test"
    "vaddq_s32_rvv_test"
    "vaddq_s64_rvv_test"
    "vadd_u8_rvv_test"
    "vadd_u16_rvv_test"
    "vadd_u32_rvv_test"
    "vadd_u64_rvv_test"
)

# Define the log file
log_file="test_results.log"

# Clear the log file if it exists
> $log_file

# Color codes
GREEN="\e[32m"
RED="\e[31m"
NOCOLOR="\e[0m"

# Execute each test
for test in "${tests[@]}"; do
    # Run the RISC-V command
    make ARCH=riscv SUBD=riscv SRCS=tests/correctness/${test}/${test}.c
    # Run the ARM command
    make ARCH=arm SUBD=arm SRCS=tests/correctness/${test}/${test}.c

    # Define the output files
    riscv_out="RUN/R-Halogen/tests/correctness/${test}/riscv/qemu-riscv64/qemu.out"
    arm_out="RUN/R-Halogen/tests/correctness/${test}/arm/qemu-aarch64/qemu.out"

    # Check if both output files exist
    if [[ -f "$riscv_out" && -f "$arm_out" ]]; then
        # Compare the output files
        if cmp -s "$riscv_out" "$arm_out"; then
            echo -e "${test}: ${GREEN}Passed${NOCOLOR}" | tee -a $log_file
        else
            echo -e "${test}: ${RED}Failed${NOCOLOR}" | tee -a $log_file
        fi
    else
        echo -e "${test}: ${RED}Output files are missing${NC}" | tee -a $log_file
    fi
done

# Print the log file on terminal
echo -e "\n"
echo "========TEST RESULTS========"
cat $log_file
echo "============================"
