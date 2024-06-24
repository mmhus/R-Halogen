// Copyright 2024 10xEngineers

#ifndef RISCV_CSR_ENCODING_H
#define RISCV_CSR_ENCODING_H

#include "platform.h"

#ifndef __riscv_xlen
#define __riscv_xlen 64
#endif

#define BYTE_ALIGMENT           0
#define HALF_WORD_ALIGNMENT     1
#define WORD_ALIGNMENT          2
#define DOUBLE_WORD_ALIGNMENT   3

#define ILLEGAL_INSTRUCTION 0xffffffff

#define ALL_ONE -1

#define str(x)  #x
#define xstr(x) str(x)

/**
 * @brief MSTATUS bits
 *
*/
#define MSTATUS_UIE         0x00000001
#define MSTATUS_SIE         0x00000002
#define MSTATUS_HIE         0x00000004
#define MSTATUS_MIE         0x00000008
#define MSTATUS_UPIE        0x00000010
#define MSTATUS_SPIE        0x00000020
#define MSTATUS_UBE         0x00000040
#define MSTATUS_MPIE        0x00000080
#define MSTATUS_SPP         0x00000100
#define MSTATUS_VS          0x00000600
#define MSTATUS_MPP         0x00001800
#define MSTATUS_FS          0x00006000
#define MSTATUS_XS          0x00018000
#define MSTATUS_MPRV        0x00020000
#define MSTATUS_SUM         0x00040000
#define MSTATUS_MXR         0x00080000
#define MSTATUS_TVM         0x00100000
#define MSTATUS_TW          0x00200000
#define MSTATUS_TSR         0x00400000
#define MSTATUS32_SD        0x80000000
#define MSTATUS_MPV         0x0000008000000000
#define MSTATUS_UXL         0x0000000300000000
#define MSTATUS_SXL         0x0000000C00000000
#define MSTATUS64_SD        0x8000000000000000

/**
 * @brief MSTATUS MPP bits
 *
*/
#define MPP_M                MSTATUS_MPP
#define MPP_S               (MPP_M & (MPP_M >> 1))
#define MPP_HS               MPP_S
#define MPP_VS              (MPP_S | MSTATUS_MPV)
#define MPP_U               (MPP_M & ~MPP_M)
#define MPP_VU              (MPP_U | MSTATUS_MPV)

/**
 * @brief MSTATUS SPP bits
 *
*/
#define SPP_S                MSTATUS_SPP
#define SPP_HS               SPP_S
#define SPP_VS              (SPP_S | MSTATUS_MPV)
#define SPP_U               (SPP_S & ~SPP_S)
#define SPP_VU              (SPP_U | MSTATUS_MPV)

/**
 * @brief Vector Configurations
 *
*/
#define VLENB (VLEN/8)

/**
 * @brief VTYPE bits
 *
*/
#define VTYPE_VLMUL         (0x7 << VTYPE_VLMUL_SHIFT)
#define VTYPE_VSEW          (0x7 << VTYPE_VSEW_SHIFT)
#define VTYPE_VTA           (0x1 << VTYPE_VTA_SHIFT)
#define VTYPE_VMA           (0x1 << VTYPE_VMA_SHIFT)
#define VTYPE_VILL          (0x1ULL << VTYPE_VILL_SHIFT)

/**
 * @brief VTYPE shift value
 *
*/
#define VTYPE_VLMUL_SHIFT     0x0
#define VTYPE_VSEW_SHIFT      0x3
#define VTYPE_VTA_SHIFT       0x6
#define VTYPE_VMA_SHIFT       0x7
#define VTYPE_VILL_SHIFT      (__riscv_xlen -1)

/**
 * @brief Writable bits of vector CSRs
 *
*/
#define VSTART_MAX 0x1ff
#define VXSAT_MAX 0x1
#define VXRM_MAX 0x3
#define VCSR_MAX 0x7

/**
 * @brief Initial value of vector CSR
 *
*/
#define VTYPE_INITIAL_VALUE VTYPE_VILL
#define VL_INITIAL_VALUE SET_0
#define VLENB_VALUE VLENB

/**
 * @brief MTVEC bits
 *
*/
#define MTVEC_BASE          0xfffffffffffffffc
#define MTVEC_MODE          0x0000000000000003
#define MTVEC_MODE_DIRECT   0x0000000000000000
#define MTVEC_MODE_VECTORED 0x0000000000000001

/**
 * @brief STVEC bits
 *
*/
#define STVEC_BASE          MTVEC_BASE
#define STVEC_MODE          MTVEC_MODE
#define STVEC_MODE_DIRECT   MTVEC_MODE_DIRECT
#define STVEC_MODE_VECTORED MTVEC_MODE_VECTORED

/**
 * @brief MCAUSE INTERRUPT
 *
*/
#define MCAUSE_INTERRUPT    0x8000000000000000
#define MCAUSE_CODE         0x7fffffffffffffff

/**
 * @brief SCAUSE INTERRUPT
 *
*/
#define SCAUSE_INTERRUPT    MCAUSE_INTERRUPT
#define SCAUSE_CODE         MCAUSE_CODE

/**
 * @brief CAUSE INTERRUPT bits
 *
*/
#define CAUSE_IRQ_S_SOFT    (MCAUSE_INTERRUPT | IRQ_S_SOFT)
#define CAUSE_IRQ_S_TIMER   (MCAUSE_INTERRUPT | IRQ_S_TIMER)
#define CAUSE_IRQ_S_EXT     (MCAUSE_INTERRUPT | IRQ_S_EXT)
#define CAUSE_IRQ_M_SOFT    (MCAUSE_INTERRUPT | IRQ_M_SOFT)
#define CAUSE_IRQ_M_TIMER   (MCAUSE_INTERRUPT | IRQ_M_TIMER)
#define CAUSE_IRQ_M_EXT     (MCAUSE_INTERRUPT | IRQ_M_EXT)
#define CAUSE_IRQ_LCOF      (MCAUSE_INTERRUPT | IRQ_LCOF)
#define CAUSE_IRQ_VS_SOFT   (MCAUSE_INTERRUPT | IRQ_VS_SOFT)
#define CAUSE_IRQ_VS_TIMER  (MCAUSE_INTERRUPT | IRQ_VS_TIMER)
#define CAUSE_IRQ_VS_EXT    (MCAUSE_INTERRUPT | IRQ_VS_EXT)
#define CAUSE_IRQ_SG_EXT    (MCAUSE_INTERRUPT | IRQ_SG_EXT)
#define CAUSE_IRQ_LCOF      (MCAUSE_INTERRUPT | IRQ_LCOF)
#define CAUSE_IRQ_TSSTOP    (MCAUSE_INTERRUPT | IRQ_TSSTOP)

#define CAUSE_FATAL_SYSTEM_ERROR (MCAUSE_INTERRUPT | 0x1)
#define CAUSE_SOFT_RESET 0x1
#define CAUSE_HARD_RESET 0x0

/**
 * @brief SSTATUS bits
 *
*/
#define SSTATUS_UIE         0x00000001
#define SSTATUS_SIE         0x00000002
#define SSTATUS_UPIE        0x00000010
#define SSTATUS_SPIE        0x00000020
#define SSTATUS_SPP         0x00000100
#define SSTATUS_VS          0x00000600
#define SSTATUS_FS          0x00006000
#define SSTATUS_XS          0x00018000
#define SSTATUS_SUM         0x00040000
#define SSTATUS_MXR         0x00080000
#define SSTATUS32_SD        0x80000000
#define SSTATUS_UXL         0x0000000300000000
#define SSTATUS64_SD        0x8000000000000000

/**
 * @brief HSTATUS bits
 *
*/
#define HSTATUS_VSBE        0x0000000000000020
#define HSTATUS_GVA         0x0000000000000040
#define HSTATUS_SPV         0x0000000000000080
#define HSTATUS_SPVP        0x0000000000000100
#define HSTATUS_HU          0x0000000000000200
#define HSTATUS_VGEIN       0x000000000003f000
#define HSTATUS_VTVM        0x0000000000100000
#define HSTATUS_VTW         0x0000000000200000
#define HSTATUS_VTSR        0x0000000000400000
#define HSTATUS_VSXL        0x0000000300000000

