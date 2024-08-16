# Copyright 2024 10xEngineers

#!/bin/bash

# Ensure the script exits on errors or undefined variables
set -euo pipefail

# Output CSV file
OUTPUT_CSV="correctness_results.csv"

# Assigning arguments to variables, or using default file names if not provided
QEMU_AARCH64_RESULTS_CSV="${1:-correctness_results_qemu-aarch64.csv}"
QEMU_RISCV64_RESULTS_CSV="${2:-correctness_results_qemu-riscv64.csv}"
SPIKE_RESULTS_CSV="${3:-correctness_results_spike.csv}"
BPIF3_RESULTS_CSV="${4:-correctness_results_bpif3.csv}"
RASPI4_RESULTS_CSV="${5:-correctness_results_raspi4.csv}"

# Path to the 2-argument correctness script
CORRECTNESS_SCRIPT="./correctness_comparison.sh"

# Temporary files to store individual comparison results
TEMP_AARCH64_RISCV64="temp_qemu_aarch64_vs_qemu_riscv64.csv"
TEMP_AARCH64_SPIKE="temp_qemu_aarch64_vs_spike.csv"
TEMP_AARCH64_BPIF3="temp_qemu_aarch64_vs_bpif3.csv"
TEMP_AARCH64_RASPI4="temp_qemu_aarch64_vs_raspi4.csv"

# Array of required CSV files
required_files=(
    "$QEMU_AARCH64_RESULTS_CSV"
    "$QEMU_RISCV64_RESULTS_CSV"
    "$SPIKE_RESULTS_CSV"
    "$BPIF3_RESULTS_CSV"
    "$RASPI4_RESULTS_CSV"
)

# Check if all required CSV files are present
for file in "${required_files[@]}"; do
    if [[ ! -f "$file" ]]; then
        echo "Error: Required file not found: $file"
        exit 1
    fi
done

# Check if the correctness script is executable
if [[ ! -x "$CORRECTNESS_SCRIPT" ]]; then
    echo "Error: Correctness script '$CORRECTNESS_SCRIPT' is not executable or not found."
    exit 1
fi

# Run the correctness comparison script for each target and store the results in temporary files
"$CORRECTNESS_SCRIPT" "$QEMU_AARCH64_RESULTS_CSV" "$QEMU_RISCV64_RESULTS_CSV" > "$TEMP_AARCH64_RISCV64"
"$CORRECTNESS_SCRIPT" "$QEMU_AARCH64_RESULTS_CSV" "$SPIKE_RESULTS_CSV" > "$TEMP_AARCH64_SPIKE"
"$CORRECTNESS_SCRIPT" "$QEMU_AARCH64_RESULTS_CSV" "$BPIF3_RESULTS_CSV" > "$TEMP_AARCH64_BPIF3"
"$CORRECTNESS_SCRIPT" "$QEMU_AARCH64_RESULTS_CSV" "$RASPI4_RESULTS_CSV" > "$TEMP_AARCH64_RASPI4"

# Check if all temporary files are created
if [[ ! -s "$TEMP_AARCH64_RISCV64" || ! -s "$TEMP_AARCH64_SPIKE" || ! -s "$TEMP_AARCH64_BPIF3" || ! -s "$TEMP_AARCH64_RASPI4" ]]; then
    echo "Error: One or more temporary result files are empty. Please check the correctness script and input CSVs."
    exit 1
fi

# Initialize the OUTPUT_CSV file with headers
echo "testname,qemu_riscv64_status,spike_status,bpif3_status,raspi4_status" > $OUTPUT_CSV

# Initialize counters for passed and failed tests
declare -A pass_count=([qemu_riscv64_status]=0 [spike_status]=0 [bpif3_status]=0 [raspi4_status]=0)
declare -A fail_count=([qemu_riscv64_status]=0 [spike_status]=0 [bpif3_status]=0 [raspi4_status]=0)

# Extract and combine the results from the temporary files into the final OUTPUT_CSV
while IFS=, read -r testname qemu_riscv64_status; do
    spike_status=$(grep "^$testname," "$TEMP_AARCH64_SPIKE" | cut -d, -f2)
    bpif3_status=$(grep "^$testname," "$TEMP_AARCH64_BPIF3" | cut -d, -f2)
    raspi4_status=$(grep "^$testname," "$TEMP_AARCH64_RASPI4" | cut -d, -f2)
    
    echo "$testname,$qemu_riscv64_status,$spike_status,$bpif3_status,$raspi4_status" >> $OUTPUT_CSV
    
    # Update pass/fail counts
    for status in qemu_riscv64_status spike_status bpif3_status raspi4_status; do
        if [[ ${!status} == "Passed" ]]; then
            pass_count[$status]=$((pass_count[$status]+1))
        elif [[ ${!status} == "Failed" ]]; then
            fail_count[$status]=$((fail_count[$status]+1))
        fi
    done
done < <(tail -n +2 "$TEMP_AARCH64_RISCV64")  # Assuming all temp files have the same testname entries

# Append the summary counts to the OUTPUT_CSV file
echo "Passed,${pass_count[qemu_riscv64_status]},${pass_count[spike_status]},${pass_count[bpif3_status]},${pass_count[raspi4_status]}" >> $OUTPUT_CSV
echo "Failed,${fail_count[qemu_riscv64_status]},${fail_count[spike_status]},${fail_count[bpif3_status]},${fail_count[raspi4_status]}" >> $OUTPUT_CSV

# Clean up temporary files
rm -f "$TEMP_AARCH64_RISCV64" "$TEMP_AARCH64_SPIKE" "$TEMP_AARCH64_BPIF3" "$TEMP_AARCH64_RASPI4"

echo "Correctness comparison complete, results saved to '$OUTPUT_CSV'."
