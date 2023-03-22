/*
-- File : dlx_pdc_interface.h
--
-- Contents : Specialisation of Checkers_pdc_interface for DLX procesor
--
-- Copyright (c) 2014-2018 Synopsys, Inc. This Synopsys processor model 
-- captures an ASIP Designer Design Technique. The model and all associated 
-- documentation are proprietary to Synopsys, Inc. and may only be used 
-- pursuant to the terms and conditions of a written license agreement with 
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution 
-- of the Synopsys processor model or the associated  documentation is 
-- strictly prohibited. 
*/


 
#ifndef _dlx_pdc_interface_h
#define _dlx_pdc_interface_h

#include "checkers_pdc_interface.h"

class dlx_pdc_interface : public Checkers_pdc_interface {
public:
 dlx_pdc_interface(int coreid, string server, int port=41001)
   : Checkers_pdc_interface(coreid, server, port) { }

    virtual bool expand_into_root_locations(const Checkers_storinfo*);

    virtual pdc_commands::instr_type get_instruction_at(AddressType pc);
    virtual void put_instruction_at(AddressType pc,
                                    pdc_commands::instr_type instr);
    virtual AddressType next_instruction(AddressType pc);
    virtual AddressType prev_instruction(AddressType pc);


protected:
};

#endif
