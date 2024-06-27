# Copyright 2024 10xEngineers
##############################################################################

MAKEFILE_DIR := $(abspath $(dir $(abspath $(lastword $(MAKEFILE_LIST)))))

##############################################################################
# Arguments

RISCV_PREFIX := riscv64-unknown-elf
QEMU := qemu-riscv64
SPIKE := spike
PK := pk
SPIKE_ISA ?= rv64imafdcv

# Source file(s)
C_SRC = program.c
ASM_SRC = program.S

# Directory where the .c and .S files are present
TESTS_DIR := ${MAKEFILE_DIR}/tests/correctness

# Number of harts.
NUM_HARTS ?= 1

# Set to 0 to disable extension. Other value to enable.
ARCH_I               := 1
ARCH_M               := 1
ARCH_A               := 1
ARCH_F               := 1
ARCH_D               := 1
ARCH_C               := 1
ARCH_H               := 1
ARCH_CBO             := 1
ARCH_V               := 1
ARCH_ZIFENCEI        := 1
ARCH_B               := 1
ifneq ($(ARCH_B),0)
  ARCH_ZBC           := 1
endif
ARCH_ZCB             := 0
ARCH_ZHINTP          := 1
ARCH_ZFHMIN          := 1
ARCH_ZAWRS           := 1
ARCH_ZKT             := 1
ARCH_ZFA             := 1
ARCH_ZICOND          := 0
ARCH_VFBF            := 0
ARCH_ZIMOP           := 0
ARCH_ZCMOP           := 0
ARCH_V_CRYPTO        := 1

# Architecture options to compiler.
MARCH_ALL            :=
MARCH_RV             := rv64
MARCH_I              := i2p1
MARCH_M              := _m2p0
MARCH_A              := _a2p1
MARCH_F              := _f2p2
MARCH_D              := _d2p2
MARCH_C              := _c2p0
MARCH_V              := _v
MARCH_CBO            := _zicbom_zicbop_zicboz
MARCH_H              := _h1p0
MARCH_ZIFENCEI       := _zifencei
MARCH_B              := _zba2p0_zbb2p0_zbs2p0
MARCH_ZBC            := _zbc2p0
MARCH_ZCB            := _zcb
MARCH_ZIHINTP        := _zihintpause
MARCH_ZFHMIN         := _zfhmin
MARCH_ZAWRS          := _zawrs
MARCH_ZKT            := _zkt
MARCH_ZFA            := _zfa
MARCH_ZICOND         := _zicond
MARCH_VFBF           := _zvfbfmin_zvfbfwma
MARCH_ZIMOP          := _zimop
MARCH_ZCMOP          := _zcmop
MARCH_V_CRYPTO       := _zvknhb_zvkned_zvkg_zvbc_zvbb

MARCH_ALL := $(MARCH_RV)

ifneq ($(ARCH_I),0)
  MARCH_ALL := $(MARCH_ALL)$(MARCH_I)
endif
ifneq ($(ARCH_M),0)
  MARCH_ALL := $(MARCH_ALL)$(MARCH_M)
endif
ifneq ($(ARCH_A),0)
  MARCH_ALL := $(MARCH_ALL)$(MARCH_A)
endif
ifneq ($(ARCH_F),0)
  MARCH_ALL := $(MARCH_ALL)$(MARCH_F)
endif
ifneq ($(ARCH_D),0)
  MARCH_ALL := $(MARCH_ALL)$(MARCH_D)
endif
ifneq ($(ARCH_C),0)
  MARCH_ALL := $(MARCH_ALL)$(MARCH_C)
endif
ifneq ($(ARCH_V),0)
  MARCH_ALL := $(MARCH_ALL)$(MARCH_V)
endif
ifneq ($(ARCH_H),0)
  MARCH_ALL := $(MARCH_ALL)$(MARCH_H)
endif
ifneq ($(ARCH_CBO),0)
  MARCH_ALL := $(MARCH_ALL)$(MARCH_CBO)
endif
ifneq ($(ARCH_ZIFENCEI),0)
  MARCH_ALL := $(MARCH_ALL)$(MARCH_ZIFENCEI)
