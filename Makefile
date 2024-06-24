# Copyright 2024 10xEngineers
##############################################################################

MAKEFILE_DIR := $(abspath $(dir $(abspath $(lastword $(MAKEFILE_LIST)))))

##############################################################################
# Arguments

RISCV_PREFIX := riscv64-unknown-elf
QEMU :=
SPIKE := spike
PK := pk
SPIKE_ISA ?= rv64imafdcv

# Source file(s)
SRCS := program

# Directory where the .c file is present
ENV_DIR := ${MAKEFILE_DIR}/tests/correctness

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
ARCH_V               := 0
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
SUBD ?= default
RUN_DIR ?=
ifeq (,$(RUN_DIR))
  RUN_DIR_FLAG = 0
  RUN_DIR := ${ENV_DIR}/RUN/${SUBD}
else
  RUN_DIR_FLAG = 1
endif

# Timeout
TIMEOUT ?= 30

# Custom Library Directory
LIB_DIR ?=

##############################################################################
# Internal variables

ELF_FILE := ${RUN_DIR}/test.elf
DIS_FILE := ${RUN_DIR}/test.disasm

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

COMPILE_EXP = "riscv64-unknown-elf-gcc ${FRAMEWORK_CFLAGS} ${CARCH} ${COPT} ${CFLAGS2} ${FRAMEWORK_SRCS} ${COMMON_SRCS} ${ENV_SRCS} ${LIB_SRCS} ${LDFLAGS} -o $@"
DISM_EXP = "riscv64-unknown-elf-objdump ${OBJDUMP_FLAGS} $< > $@"

##############################################################################
# Targets

.PHONY: default setup test spike qemu clean



default: compile spike

setup: test
	mkdir -p ${RUN_DIR}

${ELF_FILE}: setup ${ENV_SRCS}
	@echo ""
	@echo ${COMPILE_EXP} > ${RUN_DIR}/compile_cmd_rerun.sh
	@chmod u+x ${RUN_DIR}/compile_cmd_rerun.sh
	${RISCV_PREFIX}-gcc ${FRAMEWORK_CFLAGS} ${CARCH} ${COPT} ${CFLAGS2} ${FRAMEWORK_SRCS} ${COMMON_SRCS} ${ENV_SRCS} ${LIB_SRCS} ${LDFLAGS} -o $@

${DIS_FILE}: ${ELF_FILE}
	@echo ""
	@echo ${DISM_EXP} > ${RUN_DIR}/dism_cmd_rerun.sh
	@chmod u+x ${RUN_DIR}/dism_cmd_rerun.sh
	${RISCV_PREFIX}-objdump ${OBJDUMP_FLAGS} $< > $@
	@echo "export DBG=${ELF_FILE}" > ${RUN_DIR}/temp_gdb_export.sh
	@echo "${RISCV_PREFIX}-gdb --exec=${realpath ${ELF_FILE}} --symbols=${realpath ${ELF_FILE}}" >> ${RUN_DIR}/temp_gdb_export.sh

compile: ${ELF_FILE} ${DIS_FILE}
	@echo ""

test:
# ifeq (1,${ARCHTEST_LISTER_ON})
	@echo ""
	@echo "RUN_DIR : "${RUN_DIR}
	@echo "ELF_FILE: "${ELF_FILE}
	@echo "DIS_FILE: "${DIS_FILE}
	@echo "SRCS    : "${SRCS}
	@echo "ENV_DIR : "${ENV_DIR_REALPATH}
	@echo "ENV_SRCS: "${ENV_SRCS}
	@echo "LIB_DIR : "${LIB_DIR_REALPATH}
	@echo "LIB_SRCS: "${LIB_SRCS}
	@echo "CFLAGS  : "${CFLAGS2}
	@echo "LDFLAGS : "${LDFLAGS}
	@echo "MARCH   : "${MARCH_ALL}
	@echo ""
# endif
ifndef SRCS
	$(error SRCS is undefined)
endif

spike:
	@echo ""
	$(SPIKE) --isa=$(SPIKE_ISA) -l --log-commits ${PK} ${ELF_FILE} 1> ${RUN_DIR}/$@.out 2> ${RUN_DIR}/$@.err

qemu:
	@echo ""
	$(QEMU)

clean:
	rm -f  $(MAKEFILE_DIR)/temp.sh
	rm -rf $(MAKEFILE_DIR)/LINT_RUN
	rm -rf $(ENV_DIR)/RUN


