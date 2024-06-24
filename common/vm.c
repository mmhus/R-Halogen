// Copyright 2024 10xEngineers

/* Orig Author: Yunsup Lee & Andrew Waterman
   Modified by: M. Moiz Hussain, Fatima Khursid

Copyright (c) 2010-2017, The Regents of the University of California
(Regents).  All Rights Reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
3. Neither the name of the Regents nor the
   names of its contributors may be used to endorse or promote products
   derived from this software without specific prior written permission.

IN NO EVENT SHALL REGENTS BE LIABLE TO ANY PARTY FOR DIRECT, INDIRECT,
SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING LOST PROFITS, ARISING
OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF REGENTS HAS
BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

REGENTS SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE. THE SOFTWARE AND ACCOMPANYING DOCUMENTATION, IF ANY, PROVIDED
HEREUNDER IS PROVIDED "AS IS". REGENTS HAS NO OBLIGATION TO PROVIDE
MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
*/

#include <stdint.h>

#include "libtest.h"
#include "encoding.h"
#include "vm.h"

#define TOP_OF_POSITIVE_CANON_ADDR_RANGE_SV32 (((1ull << 31) - 1ull))  // 32th bit is the sign extension, positive addresses only go upto the 38th bit
#define TOP_OF_NEGATIVE_CANON_ADDR_RANGE_SV32 (0xFFFFFFFF80000000ll)   // less than 0, 32th bit is the sign extension,
                                                                       // positive addresses only go upto the 38th bit

#define TOP_OF_POSITIVE_CANON_ADDR_RANGE_SV39 (((1ull << 38) - 1ull))  // 39th bit is the sign extension, positive addresses only go upto the 38th bit
#define TOP_OF_NEGATIVE_CANON_ADDR_RANGE_SV39 (0xFFFFFFC000000000ll)   // less than 0, 39th bit is the sign extension,
                                                                       // positive addresses only go upto the 38th bit

#define TOP_OF_POSITIVE_CANON_ADDR_RANGE_SV48 (((1ull << 47) - 1ull))  // 48th bit is the sign extension, positive addresses only go upto the 47th bit
#define TOP_OF_NEGATIVE_CANON_ADDR_RANGE_SV48 (0xFFFF800000000000ll)   // less than 0 to 48th bit is the sign extension,
                                                                       // positive addresses only go upto the 47th bit

#define TOP_OF_GUEST_PHY_ADDR_RANGE_SV39x4 (((1ull << 41) - 1ull))     // positive addresses go upto the 41st bit
#define TOP_OF_GUEST_PHY_ADDR_RANGE_SV48x4 (((1ull << 50) - 1ull))     // positive addresses go upto the 50th bit

virtual_memory_system_t *vms = 0;  // Aligned here so that the rest of the variables come in the same page
pg_table_permissions permissions;
void *master_table = 0;
int no_more_pages = 0;
uint64_t implicit_phy_addrs[MAX_PG_LEVELS-1] = {0, 0, 0, 0, 0};

static  char page_buffer[RISCV_PGSIZE * NO_OF_PAGES] __attribute__((aligned(RISCV_PGSIZE*4)));
static  char *page_buffer_base = page_buffer;
static  char *page_buffer_next = page_buffer;

virtual_memory_system_t sv32 = {
  .mode = SATP_MODE_SV32,
  .levels = 2,
  .ppn_width_bits = {12, 10, 10},
  .ppn_offset_bits = {0, 12, 22},
  .entry_width_bytes = 4,
  .vpn_width_bits = {10, 10},
  .vaddr_bits = 32,
  .vaddr_invalid_hi = TOP_OF_NEGATIVE_CANON_ADDR_RANGE_SV32 - 1ull,
  .vaddr_invalid_lo = TOP_OF_POSITIVE_CANON_ADDR_RANGE_SV32
};

virtual_memory_system_t sv39 = {
  .mode = SATP_MODE_SV39,
  .levels = 3,
  .ppn_width_bits = {12, 9, 9, 26},
  .ppn_offset_bits = {0, 12, 21, 30},
  .entry_width_bytes = 8,
  .vpn_width_bits = {9, 9, 9},
  .vaddr_bits = 39,
  .vaddr_invalid_hi = TOP_OF_NEGATIVE_CANON_ADDR_RANGE_SV39 - 1ull,
  .vaddr_invalid_lo = TOP_OF_POSITIVE_CANON_ADDR_RANGE_SV39
};