endif
ifneq ($(ARCH_B),0)
  MARCH_ALL := $(MARCH_ALL)$(MARCH_B)
endif
ifneq ($(ARCH_ZBC),0)
  ifneq ($(ARCH_B),0)
    MARCH_ALL := $(MARCH_ALL)$(MARCH_ZBC)
  endif
endif
ifneq ($(ARCH_ZCB),0)
  ifneq ($(ARCH_C),0)
    MARCH_ALL := $(MARCH_ALL)$(MARCH_ZCB)
  endif
endif
ifneq ($(ARCH_ZHINTP),0)
  MARCH_ALL := $(MARCH_ALL)$(MARCH_ZIHINTP)
endif
ifneq ($(ARCH_ZFHMIN),0)
  MARCH_ALL := $(MARCH_ALL)$(MARCH_ZFHMIN)
endif
ifneq ($(ARCH_ZAWRS),0)
  MARCH_ALL := $(MARCH_ALL)$(MARCH_ZAWRS)
endif
ifneq ($(ARCH_ZKT),0)
  MARCH_ALL := $(MARCH_ALL)$(MARCH_ZKT)
endif
ifneq ($(ARCH_ZFA),0)
  MARCH_ALL := $(MARCH_ALL)$(MARCH_ZFA)
endif
ifneq ($(ARCH_ZICOND),0)
  MARCH_ALL := $(MARCH_ALL)$(MARCH_ZICOND)
endif
ifneq ($(ARCH_VFBF),0)
  ifneq ($(ARCH_V),0)
    MARCH_ALL := $(MARCH_ALL)$(MARCH_VFBF)
  endif
endif
ifneq ($(ARCH_ZIMOP),0)
  MARCH_ALL := $(MARCH_ALL)$(MARCH_ZIMOP)
endif
ifneq ($(ARCH_ZCMOP),0)
  MARCH_ALL := $(MARCH_ALL)$(MARCH_ZCMOP)
endif
ifneq ($(ARCH_V_CRYPTO),0)
  ifneq ($(ARCH_V),0)
    MARCH_ALL := $(MARCH_ALL)$(MARCH_V_CRYPTO)
  endif
endif

CARCH = -march=$(MARCH_ALL)

# Optimization options to compiler.
COPT ?= -O2

# Additional options to compiler.
SEED ?=
ifeq (,${SEED})
  CFLAG_ENTROPY := -DENTROPY=$$RANDOM
else
  CFLAG_ENTROPY := -DENTROPY=${SEED}
endif

# Other cflags
CFLAGS ?=
ifneq ($(ARCH_V),0)
  CFLAGS_V := -DARCH_V
endif

# Final cflags
CFLAGS2 := ${CFLAGS_PROJECT} ${CFLAG_ENTROPY} ${CFLAGS} ${CFLAGS_V}

# Run and output directory
RUN_DIR ?=
ifeq (,$(RUN_DIR))
  RUN_DIR_FLAG = 0
  RUN_DIR := ${TESTS_DIR}/RUN
  SPIKE_DIR := ${RUN_DIR}/spike
  QEMU_DIR := ${RUN_DIR}/qemu
else
  RUN_DIR_FLAG = 1
endif

# Timeout
TIMEOUT ?= 30

# Custom Library Directory
LIB_DIR ?=

##############################################################################
# Internal variables

# Output binary and disassembly of c source file
ELF_C_FILE := ${SPIKE_DIR}/c_test.elf
DIS_C_FILE := ${SPIKE_DIR}/c_test.disasm

# Output binary and disassembly of assembly source file
ELF_ASM_FILE := ${SPIKE_DIR}/asm_test.elf
DIS_ASM_FILE := ${SPIKE_DIR}/asm_test.disasm

# Output log files of c source file
SPIKE_OUT_C := ${SPIKE_DIR}/c_spike.out
SPIKE_LOG_C := ${SPIKE_DIR}/c_spike.err

# Output log files of assembly source file
SPIKE_OUT_ASM := ${SPIKE_DIR}/asm_spike.out
SPIKE_LOG_ASM := ${SPIKE_DIR}/asm_spike.err

