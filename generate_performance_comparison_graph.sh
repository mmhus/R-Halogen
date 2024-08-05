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

# Generate the performance comparison graph using Python
python3 - <<EOF
import csv
from quickchart import QuickChart

# Function to read CSV file and return test names and times
def read_csv(filename):
    test_names = []
    times = []
    with open(filename, 'r') as file:
        reader = csv.reader(file)
        next(reader)  # Skip header
        for row in reader:
            test_names.append(row[0])
            times.append(float(row[1]))
    return test_names, times

# Read the CSV files
arm_test_names, arm_times = read_csv('$ARM_RESULTS_CSV')
riscv_test_names, riscv_times = read_csv('$RISCV_RESULTS_CSV')

# Check if test names are the same in both files
if arm_test_names != riscv_test_names:
    raise ValueError("Test names do not match between the two CSV files")

# Initialize QuickChart
qc = QuickChart()
qc.width = 1000
qc.height = 600

# Create the chart configuration
qc.config = {
    "type": "bar",
    "data": {
        "labels": arm_test_names,
        "datasets": [
            {
                "label": "ARM",
                "data": arm_times
            },
            {
                "label": "RISC-V",
                "data": riscv_times
            }
        ]
    },
    "options": {
        "scales": {
            "yAxes": [{
                "ticks": {
                    "beginAtZero": True,
                    "suggestedMax": max(max(arm_times), max(riscv_times)) * 1.1
                },
                "scaleLabel": {
                    "display": True,
                    "labelString": "Time (us)"
                }
            }]
        },
        "title": {
            "display": True,
            "text": "Performance Comparison: ${ARM_TARGET} vs ${RISCV_TARGET}"
        }
    }
}

# Save the chart to a file
output_filename = 'performance_comparison_${ARM_TARGET}_vs_${RISCV_TARGET}.png'
qc.to_file(output_filename)
print(f"Performance Comparison graph saved to '{output_filename}'")
EOF
