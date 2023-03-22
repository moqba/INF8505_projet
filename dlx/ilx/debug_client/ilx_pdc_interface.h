/*
-- File : ilx_pdc_interface.h
--
-- Contents : Specialisation of Checkers_pdc_interface for ILX procesor
--
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/



#ifndef _ilx_pdc_interface_h
#define _ilx_pdc_interface_h

#include "ilx_define.h"
#include "checkers_pdc_interface.h"

class ilx_pdc_interface : public Checkers_pdc_interface {
public:
 ilx_pdc_interface(int coreid, string server, int port=41001)
   : Checkers_pdc_interface(coreid, server, port) { }
    virtual int put_register(string name, const DataType& val);
    virtual bool expand_into_root_locations(const Checkers_storinfo*);

    virtual pdc_commands::instr_type get_instruction_at(AddressType pc);
    virtual void put_instruction_at(AddressType pc,
                                    pdc_commands::instr_type instr);
    virtual AddressType next_instruction(AddressType pc);
    virtual AddressType prev_instruction(AddressType pc);


protected:
    virtual void load_reg_cache();
};

#endif
