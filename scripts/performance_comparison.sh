# Copyright 2024 10xEngineers

#!/bin/bash

# Ensure the script exits on errors or undefined variables
set -euo pipefail

# Function to display usage help
usage() {
    echo "Usage: $0 <arm_results_csv> <riscv_results_csv>"
    echo "Example 1: $0 performance_results_rasp4.csv performance_results_bpif3.csv"
    echo "Example 2: $0 performance_results_qemu-aarch64.csv performance_results_qemu-riscv64.csv"
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
    usage
fi

if [[ ! -f "$RISCV_RESULTS_CSV" ]]; then
    echo "Error: File not found: $RISCV_RESULTS_CSV"
    usage
fi

# Extract target names from the file names
ARM_TARGET=$(basename "$ARM_RESULTS_CSV" | sed -E 's/performance_results_([^.]+)\.csv/\1/')
RISCV_TARGET=$(basename "$RISCV_RESULTS_CSV" | sed -E 's/performance_results_([^.]+)\.csv/\1/')

# Combine results into the desired format
echo "testname,$ARM_TARGET(us),$RISCV_TARGET(us)"

# Read ARM results into an associative array
declare -A arm_times
while IFS=, read -r testname time; do
    arm_times["$testname"]=$time
done < <(tail -n +2 "$ARM_RESULTS_CSV") # Skip header

# Read RISC-V results and output combined results
while IFS=, read -r testname time; do
    arm_time=${arm_times["$testname"]}
    if [ -z "$arm_time" ]; then
        echo "Error: Test name '$testname' found in $RISCV_TARGET but not in $ARM_TARGET."
        exit 1
    fi
    echo "$testname,$arm_time,$time"
done < <(tail -n +2 "$RISCV_RESULTS_CSV") # Skip header
