/*
-- File : dlx_const.h
--
-- Contents : Constant generation for the DLX core.
--
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/



#ifndef _dlx_const_h
#define _dlx_const_h


namespace dlx_primitive {
    inline void chess_convert( uint16 lsb,int16p msb, w32& L)
    {
        L = bor(lhi(msb),lsb);
    }
};


chess_properties {
    convert_routing_const w32 : R;
}

#endif /* _dlx_const_h */
