/*
-- File : tlx_pdc_interface.c
--
-- Contents : Specialisation of Checkers_pdc_interface for TLX
--
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

#include "tlx_define.h"
#include "tlx_pdc_interface.h"

bool tlx_pdc_interface::expand_into_root_locations(const Checkers_storinfo* s)
{
    return true;  // always expand
}

pdc_commands::instr_type tlx_pdc_interface::get_instruction_at(AddressType pc)
{
    VBitWrapper instr(32,false,0);
    get_memory_at(cmd.pmem_name,pc,instr);
    return instr;
}

void tlx_pdc_interface::put_instruction_at(AddressType pc,
                                           pdc_commands::instr_type instr)
{
    put_memory_at(cmd.pmem_name,pc,instr);
}

AddressType tlx_pdc_interface::next_instruction(AddressType pc) { return pc+1; }
AddressType tlx_pdc_interface::prev_instruction(AddressType pc) { return pc-1; }