#define USTATUS_UIE         0x00000001
#define USTATUS_UPIE        0x00000010

#define XSTATUS_FS_INIT  (MSTATUS_FS & (MSTATUS_FS >> 1))
#define XSTATUS_FS_CLEAN (MSTATUS_FS & (MSTATUS_FS << 1))
#define XSTATUS_FS_DIRTY  MSTATUS_FS

#define HSTATUS_VGEIN_SHIFT 12

/**
 * @brief DCSR bits
 *
*/
#define DCSR_XDEBUGVER      (3U << 30)
#define DCSR_NDRESET        (1 << 29)
#define DCSR_FULLRESET      (1 << 28)
#define DCSR_DEBUGVER       (0xfU << 28)
#define DCSR_EBREAKVS       (1 << 17)
#define DCSR_EBREAKVU       (1 << 16)
#define DCSR_EBREAKM        (1 << 15)
#define DCSR_EBREAKS        (1 << 13)
#define DCSR_EBREAKU        (1 << 12)
#define DCSR_STEPIE         (1 << 11)
#define DCSR_STOPCOUNT      (1 << 10)
#define DCSR_STOPTIME       (1 << 9)
#define DCSR_CAUSE          (7 << 6)
#define DCSR_V              (1 << 5)
#define DCSR_MPRVEN         (1 << 4)
#define DCSR_NMIP           (1 << 3)
#define DCSR_STEP           (1 << 2)
#define DCSR_PRV            (3 << 0)

/**
 * @brief DCSR CAUSE bits
 *
*/
#define DCSR_CAUSE_NONE     0
#define DCSR_CAUSE_SWBP     1
#define DCSR_CAUSE_HWBP     2
#define DCSR_CAUSE_DEBUGINT 3
#define DCSR_CAUSE_STEP     4
#define DCSR_CAUSE_HALT     5

#define DCSR_CAUSE_SHIFT    6

/**
 * @brief MCONTROL
 *
*/
#define MCONTROL_TYPE(xlen)    (0xfULL << ((xlen)-4))
#define MCONTROL_TYPE_6(xlen)  (0x6ULL << ((xlen)-4))
#define MCONTROL_TYPE_3(xlen)  (0x3ULL << ((xlen)-4))
#define MCONTROL_DMODE(xlen)   (1ULL << ((xlen)-5))
#define MCONTROL_MASKMAX(xlen) (0x3fULL << ((xlen)-11))
#define MCONTROL_MASKMAX6 32
#define MCONTROL6_TYPE_VALUE 6

#define MCONTROL_UNCERTAIN                (1 << 26)
#define MCONTROL_HIT1                     (1 << 25)  // Not implemented
#define MCONTROL_VS                       (1 << 24)
#define MCONTROL_VU                       (1 << 23)
#define MCONTROL_HIT0                     (1 << 22)  // Not implemented
#define MCONTROL_SELECT                   (1 << 21)
#define MCONTROL_SIZE_ALL_SIZE_ACCESS     (0x0 << 16)
#define MCONTROL_SIZE_1_BYTE_ACCESS       (0x1 << 16)
#define MCONTROL_SIZE_2_BYTE_ACCESS       (0x2 << 16)
#define MCONTROL_SIZE_4_BYTE_ACCESS       (0x3 << 16)
#define MCONTROL_SIZE_8_BYTE_ACCESS       (0x5 << 16)
#define MCONTROL_ACTION                   (0xf << 12)
#define MCONTROL_CHAIN                    (1 << 11)
#define MCONTROL_MATCH                    (0xf << 7)
#define MCONTROL_M                        (1 << 6)
#define MCONTROL_UNCERTAINEN              (1 << 5)
#define MCONTROL_S                        (1 << 4)
#define MCONTROL_U                        (1 << 3)
#define MCONTROL_EXECUTE                  (1 << 2)
#define MCONTROL_STORE                    (1 << 1)
#define MCONTROL_LOAD                     (1 << 0)

#define MCONTROL_TYPE_NONE      0
#define MCONTROL_TYPE_MATCH     2

/**
 * @brief TRIGGER ACTION bits
 *
*/
#define TRIGGER_ACTION_BREAKPOINT    0
#define TRIGGER_ACTION_DEBUG_MODE    1
#define TRIGGER_ACTION_TRACE_START   2
#define TRIGGER_ACTION_TRACE_STOP    3
#define TRIGGER_ACTION_TRACE_NOTIFY  4
#define TRIGGER_ACTION_EXT_0         8
#define TRIGGER_ACTION_EXT_1         9

#define MCONTROL_ACTION_SHIFT             12

#define MCONTROL_MATCH_EQUAL     0
#define MCONTROL_MATCH_NAPOT     1
#define MCONTROL_MATCH_GE        2
#define MCONTROL_MATCH_LT        3
#define MCONTROL_MATCH_MASK_LOW  4
#define MCONTROL_MATCH_MASK_HIGH 5

/**
 * @brief TEXTRA bits
 *
*/
#define TEXTRA_MHVALUE        (0x1fffULL << 51)
#define TEXTRA_MHSELECT       (0x7ULL << 48)
#define TEXTRA_SBYTEMASK      (0x1fULL << 36)
#define TEXTRA_SVALUE         (0x3ffffffffULL << 2)
#define TEXTRA_SSELECT        (3 << 0)
#define TEXTRA_SSELECT_LSB    0
#define TEXTRA_SVALUE_LSB     2
#define TEXTRA_MHSELECT_LSB   48
#define TEXTRA_MHVALUE_LSB    51

/**
 * @brief ICOUNT bits
 *
*/
#define ICOUNT_TYPE(xlen)     (0xfULL << ((xlen)-4))
#define ICOUNT_TYPE_VALUE     3
#define ICOUNT_TYPE_3(xlen)   (0x3ULL << ((xlen)-4))
#define ICOUNT_DMODE(xlen)    (0x1ULL << ((xlen)-5))
#define ICOUNT_VS             (1 << 26)
#define ICOUNT_VU             (1 << 25)
#define ICOUNT_HIT            (1 << 24)
#define ICOUNT_COUNT          (0xf << 10)
#define ICOUNT_COUNT_LSB      10
#define ICOUNT_M              (1 << 9)
#define ICOUNT_PENDING        (1 << 8)
#define ICOUNT_PENDING_LSB    8
#define ICOUNT_S              (1 << 7)
#define ICOUNT_U              (1 << 6)
#define ICOUNT_ACTION         (0xf << 0)

/**
 * @brief TRIGGER bits
 *
*/
#define TRIGGER_EXECUTE_MIN     0
#define TRIGGER_EXECUTE_MAX     5
#define TRIGGER_LOAD_STORE_MIN  6
#define TRIGGER_LOAD_STORE_MAX  9
#define TRIGGER_NUM_0     0
#define TRIGGER_NUM_1     1
#define TRIGGER_NUM_2     2
#define TRIGGER_NUM_3     3
#define TRIGGER_NUM_4     4
#define TRIGGER_NUM_5     5
#define TRIGGER_NUM_6     6
#define TRIGGER_NUM_7     7
#define TRIGGER_NUM_8     8
#define TRIGGER_NUM_9     9
#define TRIGGER_COUNT           10
#define TRIGGER_INTERRUPT       11
#define TRIGGER_EXCEPTION       12
#define TRIGGER_EXTERNAL_MIN    13
#define TRIGGER_EXTERNAL_MAX    14

/**
 * @brief ITRIGGER bits
 *
*/
#define ITRIGGER_TYPE_4(xlen)   (0x4ULL << ((xlen)-4))
#define ITRIGGER_TYPE_VALUE     4
#define ITRIGGER_DMODE(xlen)    (0x1ULL << ((xlen)-5))
#define ITRIGGER_HIT            (0x1ULL << ((xlen)-6))
#define ITRIGGER_VS             (1 << 12)
#define ITRIGGER_VU             (1 << 11)
#define ITRIGGER_M              (1 << 9)
#define ITRIGGER_S              (1 << 7)
#define ITRIGGER_U              (1 << 6)
#define ITRIGGER_ACTION         (0xf << 0)