virtual_memory_system_t sv39x4 = {
  .mode = SATP_MODE_SV39,
  .levels = 3,
  .ppn_width_bits = {12, 9, 9, 26},
  .ppn_offset_bits = {0, 12, 21, 30},
  .entry_width_bytes = 8,
  .vpn_width_bits = {9, 9, 11},
  .vaddr_bits = 41,
  .vaddr_invalid_hi = 0xFFFFFFFFFFFFFFFF,
  .vaddr_invalid_lo = TOP_OF_GUEST_PHY_ADDR_RANGE_SV39x4
};

virtual_memory_system_t sv48 = {
  .mode = SATP_MODE_SV48,
  .levels = 4,
  .ppn_width_bits = {12, 9, 9, 9, 26},
  .ppn_offset_bits = {0, 12, 21, 30, 39},
  .entry_width_bytes = 8,
  .vpn_width_bits = {9, 9, 9, 9},
  .vaddr_bits = 48,
  .vaddr_invalid_hi = TOP_OF_NEGATIVE_CANON_ADDR_RANGE_SV48 - 1ull,
  .vaddr_invalid_lo = TOP_OF_POSITIVE_CANON_ADDR_RANGE_SV48
};

virtual_memory_system_t sv48x4 = {
  .mode = SATP_MODE_SV48,
  .levels = 4,
  .ppn_width_bits = {12, 9, 9, 9, 11},
  .ppn_offset_bits = {0, 12, 21, 30, 39},
  .entry_width_bytes = 8,
  .vpn_width_bits = {9, 9, 9, 11},
  .vaddr_bits = 50,
  .vaddr_invalid_hi = 0xFFFFFFFFFFFFFFFF,
  .vaddr_invalid_lo = TOP_OF_GUEST_PHY_ADDR_RANGE_SV48x4
};

/* Private function prototypes */
void   tb_assert(int condition);

/* Functions */
uint64_t handle_page_fault(uint64_t vaddr, int exception_cause, uint64_t offset) {
  uint64_t *physical = 0;
  switch (exception_cause) {
    case CAUSE_FETCH_PAGE_FAULT:
    case CAUSE_FETCH_GUEST_PAGE_FAULT:
    {
      physical = (uint64_t*)(vaddr + offset);
      static uint64_t page_count = 0;
      page_count++;
      if (page_count > NO_OF_PAGES) tb_fail();
      break;
    }
    case CAUSE_LOAD_PAGE_FAULT :
    case CAUSE_STORE_PAGE_FAULT:
    case CAUSE_LOAD_GUEST_PAGE_FAULT:
    case CAUSE_STORE_GUEST_PAGE_FAULT:
    {
      physical = (uint64_t*)get_page();
      break;
    }
    default:
      tb_fail();
  }
  add_entry((char*)master_table, 0, (uint64_t) vaddr, (uint64_t)physical);
  if (vms == &sv39x4 || vms == &sv48x4) {
    FLUSH_PAGE_GVMA((uint64_t)vaddr);
  } else {
    reg_mstatus.reg = read_csr(mstatus);
    if (reg_mstatus.MPV)
      FLUSH_PAGE_VVMA((uint64_t)vaddr);
    else
      FLUSH_PAGE((uint64_t)vaddr);
  }
  return (uint64_t)physical;
}

uint64_t get_page_buffer_base_address() {
  return (uint64_t)page_buffer_base;
}

void set_page_buffer_base_address(uint64_t addr) {
  page_buffer_base = (char*)addr;
  page_buffer_next = (char*)addr;
}

uint64_t get_page_buffer_cur_address() {
  return (uint64_t)page_buffer_next;
}

void set_page_buffer_cur_address(uint64_t addr) {
  page_buffer_next = (char*)addr;
}

// Return a 4Kb, aligned, page.
void *get_page() {
  page_buffer_next = (char *) (((uint64_t) page_buffer_next + 4095) & ~0xfff);
#ifndef SKIP_NO_MORE_PAGES_CHK
  if (page_buffer_next + 4096 >= page_buffer_base + (4096 * NO_OF_PAGES)) {
    no_more_pages = 1;
    tb_fail();
  }
#endif
  void *result = page_buffer_next;
  page_buffer_next += 4096;
  return result;
}

