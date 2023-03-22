/*
-- File : flx_pdc_interface.c
--
-- Contents : Specialisation of Checkers_pdc_interface for FLX
--
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

#include "flx_define.h"
#include "flx_pdc_interface.h"

bool flx_pdc_interface::expand_into_root_locations(const Checkers_storinfo* s)
{
    return true;  // always expand
}

pdc_commands::instr_type flx_pdc_interface::get_instruction_at(AddressType pc)
{
    VBitWrapper instr(32,false,0);
    DataType instr0, instr1, instr2, instr3;
    // PM is BIG endian
    get_memory_at(cmd.pmem_name,pc+0,instr0);
    get_memory_at(cmd.pmem_name,pc+1,instr1);
    get_memory_at(cmd.pmem_name,pc+2,instr2);
    get_memory_at(cmd.pmem_name,pc+3,instr3);
    instr.deposit(instr3 & 0xFF, 7, 0);
    instr.deposit(instr2 & 0xFF, 15, 8);
    instr.deposit(instr1 & 0xFF, 23, 16);
    instr.deposit(instr0 & 0xFF, 31, 24);
    return instr;
}

void flx_pdc_interface::put_instruction_at(AddressType pc,
                                           pdc_commands::instr_type instr)
{
    VBitWrapper tmp(32,false); tmp = instr;
    // PM is BIG endian
    put_memory_at(cmd.pmem_name,pc+3,tmp.extract(7,0));
    put_memory_at(cmd.pmem_name,pc+2,tmp.extract(15,8));
    put_memory_at(cmd.pmem_name,pc+1,tmp.extract(23,16));
    put_memory_at(cmd.pmem_name,pc+0,tmp.extract(31,24));
}

AddressType flx_pdc_interface::next_instruction(AddressType pc) { return pc+4; }
AddressType flx_pdc_interface::prev_instruction(AddressType pc) { return pc-4; }
