/*
-- File : trv32p5_pdc_interface.c
--
-- Contents : Specialisation of Checkers_pdc_interface for TRV32P5
--
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

#include "trv32p5_pdc_interface.h"
#include "checkers_api_l_structs.h"
#include "trv32p5_define.h"

#include <iostream>

#ifdef TRACE_PDC_API
#define trv32p5_pdc_interface trv32p5_pdc_interface_
#endif


trv32p5_pdc_interface::trv32p5_pdc_interface(int coreid, std::string server,
                                             int port)
  : Checkers_pdc_interface(coreid, server, port)
{
}

VBitWrapper trv32p5_pdc_interface::get_instruction_at(AddressType pc)
{
  unsigned ilen = 32;
  DataType byte;
  VBitWrapper instr(ilen,false);

  for (int i = 0; i < ilen/8; ++i) {
    get_memory_at(cmd.pmem_name, pc + i, byte);
    instr.deposit(byte.extract(7,0), i*8+7, i*8);
  }

  return instr;
}

void trv32p5_pdc_interface::put_instruction_at(AddressType pc, VBitWrapper instr) {
  int nb = instr.getBitSize() / 8;
  for (int i = 0; i < nb; ++i) {
    put_memory_at(cmd.pmem_name, pc + i, instr.extract(8*i+7,8*i).to<VBit<8,false>>());
  }
}

// NOTE prev/next_instruction assume that there is a software break @ PM[pc]
// they are never called for any other purpose.

AddressType trv32p5_pdc_interface::next_instruction(AddressType pc) {
  return pc + (get_instruction_at(pc).getBitSize() / 8);
}

AddressType trv32p5_pdc_interface::prev_instruction(AddressType pc) {
  // stopped past a swbreak instruction - but don't know which swbrk
  // try common swbreak instruction lengths
  if (sw_break_instrs.count(pc - 2) > 0) return pc - 2;
  if (sw_break_instrs.count(pc - 4) > 0) return pc - 4;
  if (sw_break_instrs.count(pc - 8) > 0) return pc - 8;
  std::cerr << "ERROR: could not determine prev instr at " << pc << "\n";
  return 0;
}

void trv32p5_pdc_interface::populate_common_scl_regs() {
//  // load all X[] fields
//  for (int idx = 0; idx < 32; ++idx) {
//    common_scl_regs.push_back(std::string("x") + std::to_string(idx));
//  }
}
