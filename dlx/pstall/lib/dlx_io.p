/*
-- File : dlx_io.p
--
-- Contents : Definition of the DLX IO interface.
--
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/


#include "dlx_define.h"

class v4w8    property(vector w08[4]);
class v2w8    property(vector w08[2]);
class v4u1    property( vector uint1[4]);

io_interface mem_byte_write_enable(DMb)
{

#define dm_size 2**DM_SIZE_NBIT

    trn xdm_we<v4u1>;
    mem XDM [dm_size]<v4w8,addr> access {
        xdm_ld: xdm_rd `1` = XDM[xdm_ad `0`] `1`;
        xdm_we: XDM[xdm_ad `0`] `1` = xdm_wr `0`;
    };

    reg p_dm_ad<w32>;
    reg dmb_st_ff<uint1_t>;
    reg dmh_st_ff<uint1_t>;
    reg dmw_st_ff<uint1_t>;
    reg dm_ad_ff<addr>;

    process process_result() {
        dmw_rd = xdm_rd;
        dmh_rd = p_dm_ad[1]? (xdm_rd[3]::xdm_rd[2]) : (xdm_rd[1]::xdm_rd[0]);
        uint2_t dm_ad2 = p_dm_ad;
        dmb_rd = xdm_rd[dm_ad2];
    }

    process process_request() {

          // copy signals for plain DMw load/store
        xdm_ad = dm_ad[31:2];
        p_dm_ad = dm_ad;    // address is given in this sycle, but accessed next sycle
        xdm_ld = dmw_ld | dmh_ld | dmb_ld;
        xdm_we = 0;
        xdm_wr = 0;

        if(dmb_st){
            xdm_wr = dmb_wr::dmb_wr::dmb_wr::dmb_wr;
            uint2_t dm_ad2 = dm_ad;
            xdm_we = ((uint4_t)1)<<dm_ad2;
        }
         if(dmh_st){
            xdm_wr = dmh_wr ::dmh_wr;
            xdm_we = dm_ad[1]? "1100": "0011";
        }

        if(dmw_st) {
            xdm_wr = dmw_wr;
            xdm_we = (uint4_t)"1111";
        }

        uint1_t st_ld_stall = (dmb_st_ff && dmb_ld ||                        // check st-ld sequence
                               dmh_st_ff && dmh_ld ||
                               dmw_st_ff && dmw_ld)   && dm_ad==dm_ad_ff ||

                               (dmb_st_ff && dmh_ld && dm_ad[31:1] == dm_ad_ff[31:1])||
                               (dmb_st_ff && dmw_ld && dm_ad[31:2] == dm_ad_ff[31:2])||

                               (dmh_st_ff && dmb_ld && dm_ad[31:1] == dm_ad_ff[31:1])||
                               (dmh_st_ff && dmw_ld && dm_ad[31:2] == dm_ad_ff[31:2])||

                               (dmw_st_ff && dmb_ld && dm_ad[31:2] == dm_ad_ff[31:2])||
                               (dmw_st_ff && dmh_ld && dm_ad[31:2] == dm_ad_ff[31:2])
                               ;
        DEBUG_PRINT("IO %d %d %d",st_ld_stall, dm_ad, dm_ad_ff);

        if (st_ld_stall)
            stall_instr(EX);

        // save store address
        dmb_st_ff = dmb_st;
        dmh_st_ff = dmh_st;
        dmw_st_ff = dmw_st;
        dm_ad_ff = (dmb_st || dmh_st || dmw_st) ? dm_ad : 0;

    }

    void dbg_access_DMb(unsigned a, w08& v, bool read) {
        dbg_access_XDM(a[31:2],a[1:0] , v, read);
    }
}

