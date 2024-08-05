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
    "vaddq_u8_rvv_test"
    "vaddq_u16_rvv_test"
    "vaddq_u32_rvv_test"
    "vaddq_u64_rvv_test"
)

# Ensure the script exits on errors or undefined variables
set -euo pipefail

# Color codes
GREEN="\e[32m"
RED="\e[31m"
NOCOLOR="\e[0m"

# Function to handle errors
error_handler() {
    echo -e "${RED}An error occurred during the execution of the script.${NOCOLOR}"
    exit 1
}

# Trap errors
trap error_handler ERR

# Define the log file
log_file="correctness_results.log"

# Clear the log file if it exists
: > "$log_file"

# Array to store failed tests
failed_tests=()

# Execute each test
for test in "${tests[@]}"; do
    # Run the RISC-V command
    if ! make ARCH=riscv TARGET=qemu-riscv64 SUBD=riscv SRCS=tests/correctness/"${test}"/"${test}".c; then
        echo -e "${test}: ${RED}RISC-V compilation failed${NOCOLOR}" | tee -a "$log_file"
        failed_tests+=("${test}")
        continue
    fi

    # Run the ARM command
    if ! make ARCH=arm TARGET=qemu-aarch64 SUBD=arm SRCS=tests/correctness/"${test}"/"${test}".c; then
        echo -e "${test}: ${RED}ARM compilation failed${NOCOLOR}" | tee -a "$log_file"
        failed_tests+=("${test}")
        continue
    fi

    # Define the output files
    riscv_out="RUN/tests/correctness/${test}/riscv/qemu-riscv64/qemu.out"
    arm_out="RUN/tests/correctness/${test}/arm/qemu-aarch64/qemu.out"

    # Check if both output files exist
    if [[ -f "$riscv_out" && -f "$arm_out" ]]; then
        # Compare the output files
        if cmp -s "$riscv_out" "$arm_out"; then
            echo -e "${test}: ${GREEN}Passed${NOCOLOR}" | tee -a "$log_file"
        else
            echo -e "${test}: ${RED}Failed${NOCOLOR}" | tee -a "$log_file"
            failed_tests+=("${test}")
        fi
    else
        echo -e "${test}: ${RED}Output files are missing${NOCOLOR}" | tee -a "$log_file"
        failed_tests+=("${test}")
    fi
done

# Print the log file on terminal
echo -e "\n"
echo "========TEST RESULTS========"
cat "$log_file"
echo "============================"

# Display failed tests if any
if [ ${#failed_tests[@]} -ne 0 ]; then
    echo -e "\n${RED}The following tests failed (${#failed_tests[@]} out of ${#tests[@]}):${NOCOLOR}"
    for test in "${failed_tests[@]}"; do
        echo -e "${RED}${test}${NOCOLOR}"
    done
else
    echo -e "\n${GREEN}All tests passed successfully!${NOCOLOR}"
fi

exit 0