// Return a 16Kb, aligned, page, if first page
void *get_16kb_page() {
  page_buffer_next = (char *) (((uint64_t) page_buffer_next + (4096*4)-1) & ~0x3fff);
#ifndef SKIP_NO_MORE_PAGES_CHK
  if (page_buffer_next + (4096*4) >= page_buffer_base + (4096 * NO_OF_PAGES)) {
    no_more_pages = 1;
    tb_fail();
  }
#endif
  void *result = page_buffer_next;
  page_buffer_next += (4096*4);
  return result;
}

uint64_t get_entry(char *table, unsigned index) {
  if (vms->entry_width_bytes == 4)
    return ((uint32_t *) table)[index];
  else if (vms->entry_width_bytes == 8)
    return ((uint64_t *) table)[index];
  else
    tb_assert(0);
  return 0xFFFFFFFFFFFFFFFE;
}

void set_entry(char *table, unsigned index, uint64_t value) {
  if (vms->entry_width_bytes == 4) {
  #ifndef PTE_ENTRY_OVERWRITE
    if (((uint32_t *) table)[index] != 0) tb_fail();  // entry overwrite
  #endif
    ((uint32_t *) table)[index] = value;
  } else if (vms->entry_width_bytes == 8) {
  #ifndef PTE_ENTRY_OVERWRITE
    if (((uint64_t *) table)[index] != 0) tb_fail();  // entry overwrite
  #endif
    ((uint64_t *) table)[index] = value;
  } else {
    tb_assert(0);
  }
}

// Set up 1-to-1 for this entire table.
void setup_page_table(char *table, unsigned level, uint64_t physical) {
  (void) physical;  // unused don't want to change tests
  #ifndef SKIP_PAGE_ZEROING
    for (unsigned i = 0; i < (unsigned)(1 << vms->vpn_width_bits[level]); i++) {
      set_entry(table, i, (uint64_t)0);
    }
  #endif
}

// Return contents of vpn field for the given virtual address and level.
unsigned vpn(uint64_t virtual, unsigned level) {
  if ((virtual > vms->vaddr_invalid_lo) && (virtual <= vms->vaddr_invalid_hi))
    return 2048;  // Invalid value, 2048 to allow for 16k pages
  uint64_t shift_bits = 12 + (vms->vpn_width_bits[0] * level);
  virtual >>= shift_bits;
  return virtual & ((1 << vms->vpn_width_bits[level])-1);
}

// Add an entry to the given table, at the given level (0 for 4Kb page).
void add_entry(char *table, unsigned level, uint64_t virtual, uint64_t physical) {
  for (int i=0; i < MAX_PG_LEVELS-1; i++)
    implicit_phy_addrs[i] = 0;

  unsigned current_level = vms->levels - 1;
  while (1) {
    unsigned index = vpn(virtual, current_level);
    if (index >= 2048)  // Don't add entry, invalid virtual addr with invalid index, 2048 to allow for 16k pages
      return;
    if (current_level <= level) {
      // Add the new entry.
      uint64_t new_pte = permissions[0] | ((physical >> RISCV_PGSHIFT) << PTE_PPN_SHIFT);
      set_entry(table, index, new_pte);
      return;
    }
    uint64_t pte = get_entry(table, index);
    bool is_valid = (pte & PTE_V);
    bool is_leaf = (pte & PTE_R) && (pte & PTE_X);
    if (!is_valid || is_leaf) {
      // Create a new page
      void* new_page = get_page();
      implicit_phy_addrs[current_level] = (uint64_t)new_page;
      setup_page_table(new_page, current_level - 1, virtual);

      // Have to add physical address in pte, removing lower physical bits of superpages
      uint64_t temp_addr = ((uint64_t)new_page >> RISCV_PGSHIFT) << PTE_PPN_SHIFT;
      uint64_t new_pte = permissions[current_level] | temp_addr;
      set_entry(table, index, new_pte);
      table = new_page;
    } else {
      uint64_t mask = ~((1 << PTE_PPN_SHIFT) - 1);
      table = (char *) ((pte << 2) & mask);
    }
    current_level--;
  }
}

// Set pte permissions for level
void  set_pte_permissions(uint64_t pte_permissions, uint64_t level) {
  if (level > (vms->levels-1)) tb_fail();
  permissions[level] = pte_permissions;
}