/**
 * @brief ETRIGGER bits
 *
*/
#define ETRIGGER_TYPE_5(xlen)   (0x5ULL << ((xlen)-4))
#define ETRIGGER_TYPE_VALUE     5
#define ETRIGGER_DMODE(xlen)    (0x1ULL << ((xlen)-5))
#define ETRIGGER_HIT            (0x1ULL << ((xlen)-6))
#define ETRIGGER_VS             (1 << 12)
#define ETRIGGER_VU             (1 << 11)
#define ETRIGGER_M              (1 << 9)
#define ETRIGGER_S              (1 << 7)
#define ETRIGGER_U              (1 << 6)
#define ETRIGGER_ACTION         (0xf << 0)

/**
 * @brief TMEXTTRIGGER bits
 *
*/
#define TMEXTTRIGGER_TYPE_7(xlen)   (0x7ULL << ((xlen)-4))
#define TMEXTTRIGGER_TYPE_VALUE     7
#define TMEXTTRIGGER_DMODE(xlen)    (0x1ULL << ((xlen)-5))
#define TMEXTTRIGGER_HIT            (0x1ULL << ((xlen)-6))
#define TMEXTTRIGGER_INTCTL         (1 << 22)
#define TMEXTTRIGGER_SELECT         (0xf << 6)
#define TMEXTTRIGGER_ACTION         (0xf << 0)

#define TMEXTTRIGGER_ACTION_OFFSET   (uint64_t)0
#define TMEXTTRIGGER_SELECT_OFFSET   (uint64_t)6

#define TMEXTTRIGGER_TRIGGER_INPUT_0 (uint64_t)0b0001
#define TMEXTTRIGGER_TRIGGER_INPUT_1 (uint64_t)0b0010

/**
 * @brief MENVCFG bits
 *
*/
#define MENVCFG_FIOM        0x0000000000000001
#define MENVCFG_CBIE        0x0000000000000030
#define MENVCFG_CBCFE       0x0000000000000040
#define MENVCFG_CBZE        0x0000000000000080
#define MENVCFG_PBMTE       0x4000000000000000
#define MENVCFG_STCE        0x8000000000000000

/**
 * @brief HENVCFG bits
 *
*/
#define HENVCFG_FIOM        MENVCFG_FIOM
#define HENVCFG_CBIE        MENVCFG_CBIE
#define HENVCFG_CBCFE       MENVCFG_CBCFE
#define HENVCFG_CBZE        MENVCFG_CBZE
#define HENVCFG_PBMTE       MENVCFG_PBMTE
#define HENVCFG_VSTCE       MENVCFG_STCE

/**
 * @brief SENVCFG bits
 *
*/
#define SENVCFG_FIOM        MENVCFG_FIOM
#define SENVCFG_CBIE        MENVCFG_CBIE
#define SENVCFG_CBCFE       MENVCFG_CBCFE
#define SENVCFG_CBZE        MENVCFG_CBZE

/**
 * @brief MIP bits
 *
*/
#define MIP_USIP            (1 << IRQ_U_SOFT)
#define MIP_SSIP            (1 << IRQ_S_SOFT)
#define MIP_VSSIP           (1 << IRQ_VS_SOFT)
#define MIP_MSIP            (1 << IRQ_M_SOFT)
#define MIP_UTIP            (1 << IRQ_U_TIMER)
#define MIP_STIP            (1 << IRQ_S_TIMER)
#define MIP_VSTIP           (1 << IRQ_VS_TIMER)
#define MIP_MTIP            (1 << IRQ_M_TIMER)
#define MIP_UEIP            (1 << IRQ_U_EXT)
#define MIP_SEIP            (1 << IRQ_S_EXT)
#define MIP_VSEIP           (1 << IRQ_VS_EXT)
#define MIP_MEIP            (1 << IRQ_M_EXT)
#define MIP_SGEIP           (1 << IRQ_SG_EXT)
#define MIE_SGEIE           (1 << IRQ_SG_EXT)
#define MIP_LCOFIP          (1 << IRQ_LCOF)
#define MIP_TSSTOPIP        (1 << IRQ_TSSTOP)

/**
 * @brief SUPPORTED INTERRUPTS
 *
*/
#define SUPPORTED_INTERRUPTS (MIP_MSIP  | MIP_MTIP   | MIP_MEIP  | \
                              MIP_SSIP  | MIP_STIP   | MIP_SEIP  | \
                              MIP_VSSIP | MIP_VSTIP  | MIP_VSEIP | \
                              MIP_SGEIP | MIP_LCOFIP | MIP_TSSTOPIP)

/**
 * @brief SUPPORTED INTERRUPTS HYPERVISOR DISABLED
 *
*/
#define SUPPORTED_INTERRUPTS_HYPERVISOR_DISABLED (MIP_MSIP   | MIP_MTIP | MIP_MEIP | \
                                                  MIP_SSIP   | MIP_STIP | MIP_SEIP | \
                                                  MIP_LCOFIP | MIP_TSSTOPIP)

/**
 * @brief SIP bits
 *
*/
#define SIP_SSIP     MIP_SSIP
#define SIP_STIP     MIP_STIP
#define SIP_SEIP     MIP_SEIP
#define SIP_LCOFIP   MIP_LCOFIP
#define SIP_TSSTOPIP MIP_TSSTOPIP

/**
 * @brief HIP bits
 *
*/
#define HIP_VSSIP    MIP_VSSIP
#define HIP_VSTIP    MIP_VSTIP
#define HIP_VSEIP    MIP_VSEIP
#define HIP_SGEIP    MIP_SGEIP

/**
 * @brief HVIP bits
 *
*/
#define HVIP_VSSIP    MIP_VSSIP
#define HVIP_VSTIP    MIP_VSTIP
#define HVIP_VSEIP    MIP_VSEIP

/**
 * @brief SUPERVISOR SUPPORTED INTERRUPTS
 *
*/
#define SUPERVISOR_SUPPORTED_INTERRUPTS (SIP_SSIP | SIP_STIP | SIP_SEIP | SIP_LCOFIP | SIP_TSSTOPIP)

/**
 * @brief HYPERVISOR SUPPORTED INTERRUPTS
 *
*/
#define HYPERVISOR_SUPPORTED_INTERRUPTS (MIP_VSSIP | MIP_VSTIP | MIP_VSEIP | MIP_SGEIP)

/**
 * @brief HYPERVISOR MISA bits
 *
*/
#define HYPERVISOR_MISA 7
#define HYPERVISOR_MISA_MASK (1 << HYPERVISOR_MISA)

/**
 * @brief PRIVILEGE modes
 *
*/
#define PRV_U 0
#define PRV_S 1
#define PRV_H 2
#define PRV_M 3

/**
 * @brief SATP32 bits
 *
*/
#define SATP32_MODE 0x80000000
#define SATP32_ASID 0x7FC00000
#define SATP32_PPN  0x003FFFFF

/**
 * @brief SATP64 bits
 *
*/
#define SATP64_MODE 0xF000000000000000
// #define SATP64_ASID 0x0FFFF00000000000  Affected by platform.h
#define SATP64_PPN  0x00000FFFFFFFFFFF

/**
 * @brief SATP different modes
 *
*/
#define SATP_MODE_OFF  0
#define SATP_MODE_SV32 1
#define SATP_MODE_SV39 8
#define SATP_MODE_SV48 9
#define SATP_MODE_SV57 10
#define SATP_MODE_SV64 11

/**
 * @brief SATP64 bits
 *
*/
#define SATP64_ASID_OFFSET  44
#define SATP64_MODE_OFFSET  60
#define HGATP64_VMID_OFFSET 44

/**
 * @brief The macro HGATP64_VMID is used to define the value of the VMID field in the HGATP address.
 *
*/
#define HGATP64_VMID (((1ULL << VMIDLEN) - 1) << HGATP64_VMID_OFFSET)

