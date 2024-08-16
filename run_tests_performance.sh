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

# Define the log file
log_file="performance_results_${TARGET}.csv"

# Clear the log file if it exists and write the header
if [[ "$TARGET" == "qemu-riscv64" || "$TARGET" == "spike" || "$TARGET" == "bpif3" ]]; then
    echo "testname,RISC-V (us)" > "$log_file"
elif [[ "$TARGET" == "qemu-aarch64" || "$TARGET" == "raspi4" ]]; then
    echo "testname,ARM (us)" > "$log_file"
else
    echo "Error: Invalid target specified: $TARGET"
    usage
fi

# Run tests based on the target environment
for test in "${tests[@]}"; do
    if [[ "$TARGET" == "qemu-riscv64" ]]; then
        # Run the RISC-V command
        make ARCH=riscv TARGET="${TARGET}" SUBD=riscv SRCS=tests/performance/"${test}"/"${test}".c

        # Define the output files
        riscv_out="RUN/tests/performance/${test}/riscv/${TARGET}/qemu.out"

        # Collect average performance data from the output files
        riscv_time=$(grep "RISC-V vector function" "$riscv_out" | awk '{print $6}' | awk '{count+=$1} END{print count/NR}')

        # Write the results to the log file
        echo -e "${test},${riscv_time}" | tee -a "$log_file"

    elif [[ "$TARGET" == "spike" ]]; then
        # Run the RISC-V command
        make PK=/home/jenkins_user/runner_dir/workspace/R-Halogen/riscv-pk/build/riscv64-unknown-elf/bin/pk ARCH=riscv TARGET="${TARGET}" SUBD=riscv SRCS=tests/performance/"${test}"/"${test}".c

        # Define the output files
        riscv_out="RUN/tests/performance/${test}/riscv/${TARGET}/${TARGET}.out"

        # Collect average performance data from the output files
        riscv_time=$(grep "RISC-V vector function" "$riscv_out" | awk '{print $6}' | awk '{count+=$1} END{print count/NR}')

        # Write the results to the log file
        echo -e "${test},${riscv_time}" | tee -a "$log_file"

    elif [[ "$TARGET" == "qemu-aarch64" ]]; then
        # Run the ARM command
        make ARCH=arm TARGET="${TARGET}" SUBD=arm SRCS=tests/performance/"${test}"/"${test}".c

        # Define the output files
        arm_out="RUN/tests/performance/${test}/arm/${TARGET}/qemu.out"

        # Collect average performance data from the output files
        arm_time=$(grep "ARM-Neon vector function" "$arm_out" | awk '{print $6}' | awk '{count+=$1} END{print count/NR}')

        # Write the results to the log file
        echo -e "${test},${arm_time}" | tee -a "$log_file"

    elif [[ "$TARGET" == "raspi4" ]]; then
        # Run the ARM command
        make ARCH=arm TARGET="${TARGET}" SUBD=arm SRCS=tests/performance/"${test}"/"${test}".c

        # Define the output file
        arm_out="RUN/tests/performance/${test}/arm/${TARGET}/${TARGET}.out"

        # Collect average performance data from the output file
        arm_time=$(grep "ARM-Neon vector function" "$arm_out" | awk '{print $6}' | awk '{count+=$1} END{print count/NR}')

        # Write the results to the log file
        echo -e "${test},${arm_time}" | tee -a "$log_file"

    elif [[ "$TARGET" == "bpif3" ]]; then
        # Run the RISC-V command
        make ARCH=riscv TARGET="${TARGET}" SUBD=riscv SRCS=tests/performance/"${test}"/"${test}".c

        # Define the output file
        riscv_out="RUN/tests/performance/${test}/riscv/${TARGET}/${TARGET}.out"

        # Collect average performance data from the output file
        riscv_time=$(grep "RISC-V vector function" "$riscv_out" | awk '{print $6}' | awk '{count+=$1} END{print count/NR}')

        # Write the results to the log file
        echo -e "${test},${riscv_time}" | tee -a "$log_file"

    else
        echo "Error: Invalid target specified: $TARGET"
        usage
    fi
done
