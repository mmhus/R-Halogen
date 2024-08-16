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