/**
 * @brief PPN offsets
 *
*/
#define PPN_3_OFFSET 39
#define PPN_2_OFFSET 30
#define PPN_1_OFFSET 21
#define PPN_0_OFFSET 12

/**
 * @brief PMP CFG
 *
*/
#define PMP_CFG_MASK 0xff
#define PMP_CFG_PER_REG 8

/**
 * @brief PPMP permissions
 *
*/
#define PMP_R     0x01
#define PMP_W     0x02
#define PMP_X     0x04
#define PMP_A     0x18
#define PMP_L     0x80
#define PMP_SHIFT 2

/**
 * @brief PPMP regions
 *
*/
#define PMP_TOR   0x08
#define PMP_NA4   0x10
#define PMP_NAPOT 0x18

/**
 * @brief MSECCFG bits
 *
*/
#define MSECCFG_MML  0x1
#define MSECCFG_MMWP 0x2
#define MSECCFG_RLB  0x4

/**
 * @brief IRQ modes
 *
*/
#define IRQ_U_SOFT   0
#define IRQ_S_SOFT   1
#define IRQ_VS_SOFT  2
#define IRQ_M_SOFT   3
#define IRQ_U_TIMER  4
#define IRQ_S_TIMER  5
#define IRQ_VS_TIMER 6
#define IRQ_M_TIMER  7
#define IRQ_U_EXT    8
#define IRQ_S_EXT    9
#define IRQ_VS_EXT   10
#define IRQ_M_EXT    11
#define IRQ_SG_EXT   12
#define IRQ_LCOF     13
#ifdef VT1
  #define IRQ_TSSTOP   18
#else
  #define IRQ_TSSTOP   17
#endif
// #define IRQ_COP      12 //new names
// #define IRQ_HOST     13

#define DEFAULT_RSTVEC     0x00001000
#define CLINT_SIZE         0x000c0000
#define EXT_IO_BASE        0x40000000
#define DRAM_BASE          0x80000000

/**
 * @brief HPM Macros
 *
*/
#define MHPMCOUNTER_MAXVALUE         0x0000FFFFFFFFFFFF

#define HPM_EVENT_MASK                  0xFF
#define HPM_EVENT_INSTR_RETIRE          0x12
#define HPM_EVENT_BUS_CYCLES            0x07
#define HPM_EVENT_REF_CPU_CYCLES        0x0A
#define HPM_EVENT_PIPE_STALL_EVENT      0x20
#define HPM_EVENT_DL1_ACCESS            0x19
#define HPM_EVENT_DISP_COUNT3           0x48
#define HPM_EVENT_ISSUE_COUNT_BU        0x64
#define HPM_EVENT_FP_ISSUE_COUNT        0x70
#define HPM_EVENT_TABLE_WALK_REQUESTS   0x80
#define HPM_EVENT_DTB_ACCESS_EVENT      0x90
#define HPM_EVENT_PRU_RETIRE_EVENT      0x34
#define HPM_EVENT_HW_NO_EVENT           0x00

#define CNT_OVF_ACTION_NONE          (uint64_t)0b00
#define CNT_OVF_ACTION_TRIG_0        (uint64_t)0b01
#define CNT_OVF_ACTION_TRIG_1        (uint64_t)0b10

#define EXT_TRIGGER_NONE             (uint64_t)0b000
#define EXT_TRIGGER_OVERFLOW_0       (uint64_t)0b001
#define EXT_TRIGGER_OVERFLOW_1       (uint64_t)0b010
#define EXT_TRIGGER_DEBUG_0          (uint64_t)0b100
#define EXT_TRIGGER_DEBUG_1          (uint64_t)0b101

#define HPC_ACTIVE                   (uint64_t)0
#define HPC_INACTIVE                 (uint64_t)1

/**
 * @brief MHPMEVENT registers
 *
*/
#define MHPMEVENT_SELECT_OFFSET      (uint64_t)0
#define MHPMEVENT_FILTER_OFFSET      (uint64_t)8
#define MHPMEVENT_TYPE_OFFSET        (uint64_t)16
#define MHPMEVENT_INACTIVE_OFFSET    (uint64_t)31
#define MHPMEVENT_OVF_ACTION_OFFSET  (uint64_t)32
#define MHPMEVENT_STOP_EVENT_OFFSET  (uint64_t)34
#define MHPMEVENT_START_EVENT_OFFSET (uint64_t)37
#define MHPMEVENT_VUINH_OFFSET       (uint64_t)58
#define MHPMEVENT_VSINH_OFFSET       (uint64_t)59
#define MHPMEVENT_UINH_OFFSET        (uint64_t)60
#define MHPMEVENT_SINH_OFFSET        (uint64_t)61
#define MHPMEVENT_MINH_OFFSET        (uint64_t)62
#define MHPMEVENT_OF_OFFSET          (uint64_t)63

#define MHPMEVENT_INACTIVE           (1ULL << MHPMEVENT_INACTIVE_OFFSET)
#define MHPMEVENT_VUINH              (1ULL << MHPMEVENT_VUINH_OFFSET)
#define MHPMEVENT_VSINH              (1ULL << MHPMEVENT_VSINH_OFFSET)
#define MHPMEVENT_UINH               (1ULL << MHPMEVENT_UINH_OFFSET)
#define MHPMEVENT_SINH               (1ULL << MHPMEVENT_SINH_OFFSET)
#define MHPMEVENT_MINH               (1ULL << MHPMEVENT_MINH_OFFSET)
#define MHPMEVENT_OF                 (1ULL << MHPMEVENT_OF_OFFSET)

/**
 * @brief MCOUNTINHIBIT register
 *
*/
#define COUNTEN_MASK          0xffffffffffffffff
#define MCOUNTINHIBIT_CY      (1<<0)
#define MCOUNTINHIBIT_IR      (1<<2)
#define MCOUNTINHIBIT_HPM3    (1<<3)
#define MCOUNTINHIBIT_HPM4    (1<<4)
#define MCOUNTINHIBIT_HPM5    (1<<5)
#define MCOUNTINHIBIT_HPM6    (1<<6)
#define MCOUNTINHIBIT_HPM7    (1<<7)
#define MCOUNTINHIBIT_HPM8    (1<<8)
#define MCOUNTINHIBIT_HPM9    (1<<9)
#define MCOUNTINHIBIT_HPM10   (1<<10)
#define MCOUNTINHIBIT_HPM11   (1<<11)
#define MCOUNTINHIBIT_HPM12   (1<<12)
#define MCOUNTINHIBIT_HPM31   (1<<31)
#define MCOUNTEREN_CY         (1<<0)
#define MCOUNTEREN_TM         (1<<1)
#define MCOUNTEREN_IR         (1<<2)
#define MCOUNTEREN_HPM3       (1<<3)
#define MCOUNTEREN_HPM4       (1<<4)
#define MCOUNTEREN_HPM5       (1<<5)
#define MCOUNTEREN_HPM6       (1<<6)
#define MCOUNTEREN_HPM7       (1<<7)
#define MCOUNTEREN_HPM8       (1<<8)
#define MCOUNTEREN_HPM9       (1<<9)
#define MCOUNTEREN_HPM10      (1<<10)
#define MCOUNTEREN_HPM11      (1<<11)
#define MCOUNTEREN_HPM12      (1<<12)
#define MCOUNTEREN_HPM31      (1ULL<<31)
#define SCOUNTEREN_CY         (1<<0)
#define SCOUNTEREN_TM         (1<<1)
#define SCOUNTEREN_IR         (1<<2)
#define SCOUNTEREN_HPM3       (1<<3)
#define SCOUNTOVF_HPM3        (1<<3)
#define SCOUNTOVF_HPM4        (1<<4)
#define SCOUNTOVF_HPM5        (1<<5)
#define SCOUNTOVF_HPM6        (1<<6)
#define SCOUNTOVF_HPM7        (1<<7)
#define SCOUNTOVF_HPM8        (1<<8)
#define SCOUNTOVF_HPM9        (1<<9)
#define SCOUNTOVF_HPM10       (1<<10)
#define SCOUNTOVF_HPM11       (1<<11)
#define SCOUNTOVF_HPM12       (1<<12)
#define SCOUNTOVF_HPM31       (1ULL<<31)

