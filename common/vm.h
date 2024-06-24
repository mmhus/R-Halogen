// Copyright 2024 10xEngineers

/**
 * @file vm.h
 * @brief This file contains vm related macros and function prototypes. 
 * 
 * @copyright Copyright 2023 Ventana Micro Systems
 * 
 */
#ifndef RISCV_SINGLE_CORE_VM_H
#define RISCV_SINGLE_CORE_VM_H

#include "c_test_macros.h"
#include "stdbool.h"
#include "platform.h"

#ifndef NO_OF_PAGES
  #define NO_OF_PAGES                25
#endif

#define MAX_PG_LEVELS                6
#define SMODE_SP                     (0x400000000)  // random value chosen after the .text section but below the MMODE_SP
#define TOP_OF_ISA_PHY_ADDR_SPACE    ((1ull<<56) - 1)
#define NON_CANONICAL_TVAL_MASK      (0x1ull << PHY_ADDR_SPACE_BITS)
#define NON_CANONICAL_ADDR           (~(NON_CANONICAL_TVAL_MASK - 1))


#define LEVEL_0     0
#define LEVEL_1     1
#define LEVEL_2     2
#define LEVEL_3     3
#define LEVEL_4     4
#define LEVEL_5     5

typedef struct {
    unsigned mode;
    unsigned levels;
    unsigned ppn_width_bits[MAX_PG_LEVELS-1];
    unsigned ppn_offset_bits[MAX_PG_LEVELS-1];
    unsigned entry_width_bytes;
    unsigned vpn_width_bits[MAX_PG_LEVELS-1];
    unsigned vaddr_bits;
    uint64_t vaddr_invalid_hi;
    uint64_t vaddr_invalid_lo;
} virtual_memory_system_t;

extern virtual_memory_system_t sv32;
extern virtual_memory_system_t sv39;
extern virtual_memory_system_t sv48;
extern virtual_memory_system_t sv39x4;
extern virtual_memory_system_t sv48x4;

typedef uint64_t pg_table_permissions[MAX_PG_LEVELS];
extern  pg_table_permissions permissions;

extern  virtual_memory_system_t *vms;
extern  void* master_table;
extern  uint64_t implicit_phy_addrs[MAX_PG_LEVELS-1];

void* get_page(void);
void* get_16kb_page(void);
uint64_t get_entry(char *table, unsigned index);
void  set_pte_permissions(uint64_t pte_permissions, uint64_t level);
void  add_entry(char *table, unsigned level, uint64_t virtual, uint64_t physical);
uint64_t handle_page_fault(uint64_t vaddr, int exception_cause, uint64_t offset);
void  set_entry(char *table, unsigned index, uint64_t value);
void  setup_page_table(char *table, unsigned level, uint64_t physical);
unsigned vpn(uint64_t virtual, unsigned level);
uint64_t get_page_buffer_base_address(void);
void set_page_buffer_base_address(uint64_t addr);
uint64_t get_page_buffer_cur_address(void);
void set_page_buffer_cur_address(uint64_t addr);
#endif

