# Copyright 2024 10xEngineers

import csv
from quickchart import QuickChart

# Function to read CSV file and return test names and times for all targets
def read_csv(filename):
    test_names = []
    qemu_aarch64_times = []
    qemu_riscv64_times = []
    bpif3_times = []
    raspi4_times = []
    
    with open(filename, 'r') as file:
        reader = csv.reader(file)
        next(reader)  # Skip header
        for row in reader:
            test_names.append(row[0])
            qemu_aarch64_times.append(float(row[1]))
            qemu_riscv64_times.append(float(row[2]))
            bpif3_times.append(float(row[3]))
            raspi4_times.append(float(row[4]))
    
    return test_names, qemu_aarch64_times, qemu_riscv64_times, bpif3_times, raspi4_times

# Function to generate and save a bar chart
def generate_chart(test_names, dataset1, label1, dataset2, label2, output_filename):
    # Initialize QuickChart
    qc = QuickChart()
    qc.width = 1200
    qc.height = 800

    # Create the chart configuration with bright/dark colors
    qc.config = {
        "type": "bar",
        "data": {
            "labels": test_names,
            "datasets": [
                {
                    "label": label1,
                    "data": dataset1
                },
                {
                    "label": label2,
                    "data": dataset2
                }
            ]
        },
        "options": {
            "scales": {
                "yAxes": [{
                    "ticks": {
                        "beginAtZero": True,
                        "suggestedMax": max(dataset1 + dataset2) * 1.1
                    },
                    "scaleLabel": {
                        "display": True,
                        "labelString": "Time (us)"
                    }
                }]
            },
            "title": {
                "display": True,
                "text": f"Performance Comparison: {label1} vs {label2}"
            }
        }
    }

    # Save the chart to a file
    qc.to_file(output_filename)
    print(f"Performance comparison chart saved to '{output_filename}'")

# Read the CSV file
csv_file = 'combined_performance_results.csv'
test_names, qemu_aarch64_times, qemu_riscv64_times, bpif3_times, raspi4_times = read_csv(csv_file)

# Generate and save the charts
generate_chart(test_names, qemu_aarch64_times, "QEMU AARCH64", qemu_riscv64_times, "QEMU RISCV64", "performance_comparison_qemu-aarch64_vs_qemu-riscv64.png")
generate_chart(test_names, raspi4_times, "RASPI4", bpif3_times, "BPIF3", "performance_comparison_raspi4_vs_bpif3.png")