/**
 * @brief page table entry (PTE) fields
 *
*/
#define PTE_V     0x001 /* Valid */
#define PTE_R     0x002 /* Read */
#define PTE_W     0x004 /* Write */
#define PTE_X     0x008 /* Execute */
#define PTE_U     0x010 /* User */
#define PTE_G     0x020 /* Global */
#define PTE_A     0x040 /* Accessed */
#define PTE_D     0x080 /* Dirty */
#define PTE_SOFT  0x300 /* Reserved for Software */
#define PTE_N     0x8000000000000000 /* Svnapot */

#define PTE_PPN_SHIFT 10
#define PTE_PPN1_SHIFT (PTE_PPN_SHIFT + (PPN_1_OFFSET - PPN_0_OFFSET))
#define PTE_PPN2_SHIFT (PTE_PPN_SHIFT + (PPN_2_OFFSET - PPN_0_OFFSET))
#define PTE_PPN3_SHIFT (PTE_PPN_SHIFT + (PPN_3_OFFSET - PPN_0_OFFSET))

#define PTE_TABLE(PTE) (((PTE) & (PTE_V | PTE_R | PTE_W | PTE_X)) == PTE_V)

/**
 * @brief Short timeout and pause in Decconfig2
 *
*/

#define MAX_STODURATION 0x3FFF
#define STODURATION_OFFSET 16
#define PAUSE_RESET_DELAY_VALUE 0x20
#define PAUSE_MAX_DELAY_VALUE 0xFF

/**
 * @brief PBMT field in Sv39, Sv48, and Sv57 PTEs from Svpbmt
 *
*/
#define PTE_PBMT_SHIFT  61
#define PBMT_PMA        0ULL   /*None*/
#define PBMT_NC         1ULL   /*Non-cacheable, idempotent, weakly-ordered (RVWMO or RVTSO), main memory*/
#define PBMT_IO         2ULL   /*Non-cacheable, non-idempotent, strongly-ordered (I/O ordering), I/O*/

#ifdef __riscv

#if __riscv_xlen == 64
# define MSTATUS_SD MSTATUS64_SD
# define SSTATUS_SD SSTATUS64_SD
# define RISCV_PGLEVEL_BITS 9
# define SATP_MODE SATP64_MODE
#else
# define MSTATUS_SD MSTATUS32_SD
# define SSTATUS_SD SSTATUS32_SD
# define RISCV_PGLEVEL_BITS 10
# define SATP_MODE SATP32_MODE
#endif
#define RISCV_PGSHIFT 12
#define RISCV_PGSIZE (1 << RISCV_PGSHIFT)
#define RISCV_G_ROOT_PGSHIFT 14
#define RISCV_G_ROOT_PGSIZE (1 << RISCV_G_ROOT_PGSHIFT)

#define PTE_SIZE_IN_BYTES 8
#define NUM_PTE (RISCV_PGSIZE/PTE_SIZE_IN_BYTES)
#define NUM_PTE_G_ROOT (RISCV_G_ROOT_PGSIZE/PTE_SIZE_IN_BYTES)

#define PTE_PPN_MSB    53
#define PTE_PPN_MASK   ((((1ULL << PTE_PPN_MSB) - 1) >> RISCV_PGSHIFT) << PTE_PPN_SHIFT)

/**
 * @brief Defines for Loads/Stores/AMO/HLV/HSV instruction opcodes and funct3/funct7 
 * Ld/St Instruction Size
*/
#define DOUBLE_WORD    8
#define WORD           4
#define HALF_WORD      2
#define BYTE           1
// Loads
#define LD_OPCODE      0b0000011
#define LB_FUNCT3      0b000
#define LH_FUNCT3      0b001
#define LW_FUNCT3      0b010
#define LD_FUNCT3      0b011
#define LBU_FUNCT3     0b100
#define LHU_FUNCT3     0b101
#define LWU_FUNCT3     0b110
// Floating point Loads
#define FLD_OPCODE     0b0000111
#define FLW_FUNCT3     0b010
#define FLD_FUNCT3     0b011
// Compressed Loads
#define CLW_FUNCT3     0b010
#define CLD_FUNCT3     0b011
// ZCB Loads
#define CLHU_FUNCT1    0b0
#define CLH_FUNCT1     0b1
#define CLHU_FUNCT3    0b100
#define CLH_FUNCT3     0b100
#define CLHU_FUNCT6    0b1000010
// Compressed Floating Loads
#define CFLD_FUNCT3    0b001
#define CFLW_FUNCT3    0b011
// Compressed Stack Loads
#define CFLDSP_FUNCT3  0b001
#define CLWSP_FUNCT3   0b010
#define CLDSP_FUNCT3   0b011
// Stores
#define ST_OPCODE      0b0100011
#define SB_FUNCT3      0b000
#define SH_FUNCT3      0b001
#define SW_FUNCT3      0b010
#define SD_FUNCT3      0b011
// Compressed Stores
#define CSW_FUNCT3     0b110
#define CSD_FUNCT3     0b111
// ZCB stores
#define CSB_FUNCT3     0b100
#define CSH_FUNCT3     0b100
#define CSB_FUNCT6     0b100010
#define CSH_FUNCT6     0b100011
// Floating Stores
#define FST_OPCODE     0b0100111
#define FSW_FUNCT3     0b010
#define FSD_FUNCT3     0b011
// Compressed Floating Stores
#define CFSD_FUNCT3    0b101
#define CFSW_FUNCT3    0b111
// Compressed Stack Stores
#define CFSDSP_FUNCT3  0b101
#define CSWSP_FUNCT3   0b110
#define CSDSP_FUNCT3   0b111
// AMOs
#define AMOW_FUNCT3    0b010
#define AMOD_FUNCT3    0b011
// Hypervisor Instructions
#define HLV_B_FUNCT7   0b0110000
#define HLV_H_FUNCT7   0b0110010
#define HLV_W_FUNCT7   0b0110100
#define HLV_D_FUNCT7   0b0110110
#define HSV_B_FUNCT7   0b0110001
#define HSV_H_FUNCT7   0b0110011
#define HSV_W_FUNCT7   0b0110101
#define HSV_D_FUNCT7   0b0110111

#ifndef __ASSEMBLER__

#ifdef __GNUC__

