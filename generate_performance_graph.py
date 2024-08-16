import pandas as pd
import matplotlib.pyplot as plt

# Load the data from the CSV file
csv_file_path = 'performance_results.csv'
df = pd.read_csv(csv_file_path)

# Remove "_test" from the function names in the 'testname' column
df['testname'] = df['testname'].str.replace('_test', '')

# Plotting
plt.figure(figsize=(10, 6))

# Plot the data on a logarithmic scale
for column in df.columns[1:]:
    plt.plot(df['testname'], df[column], label=column)

# Set y-axis to log scale
plt.yscale('log')
plt.xlabel('Function Name')
plt.ylabel('Execution Time (us)')
plt.title('Performance Comparison Across Targets (Logarithmic Scale)')
plt.xticks(rotation=45, ha='right')
plt.legend(loc="upper right")
plt.grid(True)
plt.tight_layout()

# Save the plot to a file
plt.savefig('performance_comparison_across_targets.png')

# Show the plot
# plt.show()
