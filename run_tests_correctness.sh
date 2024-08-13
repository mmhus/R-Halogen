# Copyright 2024 10xEngineers

#!/bin/bash

# Ensure the script exits on errors or undefined variables
set -euo pipefail

# Function to display usage help
usage() {
    echo "Usage: $0 <target>"
    echo "Possible targets:"
    echo "  qemu-riscv64   - Run tests on QEMU RISC-V emulator"
    echo "  qemu-aarch64   - Run tests on QEMU ARM emulator"
    echo "  spike          - Run tests on Spike Simulator"
    echo "  bpif3          - Run tests on Banana Pi F3"
    echo "  raspi4         - Run tests on Raspberry Pi 4"
    exit 1
}

# Check if the target is provided
if [ $# -ne 1 ]; then
    echo "Error: No target specified."
    usage
fi

TARGET=$1

# Define the list of correctness tests
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

# Define the log file for correctness results
log_file="correctness_results_${TARGET}.csv"

# Write the header to the log file
echo "testname,test no,result" > "$log_file"

# Run correctness tests based on the target environment
for i in "${!tests[@]}"; do
    test="${tests[$i]}"
    test_no=1
    
    if [[ "$TARGET" == "qemu-riscv64" ]]; then
    # Run the RISC-V command
    make ARCH=riscv TARGET="${TARGET}" SUBD=riscv SRCS=tests/correctness/"${test}"/"${test}".c

    # Define the output files
    riscv_out="RUN/tests/correctness/${test}/riscv/${TARGET}/qemu.out"

    # Read the output file line by line and write to CSV
    while IFS= read -r line; do
        echo "${test},test #${test_no},${line}" >> "$log_file"
        test_no=$((test_no + 1))
    done < "$riscv_out"

    elif [[ "$TARGET" == "spike" ]]; then
        # Run the RISC-V command
        make ARCH=riscv TARGET="${TARGET}" SUBD=riscv SRCS=tests/correctness/"${test}"/"${test}".c

        # Define the output files
        riscv_out="RUN/tests/correctness/${test}/riscv/${TARGET}/${TARGET}.out"

        # Read the output file line by line and write to CSV
        while IFS= read -r line; do
            echo "${test},test #${test_no},${line}" >> "$log_file"
            test_no=$((test_no + 1))
        done < "$riscv_out"

    elif [[ "$TARGET" == "qemu-aarch64" ]]; then
        # Run the ARM command
        make ARCH=arm TARGET="${TARGET}" SUBD=arm SRCS=tests/correctness/"${test}"/"${test}".c

        # Define the output files
        arm_out="RUN/tests/correctness/${test}/arm/${TARGET}/qemu.out"

        # Read the output file line by line and write to CSV
        while IFS= read -r line; do
            echo "${test},test #${test_no},${line}" >> "$log_file"
            test_no=$((test_no + 1))
        done < "$arm_out"

    elif [[ "$TARGET" == "raspi4" ]]; then
        # Run the ARM command
        make ARCH=arm TARGET="${TARGET}" SUBD=arm SRCS=tests/correctness/"${test}"/"${test}".c

        # Define the output file
        arm_out="RUN/tests/correctness/${test}/arm/${TARGET}/${TARGET}.out"

        # Read the output file line by line and write to CSV
        while IFS= read -r line; do
            echo "${test},test #${test_no},${line}" >> "$log_file"
            test_no=$((test_no + 1))
        done < "$arm_out"

    elif [[ "$TARGET" == "bpif3" ]]; then
        # Run the RISC-V command
        make ARCH=riscv TARGET="${TARGET}" SUBD=riscv SRCS=tests/correctness/"${test}"/"${test}".c

        # Define the output file
        riscv_out="RUN/tests/correctness/${test}/riscv/${TARGET}/${TARGET}.out"

        # Read the output file line by line and write to CSV
        while IFS= read -r line; do
            echo "${test},test #${test_no},${line}" >> "$log_file"
            test_no=$((test_no + 1))
        done < "$riscv_out"

    else
        echo "Error: Invalid target specified: $TARGET"
        usage
    fi
done
