/*
-- File : ilx_io.p
--
-- Contents : Definition of the ILX IO interface.
--
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/



//#include "ilx_define.h"

io_interface lrsc(lrsc_ena, lrsc_ack)
{
    outport lrsc_st<uint1>;

    reg r_adr<addr>;
    reg r_ctx<ctxt>;
    reg r_rsv<uint1>;
    reg r_ack<uint1>;

    process process_result()
    {
        lrsc_ack = r_ack;
    }
    process process_request()
    {
        r_ack = 0;
        if (dmw_ld & lrsc_ena) {
            r_adr = dm_ad;
            r_ctx = ctx_id;
            r_rsv = true;
            DEBUG_PRINT("reservation on addr=%d by r_ctx=%d",dm_ad, ctx_id);
        }
        bool l_match = r_rsv & r_ctx==ctx_id & (dm_ad|3)==(r_adr|3);
        if (dmw_st & lrsc_ena) {
            if (l_match) {
                r_ack = 1;
                DEBUG_PRINT("proceed store");
            } else {
                r_ack = 0;
                DEBUG_PRINT("block store");
            }
        }
        if ((dmw_st|dmh_st|dmb_st) & !lrsc_ena & (dm_ad|3)==(r_adr|3)) {
            r_rsv = false;
            DEBUG_PRINT("cancel reservation");
        }
        lrsc_st = (!lrsc_ena | l_match);
    }
}