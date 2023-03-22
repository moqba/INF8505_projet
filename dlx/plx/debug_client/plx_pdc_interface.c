/*
-- File : plx_pdc_interface.c
--
-- Contents : Specialisation of Checkers_pdc_interface for PLX
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/



#include "plx_pdc_interface.h"
#include "checkers_api_l_structs.h"

bool plx_pdc_interface::expand_into_root_locations(const Checkers_storinfo* s)
{
    return s->storage_name != "SR";
}

void plx_pdc_interface::load_reg_cache()
{
    Checkers_pdc_interface::load_reg_cache();
    int sr_val = (int)reg_cache["sr"];

    // reading from SR record components
    reg_cache["en"]  = (sr_val>> 0) & 0xffff;
    reg_cache["tk"]  = (sr_val>>16) &      1;
    reg_cache["mc"]  = (sr_val>>17) &      1;
    reg_cache["ack"] = (sr_val>>18) &      1;
    reg_cache["ap"]  = (sr_val>>19) &      7;
}

int plx_pdc_interface::get_register(string nm, long long& val)
{
#if 1
    // don't drag whole scalar register cache
    // to speed up step=+1 testing
    to_lower(nm);
    if (nm == "en") {
        long long sr_val;
        if (cmd.get_register("sr",sr_val) == ok) {
            val = sr_val & 0xffff;
            return ok;
        }
        else
            return failed;
    }
#endif
    return Checkers_pdc_interface::get_register(nm,val);
}

int plx_pdc_interface::put_register(string nm, long long val)
{
    if (Checkers_pdc_interface::put_register(nm,val) == ok)
        return ok;
    to_lower(nm);
    if (nm == "en" || nm == "tk" || nm == "mc" || nm == "ack" || nm == "ap") {
        // writing to SR record components
        long long sr_val;
        cmd.get_register("sr",sr_val);
        if      (nm == "en")  sr_val = (sr_val & ~(0xffff <<  0)) | (val & 0xffff) <<  0;
        else if (nm == "tk")  sr_val = (sr_val & ~(     1 << 16)) | (val &      1) << 16;
        else if (nm == "mc")  sr_val = (sr_val & ~(     1 << 17)) | (val &      1) << 17;
        else if (nm == "ack") sr_val = (sr_val & ~(     1 << 18)) | (val &      1) << 18;
        else if (nm == "ap")  sr_val = (sr_val & ~(     7 << 19)) | (val &      7) << 19;
        return cmd.put_register("sr",sr_val);
    }
    else return failed;
}

pdc_commands::instr_type plx_pdc_interface::get_instruction_at(unsigned pc)
{
    long long instr0, instr1, instr2, instr3;
    get_memory_at(cmd.pmem_name,pc+0,instr0);
    get_memory_at(cmd.pmem_name,pc+1,instr1);
    get_memory_at(cmd.pmem_name,pc+2,instr2);
    get_memory_at(cmd.pmem_name,pc+3,instr3);
    long long instr = (instr0 <<24) | (instr1 <<16) | (instr2 << 8) | instr3;
    return instr;
}

void plx_pdc_interface::put_instruction_at(unsigned pc,
                                           pdc_commands::instr_type instr)
{
    put_memory_at(cmd.pmem_name,pc+0,(instr >>24) & 0xff);
    put_memory_at(cmd.pmem_name,pc+1,(instr >>16) & 0xff);
    put_memory_at(cmd.pmem_name,pc+2,(instr >> 8) & 0xff);
    put_memory_at(cmd.pmem_name,pc+3,(instr >> 0) & 0xff);
}

unsigned plx_pdc_interface::next_instruction(unsigned pc) { return pc+4; }
unsigned plx_pdc_interface::prev_instruction(unsigned pc) { return pc-4; }



