/*
-- File : plx_const.h
--
-- Contents : Constant generation for the PLX core.
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/



#ifndef _plx_const_h
#define _plx_const_h


namespace plx_primitive {
    inline void chess_convert(int16p msb, uint16 lsb, w32& L)
    {
        L = bor(lhi(msb),lsb);
    }
};


chess_properties {
    convert_routing_const w32 : R;
}

#endif /* _plx_const_h */
