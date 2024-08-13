# Copyright 2024 10xEngineers

import csv
from quickchart import QuickChart

# Function to read CSV file and return the count of passed and failed tests per target
def read_csv(filename):
    test_names = []
    passed_counts = [[] for _ in range(3)]  # Three empty lists for each target
    failed_counts = [[] for _ in range(3)]  # Three empty lists for each target

    with open(filename, 'r') as file:
        reader = list(csv.reader(file))
        for row in reader[1:-2]:  # Skip the first line (header) and the last two lines
            test_names.append(row[0])
            for i in range(3):
                if row[i + 1] == "Passed":
                    passed_counts[i].append(1)
                    failed_counts[i].append(0)
                else:
                    passed_counts[i].append(0)
                    failed_counts[i].append(1)
    
    return test_names, passed_counts, failed_counts

# Read the CSV file
csv_file = 'combined_correctness_results.csv'
test_names, passed_counts, failed_counts = read_csv(csv_file)

# List of targets
targets = ['QEMU RISCV64', 'BPIF3', 'RASPI4']

# Loop over each target to create a bar chart with the title
for i, target in enumerate(targets):
    # Initialize QuickChart
    qc = QuickChart()
    qc.width = 800
    qc.height = 600
    
    # Create the chart configuration
    qc.config = {
        "type": "bar",
        "data": {
            "labels": test_names,
            "datasets": [
                {
                    "label": "Passed",
                    "data": passed_counts[i],
                    "backgroundColor": "#4CAF50"  # Green for passed
                },
                {
                    "label": "Failed",
                    "data": [-count for count in failed_counts[i]],  # Negative for failed
                    "backgroundColor": "#F44336"  # Red for failed
                }
            ]
        },
        "options": {
            "scales": {
                "yAxes": [{
                    "ticks": {
                        "beginAtZero": True
                    },
                    "scaleLabel": {
                        "display": True,
                        "labelString": "Number of Tests"
                    }
                }],
                "xAxes": [{
                    "stacked": True
                }],
                "yAxes": [{
                    "stacked": True,
                    "ticks": {
                        "beginAtZero": True,
                        "suggestedMin": -1,  # Minimum value for y-axis
                        "suggestedMax": 1  # Maximum value for y-axis
                    }
                }]
            },
            "title": {
                "display": True,
                "text": f"Correctness comparison of {target} with QEMU-AARCH64"
            }
        }
    }
    
    # Save each chart to a file
    output_filename = f'correctness_results_{target.replace(" ", "-").lower()}.png'
    qc.to_file(output_filename)
    print(f"Correctness results bar chart saved to '{output_filename}'")
