# R-Halogen
A RISC-V alternative to Neon

## Overview
This README outlines the use of the Makefile for the R-Halogen project, which facilitates compilation and simulation for codes targeting RISC-V and ARM architectures. The Makefile is designed to simplify the build and test process, supporting different environments and toolchains specific to each architecture.

## Prerequisites
- GNU Make
- RISC-V toolchain (`riscv64-unknown-linux-gnu-gcc` and related tools)
- ARM toolchain (`aarch64-none-linux-gnu-gcc` and related tools)
- QEMU for both RISC-V (`qemu-riscv64`) and ARM (`qemu-aarch64`)
- Spike RISC-V ISA Simulator (for RISC-V builds)

## R-Halogen Project Makefile
This project uses a Makefile to manage the compilation and execution of code for different architectures (RISC-V and ARM). Below is an explanation of how the Makefile works and a table of arguments with their default values.

### How the Makefile Works
The Makefile allows for the compilation and execution of code targeting RISC-V or ARM architectures. By setting the `ARCH` argument, you can switch between these architectures. The Makefile supports various tasks, including setting up the environment, compiling the code, running it on a simulator or emulator, and cleaning up.

### Makefile Arguments
The following table describes the arguments you can use with the Makefile along with their default settings:

| Argument        | Default Value               | Description                                                                            |
|-----------------|-----------------------------|----------------------------------------------------------------------------------------|
| `ARCH`          | `riscv`                     | Architecture type. Can be either `riscv` or `arm`.                                     |
| `SRCS`          | None (user specified)       | Path to the .c source file of the test in the `tests/correctness/<*_test>/` directory. |
| `RISCV_PREFIX`  | `riscv64-unknown-linux-gnu` | Prefix for the RISC-V toolchain.                                                       |
| `ARM_PREFIX`    | `aarch64-none-linux-gnu`    | Prefix for the ARM toolchain.                                                          |
| `QEMU`          | Depends on `ARCH`           | QEMU binary name, varies based on the architecture.                                    |
| `SPIKE`         | `spike` (only for RISC-V)   | Spike simulator, used only for RISC-V.                                                 |
| `SPIKE_ISA`     | `rv64imafdcv`               | Instruction set architecture for the Spike simulator.                                  |
| `PK`            | `pk`                        | Proxy kernel used with Spike for RISC-V.                                               |
| `NUM_HARTS`     | `1`                         | Number of harts (hardware threads) to simulate.                                        |

### Targets
- `default`: Compiles the code and runs it on both Spike (for RISC-V) and QEMU.
- `setup`: Prepares the run directory and any necessary subdirectories.
- `compile`: Compiles the source files into an ELF executable and disassembles it.
- `spike`: Runs the compiled RISC-V executable on the Spike simulator.
- `qemu`: Runs the compiled executable on QEMU (supports both ARM and RISC-V).
- `clean`: Cleans up the build and run directories.

### Usage
To use the Makefile, you can invoke it from the command line with the desired target and arguments. Specify the source file using `SRCS` argument:

```bash
make ARCH=riscv SRCS=tests/correctness/<test_name>/<file_name>.c
make ARCH=arm SRCS=tests/correctness/<test_name>/<file_name>.c
make clean
