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
    "vsub_s8_rvv_test"
    "vsub_s16_rvv_test"
    "vsub_s32_rvv_test"
    "vsub_s64_rvv_test"
    "vsubq_s8_rvv_test"
    "vsubq_s16_rvv_test"
    "vsubq_s32_rvv_test"
    "vsubq_s64_rvv_test"
    "vsub_u8_rvv_test"
    "vsub_u16_rvv_test"
    "vsub_u32_rvv_test"
    "vsub_u64_rvv_test"
    "vsubq_u8_rvv_test"
    "vsubq_u16_rvv_test"
    "vsubq_u32_rvv_test"
    "vsubq_u64_rvv_test"
    "vaddl_s8_rvv_test"
    "vaddl_s16_rvv_test"
    "vaddl_s32_rvv_test"
    "vaddl_u8_rvv_test"
    "vaddl_u16_rvv_test"
    "vaddl_u32_rvv_test"
    "vaddw_s8_rvv_test"
    "vaddw_s16_rvv_test"
    "vaddw_s32_rvv_test"
    "vaddw_u8_rvv_test"
    "vaddw_u16_rvv_test"
    "vaddw_u32_rvv_test"
    "vhadd_s8_rvv_test"
    "vhadd_s16_rvv_test"
    "vhadd_s32_rvv_test"
    "vhaddq_s8_rvv_test"
    "vhaddq_s16_rvv_test"
    "vhaddq_s32_rvv_test"
    "vhadd_u8_rvv_test"
    "vhadd_u16_rvv_test"
    "vhadd_u32_rvv_test"
    "vhaddq_u8_rvv_test"
    "vhaddq_u16_rvv_test"
    "vhaddq_u32_rvv_test"
    "vsubl_s8_rvv_test"
    "vsubl_s16_rvv_test"
    "vsubl_s32_rvv_test"
    "vsubl_u8_rvv_test"
    "vsubl_u16_rvv_test"
    "vsubl_u32_rvv_test"
    "vsubw_s8_rvv_test"
    "vsubw_s16_rvv_test"
    "vsubw_s32_rvv_test"
    "vsubw_u8_rvv_test"
    "vsubw_u16_rvv_test"
    "vsubw_u32_rvv_test"
    "vhsub_s8_rvv_test"
    "vhsub_s16_rvv_test"
    "vhsub_s32_rvv_test"
    "vhsubq_s8_rvv_test"
    "vhsubq_s16_rvv_test"
    "vhsubq_s32_rvv_test"
    "vhsub_u8_rvv_test"
    "vhsub_u16_rvv_test"
    "vhsub_u32_rvv_test"
    "vhsubq_u8_rvv_test"
    "vhsubq_u16_rvv_test"
    "vhsubq_u32_rvv_test"
    "vrhadd_s8_rvv_test"
    "vrhadd_s16_rvv_test"
    "vrhadd_s32_rvv_test"
    "vrhaddq_s8_rvv_test"
    "vrhaddq_s16_rvv_test"
    "vrhaddq_s32_rvv_test"
    "vrhadd_u8_rvv_test"
    "vrhadd_u16_rvv_test"
    "vrhadd_u32_rvv_test"
    "vrhaddq_u8_rvv_test"
    "vrhaddq_u16_rvv_test"
    "vrhaddq_u32_rvv_test"
    "vqadd_s8_rvv_test"
    "vqadd_s16_rvv_test"
    "vqadd_s32_rvv_test"
    "vqadd_s64_rvv_test"
    "vqaddq_s8_rvv_test"
    "vqaddq_s16_rvv_test"
    "vqaddq_s32_rvv_test"
    "vqaddq_s64_rvv_test"
    "vqadd_u8_rvv_test"
    "vqadd_u16_rvv_test"
    "vqadd_u32_rvv_test"
    "vqadd_u64_rvv_test"
    "vqaddq_u8_rvv_test"
    "vqaddq_u16_rvv_test"
    "vqaddq_u32_rvv_test"
    "vqaddq_u64_rvv_test"
    "vqsub_s8_rvv_test"
    "vqsub_s16_rvv_test"
    "vqsub_s32_rvv_test"
    "vqsub_s64_rvv_test"
    "vqsubq_s8_rvv_test"
    "vqsubq_s16_rvv_test"
    "vqsubq_s32_rvv_test"
    "vqsubq_s64_rvv_test"
    "vqsub_u8_rvv_test"
    "vqsub_u16_rvv_test"
    "vqsub_u32_rvv_test"
    "vqsub_u64_rvv_test"
    "vqsubq_u8_rvv_test"
    "vqsubq_u16_rvv_test"
    "vqsubq_u32_rvv_test"
    "vqsubq_u64_rvv_test"
    "vaddhn_s16_rvv_test"
    "vaddhn_s32_rvv_test"
    "vaddhn_s64_rvv_test"
    "vaddhn_u16_rvv_test"
    "vaddhn_u32_rvv_test"
    "vaddhn_u64_rvv_test"
    "vsubhn_s16_rvv_test"
    "vsubhn_s32_rvv_test"
    "vsubhn_s64_rvv_test"
    "vsubhn_u16_rvv_test"
    "vsubhn_u32_rvv_test"
    "vsubhn_u64_rvv_test"
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
        make PK=/home/jenkins_user/runner_dir/workspace/R-Halogen/riscv-pk/build/riscv64-unknown-elf/bin/pk ARCH=riscv TARGET="${TARGET}" SUBD=riscv SRCS=tests/correctness/"${test}"/"${test}".c

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
