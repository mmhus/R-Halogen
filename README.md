# R-Halogen
A RISC-V alternative to Neon

## Overview
This README outlines the use of the Makefile and various scripts for the R-Halogen project, which facilitates compilation, testing, and simulation for codes targeting RISC-V and ARM architectures. The Makefile and scripts are designed to simplify the build, test, and analysis process, supporting different environments, architectures, and toolchains.

## Prerequisites
- GNU Make
- RISC-V toolchain (`riscv64-unknown-linux-gnu-gcc` and related tools)
- ARM toolchain (`aarch64-none-linux-gnu-gcc` and related tools)
- QEMU for both RISC-V (`qemu-riscv64`) and ARM (`qemu-aarch64`)
- Spike RISC-V ISA Simulator (for RISC-V builds)
- BPIF3 and RASPI4 hardware emulation environments (for RISC-V and ARM)
- Python 3 (for generating graphs)

## R-Halogen Project Makefile
This project uses a Makefile to manage the compilation and execution of code for different architectures (RISC-V and ARM). The Makefile includes support for multiple target platforms, specified via the `TARGET` argument. Below is an explanation of how the Makefile works and a table of arguments with their default values.

### How the Makefile Works
The Makefile allows for the compilation and execution of code targeting RISC-V or ARM architectures. By setting the `ARCH` argument, you can switch between these architectures. The `TARGET` argument allows you to specify the exact target platform or simulator you want to use. The Makefile supports various tasks, including setting up the environment, compiling the code, running it on a simulator, emulator, or hardware, and cleaning up.

### Makefile Arguments
The following table describes the arguments you can use with the Makefile along with their default settings:

| Argument        | Default Value               | Description                                                                            |
|-----------------|-----------------------------|----------------------------------------------------------------------------------------|
| `ARCH`          | `riscv`                     | Architecture type. Can be either `riscv` or `arm`.                                     |
| `TARGET`        | `qemu-riscv64`              | Specifies the target platform or simulator. Supports `qemu-riscv64`, `qemu-aarch64`, `spike`, `bpif3`, and `raspi4`.  |
| `SRCS`          | None (user specified)       | Path to the .c source file of the test in the `tests/correctness/<*_test>/` directory. |
| `RISCV_PREFIX`  | `riscv64-unknown-linux-gnu` | Prefix for the RISC-V toolchain.                                                       |
| `ARM_PREFIX`    | `aarch64-none-linux-gnu`    | Prefix for the ARM toolchain.                                                          |
| `BPIF3_PREFIX`  | `riscv64-linux-gnu`         | Prefix for the BPIF3 toolchain.                                                        |
| `RASPI4_PREFIX` | `aarch64-linux-gnu`         | Prefix for the RASPI4 toolchain.                                                       |
| `QEMU`          | Depends on `ARCH` and `TARGET`| QEMU binary name, varies based on the architecture and target.                          |
| `SPIKE`         | `spike` (only for RISC-V)   | Spike simulator, used only for RISC-V.                                                 |
| `SPIKE_ISA`     | `rv64imafdcv`               | Instruction set architecture for the Spike simulator.                                  |
| `PK`            | `pk`                        | Proxy kernel used with Spike for RISC-V.                                               |
| `NUM_HARTS`     | `1`                         | Number of harts (hardware threads) to simulate.                                        |

### Targets
- `default`: Compiles the code and runs it on the specified `TARGET`. If `TARGET` is `spike`, it will run on the Spike simulator (for RISC-V). For `qemu-riscv64` and `qemu-aarch64`, it will run on QEMU. For `bpif3` and `raspi4`, it will run on the respective hardware or emulator.
- `setup`: Prepares the run directory and any necessary subdirectories.
- `compile`: Compiles the source files into an ELF executable and disassembles it.
- `spike`: Runs the compiled RISC-V executable on the Spike simulator.
- `qemu`: Runs the compiled executable on QEMU (supports both ARM and RISC-V).
- `bpif3`: Runs the compiled executable on BPIF3 (Banana Pi BPI-F3 RISC-V SBC).
- `raspi4`: Runs the compiled executable on RASPI4 (Raspberry Pi 4 ARM Board).
- `clean`: Cleans up the build and run directories.

### Usage
To use the Makefile, you can invoke it from the command line with the desired target and arguments. Specify the source file using `SRCS` and the target using the `TARGET` argument:

```bash
make ARCH=riscv TARGET=qemu-riscv64 SRCS=tests/correctness/<test_name>/<file_name>.c
make ARCH=arm TARGET=qemu-aarch64 SRCS=tests/correctness/<test_name>/<file_name>.c
make ARCH=riscv TARGET=spike SRCS=tests/correctness/<test_name>/<file_name>.c
make ARCH=riscv TARGET=bpif3 SRCS=tests/correctness/<test_name>/<file_name>.c
make ARCH=arm TARGET=raspi4 SRCS=tests/correctness/<test_name>/<file_name>.c
make clean
```
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

5. **`combined_correctness_comparison.sh`**
   - **Purpose**: This script combines the results from three CSV files using the `correctness_comparison.sh` script and outputs a single CSV file with correctness statuses for `qemu-riscv64`, `bpif3`, and `raspi4`.
   - **Usage**: `./combined_correctness_comparison.sh <aarch64_csv> <riscv64_csv> <bpif3_csv> <raspi4_csv>`
   - **Output Format**:
     ```
     testname,qemu_riscv64_status,bpif3_status,raspi4_status
     vadd_s8_rvv_test,Passed,Failed,Passed
     vadd_s16_rvv_test,Passed,Passed,Passed
     Passed,2,1,2
     Failed,0,1,0
     ```

6. **`combined_performance_comparison.sh`**
   - **Purpose**: This script combines the results from four CSV files using the `performance_comparison.sh` script and outputs a single CSV file comparing the performance across `qemu-aarch64`, `qemu-riscv64`, `bpif3`, and `raspi4`.
   - **Usage**: `./combined_performance_comparison.sh <aarch64_csv> <riscv64_csv> <bpif3_csv> <raspi4_csv>`
   - **Output Format**:
     ```
     testname,qemu_aarch64(us),qemu_riscv64(us),bpif3(us),raspi4(us)
     vadd_s8_rvv_test,0.80875,8.15625,0.2375,0.05625
     vadd_s16_rvv_test,1.00125,10.5212,0.1225,0.0525
     ```

### Python Scripts

7. **`generate_correctness_graph.py`**
   - **Purpose**: This Python script generates three graphical representation of the correctness comparison results. The graph visually shows which tests passed or failed across different targets with qemu-aarch64.
   - **Output Files**:
     ```
     correctness_results_qemu-riscv64.png
     correctness_results_bpif3.png
     correctness_results_raspi4.png
     ```

8. **`generate_performance_graph.py`**
   - **Purpose**: This Python script generates two graphical representation of the performance comparison results. The graph visually compares the performance (in microseconds) of tests across different targets.
   - **Output Files**:
     ```
     performance_comparison_qemu_aarch64_vs_qemu_riscv64.png
     performance_comparison_raspi4_vs_bpif3.png
     ```
     