#define read_csr(reg) \
  __extension__ \
  ({ \
    uint64_t __tmp; \
    asm volatile ("csrr %0, " #reg : "=r"(__tmp)); \
    __tmp; \
  }) \

#define write_csr(reg, val) \
  __extension__ \
  ({ \
    asm volatile ("csrw " #reg ", %0" :: "rK"(val)); \
  }) \

#define swap_csr(reg, val) \
  __extension__ \
  ({ \
    uint64_t __tmp; \
    asm volatile ("csrrw %0, " #reg ", %1" : "=r"(__tmp) : "rK"(val)); \
    __tmp; \
  }) \

#define set_csr(reg, bit) \
  __extension__ \
  ({ \
    uint64_t __tmp; \
    asm volatile ("csrrs %0, " #reg ", %1" : "=r"(__tmp) : "rK"(bit)); \
    __tmp; \
  }) \

#define clear_csr(reg, bit) \
  __extension__ \
  ({ \
    uint64_t __tmp; \
    asm volatile ("csrrc %0, " #reg ", %1" : "=r"(__tmp) : "rK"(bit)); \
    __tmp; \
  }) \

#define rdtime() read_csr(time)
#define rdcycle() read_csr(cycle)
#define rdinstret() read_csr(instret)

#endif

#endif

#endif

#endif


/**
 * @brief S/VS time compare CSRs (Added by Sstc Extension)
 * 
*/
#define CSR_STIMECMP  0x14d
#define CSR_VSTIMECMP 0x24d

/**
 * @brief envcfg CSRs
 * 
*/
#define CSR_MENVCFG 0x30a
#define CSR_SENVCFG 0x10a
#define CSR_HENVCFG 0x60a

/**
 * @brief AIA CSRs
 * 
*/
#define CSR_MISELECT 0x350
#define CSR_MIREG 0x351
#define CSR_MTOPI 0xFB0

#define CSR_MTOPEI 0x35C
#define CSR_MVIEN 0x308
#define CSR_MVIP 0x309
#define CSR_SISELECT 0x150
#define CSR_SIREG 0x151
#define CSR_STOPI 0xDB0

#define CSR_STOPEI 0x15C
#define CSR_HVIEN 0X608
#define CSR_HVICTL 0X609
#define CSR_HVIPRIO1 0X646
#define CSR_HVIPRIO2 0X647
#define CSR_VSISELECT 0x250
#define CSR_VSIREG 0x251
#define CSR_VSTOPI 0xEB0

#define CSR_VSTOPEI 0x25C

#define HVICTL_VTI     0x40000000
#define HVICTL_IID     0x0fff0000
#define HVICTL_IPRIOM  0x00000100
#define HVICTL_IPRIO   0x000000ff
#define HVICTL_DPR     0x00000200
#define HVICTL_IID_OFFSET 16

#define MTOPI_IID_MASK   0x000000000FFF0000
#define MTOPI_IPRIO      0x00000000000000FF
#define MTOPI_IID_OFFSET 16

#define MTOPI_IID_MASK     0x000000000FFF0000
#define MTOPI_IPRIO        0x00000000000000FF
#define MTOPI_IID_OFFSET   16

#define STOPI_IID_MASK     MTOPI_IID_MASK
#define STOPI_IPRIO        MTOPI_IPRIO
#define STOPI_IID_OFFSET   MTOPI_IID_OFFSET

#define VSTOPI_IID_MASK    STOPI_IID_MASK
#define VSTOPI_IPRIO       STOPI_IPRIO
#define VSTOPI_IID_OFFSET  STOPI_IID_OFFSET

#define MNMI_MNMIP   0x1
#define MNMI_MNMIE   0x2
#define MNMI_MPNMIE  0x4

#define TOPEI_IPRIO_MASK  0x00000000000007FF
#define TOPEI_IID_MASK    0x0000000007FF0000
#define TOPEI_IID_OFFSET  16

#define DCONTROL_INROM 0x0000000000000001

/**
 * @brief State enable CSRs
 * 
*/
#define CSR_MSTATEEN0 0x30c
#define CSR_MSTATEEN1 0x30d
#define CSR_MSTATEEN2 0x30e
#define CSR_MSTATEEN3 0x30f
#define CSR_SSTATEEN0 0x10c
#define CSR_SSTATEEN1 0x10d
#define CSR_SSTATEEN2 0x10e
#define CSR_SSTATEEN3 0x10f
#define CSR_HSTATEEN0 0x60c
#define CSR_HSTATEEN1 0x60d
#define CSR_HSTATEEN2 0x60e
#define CSR_HSTATEEN3 0x60f

#define CSR_FFLAGS 0x1
#define CSR_FRM 0x2
#define CSR_FCSR 0x3
#define CSR_USTATUS 0x0
#define CSR_UIE 0x4
#define CSR_UTVEC 0x5
#define CSR_VSTART 0x8
#define CSR_VXSAT 0x9
#define CSR_VXRM 0xa
#define CSR_VCSR 0xf
#define CSR_USCRATCH 0x40
#define CSR_UEPC 0x41
#define CSR_UCAUSE 0x42
#define CSR_UTVAL 0x43
#define CSR_UIP 0x44
#define CSR_CYCLE 0xc00
#define CSR_TIME 0xc01
#define CSR_INSTRET 0xc02
#define CSR_HPMCOUNTER3 0xc03
#define CSR_HPMCOUNTER4 0xc04
#define CSR_HPMCOUNTER5 0xc05
#define CSR_HPMCOUNTER6 0xc06
#define CSR_HPMCOUNTER7 0xc07
#define CSR_HPMCOUNTER8 0xc08
#define CSR_HPMCOUNTER9 0xc09
#define CSR_HPMCOUNTER10 0xc0a
#define CSR_HPMCOUNTER11 0xc0b
#define CSR_HPMCOUNTER12 0xc0c
#define CSR_HPMCOUNTER13 0xc0d
#define CSR_HPMCOUNTER14 0xc0e
#define CSR_HPMCOUNTER15 0xc0f
#define CSR_HPMCOUNTER16 0xc10
#define CSR_HPMCOUNTER17 0xc11
#define CSR_HPMCOUNTER18 0xc12
#define CSR_HPMCOUNTER19 0xc13
#define CSR_HPMCOUNTER20 0xc14
#define CSR_HPMCOUNTER21 0xc15
#define CSR_HPMCOUNTER22 0xc16
#define CSR_HPMCOUNTER23 0xc17
#define CSR_HPMCOUNTER24 0xc18
#define CSR_HPMCOUNTER25 0xc19
#define CSR_HPMCOUNTER26 0xc1a
#define CSR_HPMCOUNTER27 0xc1b
#define CSR_HPMCOUNTER28 0xc1c
#define CSR_HPMCOUNTER29 0xc1d
#define CSR_HPMCOUNTER30 0xc1e
#define CSR_HPMCOUNTER31 0xc1f
#define CSR_VL 0xc20
#define CSR_VTYPE 0xc21
#define CSR_VLENB 0xc22
#define CSR_SSTATUS 0x100
#define CSR_SEDELEG 0x102
#define CSR_SIDELEG 0x103
#define CSR_SIE 0x104
#define CSR_STVEC 0x105
#define CSR_SCOUNTEREN 0x106
#define CSR_SSCRATCH 0x140
#define CSR_SEPC 0x141
#define CSR_SCAUSE 0x142
#define CSR_STVAL 0x143
#define CSR_SIP 0x144
#define CSR_SATP 0x180
#define CSR_VSSTATUS 0x200
#define CSR_VSIE 0x204
#define CSR_VSTVEC 0x205
#define CSR_VSSCRATCH 0x240
#define CSR_VSEPC 0x241
#define CSR_VSCAUSE 0x242
#define CSR_VSTVAL 0x243
#define CSR_VSIP 0x244
#define CSR_VSATP 0x280
#define CSR_HSTATUS 0x600
#define CSR_HEDELEG 0x602
#define CSR_HIDELEG 0x603
#define CSR_HIE 0x604
#define CSR_HTIMEDELTA 0x605
#define CSR_HCOUNTEREN 0x606
#define CSR_HGEIE 0x607
#define CSR_HCONTEXT 0x6a8
#define CSR_HTVAL 0x643
#define CSR_HIP 0x644
#define CSR_HVIP 0x645
#define CSR_HTINST 0x64a
#define CSR_HGATP 0x680
#define CSR_HGEIP 0xe12
#define CSR_UTVT 0x7
#define CSR_UNXTI 0x45
#define CSR_UINTSTATUS 0x46
#define CSR_USCRATCHCSW 0x48
#define CSR_USCRATCHCSWL 0x49
#define CSR_STVT 0x107
#define CSR_SNXTI 0x145
#define CSR_SINTSTATUS 0x146
#define CSR_SSCRATCHCSW 0x148
#define CSR_SSCRATCHCSWL 0x149
#define CSR_MTVT 0x307
#define CSR_MNXTI 0x345
#define CSR_MINTSTATUS 0x346
#define CSR_MSCRATCHCSW 0x348
#define CSR_MSCRATCHCSWL 0x349
#define CSR_MSTATUS 0x300
#define CSR_MISA 0x301
#define CSR_MEDELEG 0x302
#define CSR_MIDELEG 0x303
#define CSR_MIE 0x304
#define CSR_MTVEC 0x305
#define CSR_MCOUNTEREN 0x306
#define CSR_MCOUNTINHIBIT 0x320
#define CSR_MSCRATCH 0x340
#define CSR_MEPC 0x341
#define CSR_MCAUSE 0x342
#define CSR_MTVAL 0x343
#define CSR_MIP 0x344
#define CSR_MTINST 0x34a
#define CSR_MTVAL2 0x34b
#define CSR_PMPCFG0 0x3a0
#define CSR_PMPCFG1 0x3a1
#define CSR_PMPCFG2 0x3a2
#define CSR_PMPCFG3 0x3a3
#define CSR_PMPADDR0 0x3b0
#define CSR_PMPADDR1 0x3b1
#define CSR_PMPADDR2 0x3b2
#define CSR_PMPADDR3 0x3b3
#define CSR_PMPADDR4 0x3b4
#define CSR_PMPADDR5 0x3b5
#define CSR_PMPADDR6 0x3b6
#define CSR_PMPADDR7 0x3b7
#define CSR_PMPADDR8 0x3b8
#define CSR_PMPADDR9 0x3b9
#define CSR_PMPADDR10 0x3ba
#define CSR_PMPADDR11 0x3bb
#define CSR_PMPADDR12 0x3bc
#define CSR_PMPADDR13 0x3bd
#define CSR_PMPADDR14 0x3be
#define CSR_PMPADDR15 0x3bf
#define CSR_MSECCFG 0x747
#define CSR_TSELECT 0x7a0
#define CSR_TDATA1 0x7a1
#define CSR_TDATA2 0x7a2
#define CSR_TDATA3 0x7a3
#define CSR_TINFO  0x7a4
#define CSR_DCSR 0x7b0
#define CSR_DPC 0x7b1
#define CSR_DSCRATCH0 0x7b2
#define CSR_DSCRATCH1 0x7b3
#define CSR_MCYCLE 0xb00
#define CSR_MINSTRET 0xb02
#define CSR_MHPMCOUNTER3 0xb03
#define CSR_MHPMCOUNTER4 0xb04
#define CSR_MHPMCOUNTER5 0xb05
#define CSR_MHPMCOUNTER6 0xb06
#define CSR_MHPMCOUNTER7 0xb07
#define CSR_MHPMCOUNTER8 0xb08
#define CSR_MHPMCOUNTER9 0xb09
#define CSR_MHPMCOUNTER10 0xb0a
#define CSR_MHPMCOUNTER11 0xb0b
#define CSR_MHPMCOUNTER12 0xb0c
#define CSR_MHPMCOUNTER13 0xb0d
#define CSR_MHPMCOUNTER14 0xb0e
#define CSR_MHPMCOUNTER15 0xb0f
#define CSR_MHPMCOUNTER16 0xb10
#define CSR_MHPMCOUNTER17 0xb11
#define CSR_MHPMCOUNTER18 0xb12
#define CSR_MHPMCOUNTER19 0xb13
#define CSR_MHPMCOUNTER20 0xb14
#define CSR_MHPMCOUNTER21 0xb15
#define CSR_MHPMCOUNTER22 0xb16
#define CSR_MHPMCOUNTER23 0xb17
#define CSR_MHPMCOUNTER24 0xb18
#define CSR_MHPMCOUNTER25 0xb19
#define CSR_MHPMCOUNTER26 0xb1a
#define CSR_MHPMCOUNTER27 0xb1b
#define CSR_MHPMCOUNTER28 0xb1c
#define CSR_MHPMCOUNTER29 0xb1d
#define CSR_MHPMCOUNTER30 0xb1e
#define CSR_MHPMCOUNTER31 0xb1f
#define CSR_MHPMEVENT3 0x323
#define CSR_MHPMEVENT4 0x324
#define CSR_MHPMEVENT5 0x325
#define CSR_MHPMEVENT6 0x326
#define CSR_MHPMEVENT7 0x327
#define CSR_MHPMEVENT8 0x328
#define CSR_MHPMEVENT9 0x329
#define CSR_MHPMEVENT10 0x32a
#define CSR_MHPMEVENT11 0x32b
#define CSR_MHPMEVENT12 0x32c
#define CSR_MHPMEVENT13 0x32d
#define CSR_MHPMEVENT14 0x32e
#define CSR_MHPMEVENT15 0x32f
#define CSR_MHPMEVENT16 0x330
#define CSR_MHPMEVENT17 0x331
#define CSR_MHPMEVENT18 0x332
#define CSR_MHPMEVENT19 0x333
#define CSR_MHPMEVENT20 0x334
#define CSR_MHPMEVENT21 0x335
#define CSR_MHPMEVENT22 0x336
#define CSR_MHPMEVENT23 0x337
#define CSR_MHPMEVENT24 0x338
#define CSR_MHPMEVENT25 0x339
#define CSR_MHPMEVENT26 0x33a
#define CSR_MHPMEVENT27 0x33b
#define CSR_MHPMEVENT28 0x33c
#define CSR_MHPMEVENT29 0x33d
#define CSR_MHPMEVENT30 0x33e
#define CSR_MHPMEVENT31 0x33f
#define CSR_SCOUNTOVF   0xda0
#define CSR_MVENDORID 0xf11
#define CSR_MARCHID 0xf12
#define CSR_MIMPID 0xf13
#define CSR_MHARTID 0xf14
#define CSR_MCONFIGPTR 0xf15
#define CSR_HTIMEDELTAH 0x615
#define CSR_CYCLEH 0xc80
#define CSR_TIMEH 0xc81
#define CSR_INSTRETH 0xc82
#define CSR_HPMCOUNTER3H 0xc83
#define CSR_HPMCOUNTER4H 0xc84
#define CSR_HPMCOUNTER5H 0xc85
#define CSR_HPMCOUNTER6H 0xc86
#define CSR_HPMCOUNTER7H 0xc87
#define CSR_HPMCOUNTER8H 0xc88
#define CSR_HPMCOUNTER9H 0xc89
#define CSR_HPMCOUNTER10H 0xc8a
#define CSR_HPMCOUNTER11H 0xc8b
#define CSR_HPMCOUNTER12H 0xc8c
#define CSR_HPMCOUNTER13H 0xc8d
#define CSR_HPMCOUNTER14H 0xc8e
#define CSR_HPMCOUNTER15H 0xc8f
#define CSR_HPMCOUNTER16H 0xc90
#define CSR_HPMCOUNTER17H 0xc91
#define CSR_HPMCOUNTER18H 0xc92
#define CSR_HPMCOUNTER19H 0xc93
#define CSR_HPMCOUNTER20H 0xc94
#define CSR_HPMCOUNTER21H 0xc95
#define CSR_HPMCOUNTER22H 0xc96
#define CSR_HPMCOUNTER23H 0xc97
#define CSR_HPMCOUNTER24H 0xc98
#define CSR_HPMCOUNTER25H 0xc99
#define CSR_HPMCOUNTER26H 0xc9a
#define CSR_HPMCOUNTER27H 0xc9b
#define CSR_HPMCOUNTER28H 0xc9c
#define CSR_HPMCOUNTER29H 0xc9d
#define CSR_HPMCOUNTER30H 0xc9e
#define CSR_HPMCOUNTER31H 0xc9f
#define CSR_MSTATUSH 0x310
#define CSR_MCYCLEH 0xb80
#define CSR_MINSTRETH 0xb82
#define CSR_MHPMCOUNTER3H 0xb83
#define CSR_MHPMCOUNTER4H 0xb84
#define CSR_MHPMCOUNTER5H 0xb85
#define CSR_MHPMCOUNTER6H 0xb86
#define CSR_MHPMCOUNTER7H 0xb87
#define CSR_MHPMCOUNTER8H 0xb88
#define CSR_MHPMCOUNTER9H 0xb89
#define CSR_MHPMCOUNTER10H 0xb8a
#define CSR_MHPMCOUNTER11H 0xb8b
#define CSR_MHPMCOUNTER12H 0xb8c
#define CSR_MHPMCOUNTER13H 0xb8d
#define CSR_MHPMCOUNTER14H 0xb8e
#define CSR_MHPMCOUNTER15H 0xb8f
#define CSR_MHPMCOUNTER16H 0xb90
#define CSR_MHPMCOUNTER17H 0xb91
#define CSR_MHPMCOUNTER18H 0xb92
#define CSR_MHPMCOUNTER19H 0xb93
#define CSR_MHPMCOUNTER20H 0xb94
#define CSR_MHPMCOUNTER21H 0xb95
#define CSR_MHPMCOUNTER22H 0xb96
#define CSR_MHPMCOUNTER23H 0xb97
#define CSR_MHPMCOUNTER24H 0xb98
#define CSR_MHPMCOUNTER25H 0xb99
#define CSR_MHPMCOUNTER26H 0xb9a
#define CSR_MHPMCOUNTER27H 0xb9b
#define CSR_MHPMCOUNTER28H 0xb9c
#define CSR_MHPMCOUNTER29H 0xb9d
#define CSR_MHPMCOUNTER30H 0xb9e
#define CSR_MHPMCOUNTER31H 0xb9f

/**
 * @brief Custom CSRs
 *
*/
#define CSR_MNMI 0xbc1
#define CSR_MSALT 0xbc0

#define read_csr_define(reg) \
  __extension__ \
  ({ \
    uint64_t __tmp; \
    asm volatile ("csrr %0, " xstr(reg) : "=r"(__tmp)); \
    __tmp; \
  }) \

#define write_csr_define(reg, val) \
  __extension__ \
  ({ \
    asm volatile ("csrw " xstr(reg) ", %0" :: "rK"(val)); \
  }) \

#define set_csr_define(reg, bit) \
  __extension__ \
  ({ \
    uint64_t __tmp; \
    asm volatile ("csrrs %0, " xstr(reg) ", %1" : "=r"(__tmp) : "rK"(bit)); \
    __tmp; \
  }) \

#define clear_csr_define(reg, bit) \
  __extension__ \
  ({ \
    uint64_t __tmp; \
    asm volatile ("csrrc %0, " xstr(reg) ", %1" : "=r"(__tmp) : "rK"(bit)); \
    __tmp; \
  }) \

#define CAUSE_MISALIGNED_FETCH 0x0
#define CAUSE_FETCH_ACCESS 0x1
#define CAUSE_ILLEGAL_INSTRUCTION 0x2
#define CAUSE_BREAKPOINT 0x3
#define CAUSE_INSTR_ADDR_BREAKPOINT 0x3
#define CAUSE_LOAD_STORE_AMO_BREAKPOINT 0x3
#define CAUSE_MISALIGNED_LOAD 0x4
#define CAUSE_LOAD_ACCESS 0x5
#define CAUSE_MISALIGNED_STORE 0x6
#define CAUSE_STORE_ACCESS 0x7
#define CAUSE_USER_ECALL 0x8
#define CAUSE_VU_ECALL 0x8
#define CAUSE_SUPERVISOR_ECALL 0x9
#define CAUSE_HS_ECALL 0x9
#define CAUSE_VS_ECALL 0xa
#define CAUSE_HYPERVISOR_ECALL 0xa
#define CAUSE_MACHINE_ECALL 0xb
#define CAUSE_FETCH_PAGE_FAULT 0xc
#define CAUSE_LOAD_PAGE_FAULT 0xd
#define CAUSE_STORE_PAGE_FAULT 0xf
#define CAUSE_FETCH_GUEST_PAGE_FAULT 0x14
#define CAUSE_LOAD_GUEST_PAGE_FAULT 0x15
#define CAUSE_VIRTUAL_INSTR_TRAP 0x16
#define CAUSE_STORE_GUEST_PAGE_FAULT 0x17
#define CAUSE_INSTRUCTION_CORRUPTION 0x18
#define CAUSE_LOAD_DATA_CORRUPTION 0x19
#define CAUSE_STORE_DATA_CORRUPTION 0x1B
#define CAUSE_AMO_DATA_CORRUPTION 0x1B
#define CAUSE_DATA_CORRUPTION 0x20

#define SUPPORTED_EXCEPTIONS_VT1  (\
  (1 << CAUSE_FETCH_ACCESS)           | (1 << CAUSE_ILLEGAL_INSTRUCTION)  | (1 << CAUSE_BREAKPOINT)            | \
  (1 << CAUSE_LOAD_ACCESS)            | (1 << CAUSE_STORE_ACCESS)         | (1 << CAUSE_USER_ECALL)            | \
  (1 << CAUSE_VU_ECALL)               | (1 << CAUSE_SUPERVISOR_ECALL)     | (1 << CAUSE_MACHINE_ECALL)         | \
  (1 << CAUSE_FETCH_PAGE_FAULT)       | (1 << CAUSE_LOAD_PAGE_FAULT)      | (1 << CAUSE_STORE_PAGE_FAULT)      | \
  (1 << CAUSE_INSTRUCTION_CORRUPTION) | (1 << CAUSE_LOAD_DATA_CORRUPTION) | (1 << CAUSE_STORE_DATA_CORRUPTION) | \
  (1 << CAUSE_AMO_DATA_CORRUPTION)    | (1 << CAUSE_HS_ECALL)             | (1 << CAUSE_VIRTUAL_INSTR_TRAP)    | \
  (1 << CAUSE_FETCH_GUEST_PAGE_FAULT) | (1 << CAUSE_VS_ECALL)             | (1 << CAUSE_LOAD_GUEST_PAGE_FAULT) | \
  (1 << CAUSE_STORE_GUEST_PAGE_FAULT))

#define SUPPORTED_EXCEPTIONS  (\
  (1ULL << CAUSE_FETCH_ACCESS)           | (1ULL << CAUSE_ILLEGAL_INSTRUCTION)  | (1ULL << CAUSE_BREAKPOINT)            | \
  (1ULL << CAUSE_LOAD_ACCESS)            | (1ULL << CAUSE_STORE_ACCESS)         | (1ULL << CAUSE_USER_ECALL)            | \
  (1ULL << CAUSE_VU_ECALL)               | (1ULL << CAUSE_SUPERVISOR_ECALL)     | (1ULL << CAUSE_MACHINE_ECALL)         | \
  (1ULL << CAUSE_FETCH_PAGE_FAULT)       | (1ULL << CAUSE_LOAD_PAGE_FAULT)      | (1ULL << CAUSE_STORE_PAGE_FAULT)      | \
  (1ULL << CAUSE_DATA_CORRUPTION)        | (1ULL << CAUSE_HS_ECALL)             | (1ULL << CAUSE_VIRTUAL_INSTR_TRAP)    | \
  (1ULL << CAUSE_FETCH_GUEST_PAGE_FAULT) | (1ULL << CAUSE_VS_ECALL)             | (1ULL << CAUSE_LOAD_GUEST_PAGE_FAULT) | \
  (1ULL << CAUSE_STORE_GUEST_PAGE_FAULT))

#define SUPPORTED_EXCEPTIONS_HYPERVISOR_DISABLED  (\
  (1 << CAUSE_FETCH_ACCESS)           | (1 << CAUSE_ILLEGAL_INSTRUCTION)  | (1 << CAUSE_BREAKPOINT)            | \
  (1 << CAUSE_LOAD_ACCESS)            | (1 << CAUSE_STORE_ACCESS)         | (1 << CAUSE_USER_ECALL)            | \
  (1 << CAUSE_VU_ECALL)               | (1 << CAUSE_SUPERVISOR_ECALL)     | (1 << CAUSE_MACHINE_ECALL)         | \
  (1 << CAUSE_FETCH_PAGE_FAULT)       | (1 << CAUSE_LOAD_PAGE_FAULT)      | (1 << CAUSE_STORE_PAGE_FAULT)      | \
  (1 << CAUSE_INSTRUCTION_CORRUPTION) | (1 << CAUSE_LOAD_DATA_CORRUPTION) | (1 << CAUSE_STORE_DATA_CORRUPTION) | \
  (1 << CAUSE_AMO_DATA_CORRUPTION))

#define HYPERVISOR_SUPPORTED_EXCEPTIONS (\
  (1 << CAUSE_HS_ECALL) | (1 << CAUSE_VIRTUAL_INSTR_TRAP)    | (1 << CAUSE_FETCH_GUEST_PAGE_FAULT) | \
  (1 << CAUSE_VS_ECALL) | (1 << CAUSE_LOAD_GUEST_PAGE_FAULT) | (1 << CAUSE_STORE_GUEST_PAGE_FAULT))

#endif
/* ENCODING_H */

