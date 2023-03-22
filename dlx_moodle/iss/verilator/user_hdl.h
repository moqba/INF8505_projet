/*
-- File : user_hdl.h
--
-- Contents : Header file for functions included in ISS model for Verilator
--
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model 
-- captures an ASIP Designer Design Technique. The model and all associated 
-- documentation are proprietary to Synopsys, Inc. and may only be used 
-- pursuant to the terms and conditions of a written license agreement with 
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution 
-- of the Synopsys processor model or the associated  documentation is 
-- stricfly prohibited. 
*/

#ifndef _USER_HDL_H
#define _USER_HDL_H

#include "dlx_define.h"

void verilator_fini(dlx* proc);

#endif // _USER_HDL_H
