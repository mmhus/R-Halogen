# Copyright 2024 10xEngineers

#!/bin/bash

# Ensure the script exits on errors or undefined variables
set -euo pipefail

# Function to display usage help
usage() {
    echo "Usage: $0 <arm_results_csv> <riscv_results_csv>"
    echo "Example 1: $0 correctness_results_rasp4.csv correctness_results_bpif3.csv"
    echo "Example 2: $0 correctness_results_qemu-aarch64.csv correctness_results_qemu-riscv64.csv"
    exit 1
}

# Check if the correct number of arguments is provided
if [ $# -ne 2 ]; then
    echo "Error: Invalid number of arguments."
    usage
fi

ARM_RESULTS_CSV=$1
RISCV_RESULTS_CSV=$2

# Check if the provided files exist
if [[ ! -f "$ARM_RESULTS_CSV" ]]; then
    echo "Error: File not found: $ARM_RESULTS_CSV"
    exit 1
fi

if [[ ! -f "$RISCV_RESULTS_CSV" ]]; then
    echo "Error: File not found: $RISCV_RESULTS_CSV"
    exit 1
fi

# Extract target names from the file names
RISCV_TARGET=$(basename "$RISCV_RESULTS_CSV" | sed -E 's/correctness_results_([^.]+)\.csv/\1/')

# Initialize variables
all_tests_passed=true
current_test_name=""

# Output header
echo "testname,${RISCV_TARGET}_status"

# Compare results and determine pass/fail status
while IFS=, read -r arm_test_name arm_test_no arm_result; do
    if [ -n "$arm_test_name" ]; then
        if [ "$current_test_name" != "$arm_test_name" ] && [ -n "$current_test_name" ]; then
            # Output the result in the desired format
            if $all_tests_passed; then
                echo "$current_test_name,Passed"
            else
                echo "$current_test_name,Failed"
            fi
            # Reset for next testname
            all_tests_passed=true
        fi
        current_test_name="$arm_test_name"

        # Find the corresponding RISC-V result
        riscv_line=$(grep "^$arm_test_name,$arm_test_no" "$RISCV_RESULTS_CSV")
        riscv_result=$(echo "$riscv_line" | cut -d, -f3-)
        
        if [ "$arm_result" != "$riscv_result" ]; then
            all_tests_passed=false
        fi
    fi
done < <(tail -n +2 "$ARM_RESULTS_CSV")  # Skip the header

# Output the last test result
if [ -n "$current_test_name" ]; then
    if $all_tests_passed; then
        echo "$current_test_name,Passed"
    else
        echo "$current_test_name,Failed"
    fi
fi
