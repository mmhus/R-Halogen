## R-Halogen Project Scripts
The R-Halogen project includes several scripts to facilitate testing and performance analysis across different architectures and platforms. Below is a description of each script:

### Shell Scripts

1. **`run_tests_correctness.sh`**
    - **Purpose**: This script takes the target as an argument and compiles and runs correctness tests on the specified target.
    - **Usage**: `./run_tests_correctness.sh <target>`

2. **`run_tests_performance.sh`**
    - **Purpose**: This script takes the target as an argument and compiles and runs performance tests on the specified target.
    - **Usage**: `./run_tests_performance.sh <target>`

3. **`correctness_comparison.sh`**
    - **Purpose**: This script takes two arguments: the first is a CSV file for `aarch64`, and the second is a CSV file for `riscv64`. It outputs a CSV file showing the test name and the correctness status for `qemu-riscv64` with `qemu-aarch64`.
    - **Usage**: `./correctness_comparison.sh <aarch64_csv> <riscv64_csv>`
    - **Output Format**:
        ```
        testname,qemu-riscv64_status
        vadd_s8_rvv_test,Passed
        vadd_s16_rvv_test,Passed
        ```

4. **`performance_comparison.sh`**
    - **Purpose**: This script takes two arguments: the first is a CSV file for `aarch64`, and the second is a CSV file for `riscv64`. It outputs a CSV file comparing the performance (in microseconds) between `qemu-aarch64` and `qemu-riscv64`.
    - **Usage**: `./performance_comparison.sh <aarch64_csv> <riscv64_csv>`
    - **Output Format**:
        ```
        testname,qemu-aarch64(us),qemu-riscv64(us)
        vadd_s8_rvv_test,0.80875,8.15625
        vadd_s16_rvv_test,1.00125,10.5212
        ```

5. **`correctness_comparison_results.sh`**
    - **Purpose**: This script combines the results from four CSV files using the `correctness_comparison.sh` script and outputs a single CSV file with correctness statuses for `qemu-riscv64`, `spike`, `bpif3`, and `raspi4` against `qemu-aarch64`.
    - **Usage**: `./combined_correctness_comparison.sh <aarch64_csv> <riscv64_csv> <spike_csv> <bpif3_csv> <raspi4_csv>`
    - **Output Format**:
        ```
        testname,qemu_riscv64_status,spike_status,bpif3_status,raspi4_status
        vadd_s8_rvv_test,Passed,Passed,Failed,Passed
        vadd_s16_rvv_test,Passed,Passed,Passed,Passed
        Passed,2,2,1,2
        Failed,0,0,1,0
        ```

6. **`performance_comparison_results.sh`**
    - **Purpose**: This script combines the results from five CSV files using the `performance_comparison.sh` script and outputs a single CSV file comparing the performance across `qemu-aarch64`, `qemu-riscv64`, `spike`, `bpif3`, and `raspi4`.
    - **Usage**: `./combined_performance_comparison.sh <aarch64_csv> <riscv64_csv> <spike_csv> <bpif3_csv> <raspi4_csv>`
    - **Output Format**:
        ```
        testname,qemu_aarch64(us),qemu_riscv64(us),spike(us),bpif3(us),raspi4(us)
        vadd_s8_rvv_test,0.80875,8.15625,0.26,0.2375,0.05625
        vadd_s16_rvv_test,1.00125,10.5212,0.26,0.1225,0.0525
        ```

### Python Scripts

7. **`generate_performance_graph.py`**
    - **Purpose**: This Python script generates a graphical representation of the performance comparison results. The graph visually compares the performance (in microseconds) a shows a graph in logarithmic scale of tests across different targets.
    - **Output Files**:
        ```
        performance_comparison_across_targets.png
        ```

### Cloud-V Pipeline Scripts

8. **`r-halogen_pipeline`**
    - **Purpose**: This pipeline script is designed to automate the testing and analysis of the R-Halogen project across multiple targets. It coordinates correctness and performance testing, handles results comparison, and generates performance graphs. The script utilizes Jenkins pipelines to manage and execute tests in parallel, optimize resource usage, and ensure clean environments for each run.
    - **Artifacts**: This script generates three artifacts on Cloud-V.
     ```
        correctness_results.csv: Contains the results of correctness tests across different targets.
        performance_results.csv: Contains the results of performance tests across different targets.
        performance_comparison_across_targets.png: A graphical representation of performance comparison across targets.
     ```
