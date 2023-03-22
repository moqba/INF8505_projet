/*
-- File : mcld_vector.h
--
-- Contents : Vector application layer for the MCLD processor.
--
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/



#ifndef _mcld_vector_h
#define _mcld_vector_h

class  vint_t property( vector      int[4] );
chess_property{
    representation  vint_t : v4w32;
}
class vint_t {
    inline vint_t(int, int, int, int);
    vint_t(int);
};



promotion vint_t vbcast(int)  = v4w32(w32);
promotion vint_t vneg(vint_t) = v4w32 vneg(v4w32);
promotion int    vsum(vint_t) = w32   vsum(v4w32);


#endif // _mcld_vector_h

