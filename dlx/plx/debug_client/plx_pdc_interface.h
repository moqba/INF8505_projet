/*
-- File : plx_pdc_interface.h
--
-- Contents : Specialisation of Checkers_pdc_interface for PLX procesor
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/



#ifndef _plx_pdc_interface_h
#define _plx_pdc_interface_h

#include "checkers_pdc_interface.h"

class plx_pdc_interface : public Checkers_pdc_interface {
public:
    plx_pdc_interface(int coreid, string server, int port=41001)
        : Checkers_pdc_interface(coreid, server, port) { }

    virtual int get_register(string nm, long long& val);
    virtual int put_register(string nm, long long val);
    virtual bool expand_into_root_locations(const Checkers_storinfo*);

    virtual pdc_commands::instr_type get_instruction_at(unsigned pc);
    virtual void put_instruction_at(unsigned pc,
                                    pdc_commands::instr_type instr);
    virtual unsigned next_instruction(unsigned pc);
    virtual unsigned prev_instruction(unsigned pc);

protected:
    virtual void load_reg_cache();
};

#endif
