/*
-- File : ilx_pdc_interface.c
--
-- Contents : Specialisation of Checkers_pdc_interface for ILX
--
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

#include "ilx_define.h"
#include "ilx_pdc_interface.h"
#include "checkers_api_l_structs.h"

bool ilx_pdc_interface::expand_into_root_locations(const Checkers_storinfo* s)
{
     //return true;
    return s->storage_name != "SR";
}
void ilx_pdc_interface::load_reg_cache()
{
    Checkers_pdc_interface::load_reg_cache();
    DataType sr_val = reg_cache["sr"];

    reg_cache["en"] = (sr_val>>0) & 0xf;
    reg_cache["tk"] = (sr_val>>4) &   1;
    reg_cache["mc"] = (sr_val>>5) &   1;
}
int ilx_pdc_interface::put_register(string name, const DataType& val)
{
    if (Checkers_pdc_interface::put_register(name,val) == ok)
        return ok;
    to_lower(name);
    if (name == "en" || name == "tk" || name == "mc") {
        // writing to SR record components
        DataType sr_val;
        cmd.get_register("sr",sr_val);
        if      (name == "en") sr_val = (sr_val & ~(0xf << 0)) | (val & 0xf) << 0;
        else if (name == "tk") sr_val = (sr_val & ~(  1 << 4)) | (val &   1) << 4;
        else if (name == "mc") sr_val = (sr_val & ~(  1 << 5)) | (val &   1) << 5;
        return cmd.put_register("sr",sr_val);
    }
    else return failed;
}

pdc_commands::instr_type ilx_pdc_interface::get_instruction_at(AddressType pc)
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

void ilx_pdc_interface::put_instruction_at(AddressType pc,
                                           pdc_commands::instr_type instr)
{
    VBitWrapper tmp(32,false); tmp = instr;
    // PM is BIG endian
    put_memory_at(cmd.pmem_name,pc+3,tmp.extract(7,0));
    put_memory_at(cmd.pmem_name,pc+2,tmp.extract(15,8));
    put_memory_at(cmd.pmem_name,pc+1,tmp.extract(23,16));
    put_memory_at(cmd.pmem_name,pc+0,tmp.extract(31,24));
}

AddressType ilx_pdc_interface::next_instruction(AddressType pc) { return pc+4; }
AddressType ilx_pdc_interface::prev_instruction(AddressType pc) { return pc-4; }
