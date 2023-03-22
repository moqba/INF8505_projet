/*
-- File : plx_hw.h
--
-- Contents : Processor header-file for the PLX processor.
--
-- Copyright (c) 2014-2017 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

#ifndef _plx_hw_h
#define _plx_hw_h

namespace plx_primitive {
    class w64   property(64 bit signed);
    class tag   property(64 bit signed);
    class v4tag property(vector tag[4]);
}

#endif

