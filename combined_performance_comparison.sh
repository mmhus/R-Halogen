# Copyright 2024 10xEngineers

#!/bin/bash

# Ensure the script exits on errors or undefined variables
set -euo pipefail

# Output CSV file
OUTPUT_CSV="combined_performance_results.csv"

# Assigning arguments to variables, or using default file names if not provided
QEMU_AARCH64_RESULTS_CSV="${1:-performance_results_qemu-aarch64.csv}"
QEMU_RISCV64_RESULTS_CSV="${2:-performance_results_qemu-riscv64.csv}"
BPIF3_RESULTS_CSV="${3:-performance_results_bpif3.csv}"
RASPI4_RESULTS_CSV="${4:-performance_results_raspi4.csv}"

# Array of required CSV files
required_files=(
    "$QEMU_AARCH64_RESULTS_CSV"
    "$QEMU_RISCV64_RESULTS_CSV"
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

# Initialize the OUTPUT_CSV file with headers
echo "testname,qemu_aarch64 (us),qemu_riscv64 (us),bpif3 (us),raspi4 (us)" > $OUTPUT_CSV

# Read results into associative arrays for each target
declare -A qemu_riscv64_times
declare -A bpif3_times
declare -A raspi4_times

# Function to read a CSV file into an associative array
read_csv_into_array() {
    local csv_file=$1
    local -n array=$2
    while IFS=, read -r testname time; do
        array["$testname"]=$time
    done < <(tail -n +2 "$csv_file") # Skip header
}

# Read the non-primary CSV files into the corresponding arrays
read_csv_into_array "$QEMU_RISCV64_RESULTS_CSV" qemu_riscv64_times
read_csv_into_array "$BPIF3_RESULTS_CSV" bpif3_times
read_csv_into_array "$RASPI4_RESULTS_CSV" raspi4_times

# Iterate over the qemu-aarch64 CSV file in the order it appears and combine results
while IFS=, read -r testname aarch64_time; do
    riscv64_time=${qemu_riscv64_times["$testname"]:=""}  # Default to empty string if not found
    bpif3_time=${bpif3_times["$testname"]:=""}  # Default to empty string if not found
    raspi4_time=${raspi4_times["$testname"]:=""}  # Default to empty string if not found
    
    echo "$testname,$aarch64_time,$riscv64_time,$bpif3_time,$raspi4_time" >> $OUTPUT_CSV
done < <(tail -n +2 "$QEMU_AARCH64_RESULTS_CSV")

echo "Performance comparison complete, results saved to '$OUTPUT_CSV'."