LIB_DIR_REALPATH := $(realpath $(LIB_DIR))
LIB_SRCS := \
	$(wildcard $(LIB_DIR_REALPATH)/*.c) \
	$(wildcard $(LIB_DIR_REALPATH)/*.S)

ENV_DIR_REALPATH := $(realpath $(ENV_DIR))
ENV_SRCS := \
	$(wildcard $(ENV_DIR_REALPATH)/*.c) \
	$(wildcard $(ENV_DIR_REALPATH)/*.S)

COMMON_DIR := $(MAKEFILE_DIR)/common
COMMON_SRCS := \

FRAMEWORK_CFLAGS := \
	-Werror \
	-mcmodel=medany \
	-g \
	-ggdb

OBJDUMP_FLAGS := \
	--all-headers \
	--demangle \
	--disassemble-all \
	--disassembler-options=no-aliases,numeric \
	--full-contents \
	--prefix-addresses \
	--line-numbers \
	--show-raw-insn \
	--source

#if given default LD
LD_DEFAULT?=
ifeq (,$(LD_DEFAULT))
#ENV_DIR has a higher linker file priority than LIB_DIR
	ifneq (,$(wildcard $(ENV_DIR_REALPATH)/link.ld))
		LDFLAGS = -T$(realpath $(ENV_DIR_REALPATH))/link.ld
	else
#LIB_DIR has a higher linker file priority than no linker file
		ifneq (,$(wildcard $(LIB_DIR_REALPATH)/link.ld))
			LDFLAGS = -T$(realpath $(LIB_DIR_REALPATH))/link.ld
		else
			LDFLAGS =
		endif
	endif
else
	LDFLAGS =
endif

##############################################################################
# Expansions

COMPILE_EXP_C = "riscv64-unknown-elf-gcc ${FRAMEWORK_CFLAGS} ${CARCH} ${COPT} ${CFLAGS2} ${FRAMEWORK_SRCS} ${COMMON_SRCS} ${ENV_SRCS} ${LIB_SRCS} ${LDFLAGS} ${TESTS_DIR}/${C_SRC} -o $@"
DISM_EXP_C = "riscv64-unknown-elf-objdump ${OBJDUMP_FLAGS} $< > $@"

COMPILE_EXP_ASM = "riscv64-unknown-elf-gcc ${FRAMEWORK_CFLAGS} ${CARCH} ${COPT} ${CFLAGS2} ${FRAMEWORK_SRCS} ${COMMON_SRCS} ${ENV_SRCS} ${LIB_SRCS} ${LDFLAGS} -nostartfiles ${TESTS_DIR}/${ASM_SRC} -o $@"
DISM_EXP_ASM = "riscv64-unknown-elf-objdump ${OBJDUMP_FLAGS} $< > $@"

##############################################################################
# Targets

.PHONY: default setup test spike qemu clean



default: compile spike

setup: test
	mkdir -p ${SPIKE_DIR}

# Compile .c Source File
${ELF_C_FILE}: setup ${TESTS_DIR}/${C_SRC}
	@echo ""
	@echo ${COMPILE_EXP_C} > ${SPIKE_DIR}/c_compile_cmd_rerun.sh
	@chmod u+x ${SPIKE_DIR}/c_compile_cmd_rerun.sh
	${RISCV_PREFIX}-gcc ${FRAMEWORK_CFLAGS} ${CARCH} ${COPT} ${CFLAGS2} ${FRAMEWORK_SRCS} ${COMMON_SRCS} ${ENV_SRCS} ${LIB_SRCS} ${LDFLAGS} ${TESTS_DIR}/${C_SRC} -o $@

${DIS_C_FILE}: ${ELF_C_FILE}
	@echo ""
	@echo ${DISM_EXP_C} > ${SPIKE_DIR}/c_dism_cmd_rerun.sh
	@chmod u+x ${SPIKE_DIR}/c_dism_cmd_rerun.sh
	${RISCV_PREFIX}-objdump ${OBJDUMP_FLAGS} $< > $@
	@echo "export DBG=${ELF_C_FILE}" > ${SPIKE_DIR}/c_temp_gdb_export.sh
	@echo "${RISCV_PREFIX}-gdb --exec=${realpath ${ELF_C_FILE}} --symbols=${realpath ${ELF_C_FILE}}" >> ${SPIKE_DIR}/c_temp_gdb_export.sh

compile_c: ${ELF_C_FILE} ${DIS_C_FILE}
	@echo ""

# Compile .S Source File
${ELF_ASM_FILE}: setup ${TESTS_DIR}/${ASM_SRC}
	@echo ""
	@echo ${COMPILE_EXP_ASM} > ${SPIKE_DIR}/asm_compile_cmd_rerun.sh
	@chmod u+x ${SPIKE_DIR}/asm_compile_cmd_rerun.sh
	${RISCV_PREFIX}-gcc ${FRAMEWORK_CFLAGS} ${CARCH} ${COPT} ${CFLAGS2} ${FRAMEWORK_SRCS} ${COMMON_SRCS} ${ENV_SRCS} ${LIB_SRCS} ${LDFLAGS} -nostartfiles ${TESTS_DIR}/${ASM_SRC} -o $@

${DIS_ASM_FILE}: ${ELF_ASM_FILE}
	@echo ""
	@echo ${DISM_EXP_ASM} > ${SPIKE_DIR}/asm_dism_cmd_rerun.sh
	@chmod u+x ${SPIKE_DIR}/asm_dism_cmd_rerun.sh
	${RISCV_PREFIX}-objdump ${OBJDUMP_FLAGS} $< > $@
	@echo "export DBG=${ELF_ASM_FILE}" > ${SPIKE_DIR}/asm_temp_gdb_export.sh
	@echo "${RISCV_PREFIX}-gdb --exec=${realpath ${ELF_ASM_FILE}} --symbols=${realpath ${ELF_ASM_FILE}}" >> ${SPIKE_DIR}/asm_temp_gdb_export.sh

compile_asm: ${ELF_ASM_FILE} ${DIS_ASM_FILE}
	@echo ""

compile: compile_c compile_asm

test:
# ifeq (1,${ARCHTEST_LISTER_ON})
	@echo ""
	@echo "RUN_DIR		: "${RUN_DIR}
	@echo "SPIKE_DIR	: "${SPIKE_DIR}
	@echo "QEMU_DIR		: "${QEMU_DIR}
	@echo "ELF_C_FILE	: "${ELF_C_FILE}
	@echo "DIS_C_FILE	: "${DIS_C_FILE}
	@echo "ELF_ASM_FILE	: "${ELF_ASM_FILE}
	@echo "DIS_ASM_FILE	: "${DIS_ASM_FILE}
	@echo "C_SRC     	: "${C_SRC}
	@echo "ASM_SRC     	: "${ASM_SRC}
	@echo "ENV_DIR   	: "${ENV_DIR_REALPATH}
	@echo "ENV_SRCS  	: "${ENV_SRCS}
	@echo "LIB_DIR   	: "${LIB_DIR_REALPATH}
	@echo "LIB_SRCS  	: "${LIB_SRCS}
	@echo "CFLAGS    	: "${CFLAGS2}
	@echo "LDFLAGS   	: "${LDFLAGS}
	@echo "MARCH     	: "${MARCH_ALL}
	@echo ""
# endif
ifndef C_SRC
	$(error C_SRC is undefined)
endif

# Run C Binary on Spike
spike_c:
	@echo ""
	$(SPIKE) --isa=$(SPIKE_ISA) -l --log-commits ${PK} ${ELF_C_FILE} 1> ${SPIKE_OUT_C} 2> ${SPIKE_LOG_C}

# Run Assembly Binary on Spike
spike_asm:
	@echo ""
	$(SPIKE) --isa=$(SPIKE_ISA) -l --log-commits ${PK} ${ELF_ASM_FILE} 1> ${SPIKE_OUT_ASM} 2> ${SPIKE_LOG_ASM}

spike: spike_c spike_asm

qemu:
	@echo ""
	$(QEMU)

clean:
	rm -f  $(MAKEFILE_DIR)/temp.sh
	rm -rf $(MAKEFILE_DIR)/LINT_RUN
	rm -rf $(TESTS_DIR)/RUN


