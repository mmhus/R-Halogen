import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# Read the CSV data
data = pd.read_csv('performance_results.csv')

# Clean up test names
data['testname'] = data['testname'].str.replace('_test', '')

# Define the tests_name and the corresponding data
tests_name = data['testname']
targets = data.columns[1:]

# Set up the figure and axis
fig, ax = plt.subplots(figsize=(16, 8))

# Plotting the bar graph
bar_width = 0.16
index = np.arange(len(tests_name))

# Create the bar positions for each target
positions = [index + i * bar_width for i in range(len(targets))]

# Plot each target's data as a set of bars
for i, target in enumerate(targets):
    bars = ax.bar(positions[i], data[target], bar_width, label=target, edgecolor='black', linewidth=0.5)
    
    # Add value labels slightly above the center of each bar
    for bar in bars:
        height = bar.get_height()
        ax.text(bar.get_x() + bar.get_width() / 2, height * 1.02,
                f'{height:.2f}', ha='center', va='bottom', fontsize=6.5, rotation=90)

# Set logarithmic scale for the y-axis
ax.set_yscale('log')

# Customize the plot
ax.set_xlabel('Function Name')
ax.set_ylabel('Execution Time (µs)')
ax.set_title('Performance Comparison Across Targets (Logarithmic Scale)')

# Set x-axis ticks and labels
ax.set_xticks(index + bar_width * (len(targets) - 1) / 2)
ax.set_xticklabels(tests_name, rotation=45, ha='right', fontsize=10)

# Customize the legend
ax.legend(title='Target', loc='upper right')

# Add grid lines
ax.grid(True, axis='y', linestyle='--', alpha=0.7)

# Adjust layout and display the plot
plt.tight_layout()
plt.savefig('performance_comparison_across_targets.png', dpi=300, bbox_inches='tight')

# Display the plot
# plt.show()
