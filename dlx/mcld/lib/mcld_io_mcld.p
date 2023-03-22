/*
-- File : mcld_io_mcld.p
--
-- Contents : Definition of iterative vector load/store.
--
-- Copyright (c) 2014-2021 Synopsys, Inc. This processor model and the associated
-- documentation are proprietary to Synopsys, Inc.  This model may only be
-- used in accordance with the terms and conditions of a written license
-- agreement with Synopsys, Inc.  All other use, reproduction, or distribution
-- of this model are strictly prohibited.
*/



#include "mcld_define.h"

#define dm_size 2**DM_SIZE_NBIT
io_interface banks (DMb)
{
    class v4u1    property( vector uint1[4]);
    class v4w8    property(vector w08[4]);

    trn xdm_we<v4u1>;
    mem XDM [dm_size]<v4w8,addr> access {
        xdm_ld: xdm_rd `1` = XDM[xdm_ad `0`] `1`;
        xdm_we: XDM[xdm_ad `0`] `1` = xdm_wr `0`;
    };

    /*
       A vector load is executed by doing 4 consecutive element loads.
       The timing is as folows ('Ai' is the address phase of a load, 'Di' is
       the data phase.

       Cycle    :   0     1     2     3     4    5
       ---------:----------------------------------
       A-phase  :   A0    A1    A2    A3
       D-phase  :         D0    D1    D2    D3
       dmv_ld   :   1     0     0     0     0    0
       rv_ld    :   0     1     1     1     1    0
       rv_elem  :   0     3     2     1     0    0
       rv_addr  :   a     a+1   a+2   a+3
       rv_data  :         a000  ab00  abc0  abcd


       The timing for a store is as follows

       Cycle    :   0     1     2     3     4    5
       ---------:----------------------------------
       A-phase  :   A0    A1    A2    A3
       D-phase  :   D0    D1    D2    D3
       dmv_st   :   1     0     0     0     0
       rv_st    :   0     1     1     1     0
       rv_elem  :   0     2     1     0
       rv_addr  :   a     a+1   a+2   a+3

       // RAW hazard (hw_stall_lv_dpcy)
       lv_dpcy  :   1     1     1     1     0    0
       lv       :   EX    -     -     -     wr   -
       rd from V:   -     -     -     ID*   ID   EX(rd)

       // WAW hazard (hw_stall_lv_out)
       wr to V  :   -     -     -     ID*   ID   EX(wr)

       // lv-lv sequence (hw_stall_lv_lv)
       lv_busy  :   1     1     1     0     0    0
       lv       :   A0    A1    A2    A3
                          D0    D1    D2    D3
       lv       :               ID*   ID    A0   A1
                                                 D0

       // lv-sv sequence (hw_stall_lv_sv)
       lv_busy  :   1     1     1     0     0    0
       lv       :   A0    A1    A2    A3
                          D0    D1    D2    D3
       sv       :               ID*   ID    A0   A1
                                            D0   D1

       // sv-lv sequence (hw_stall_sv_lv)
       sv_busy  :   1     1     1     0     0    0
       sv       :   A0    A1    A2    A3
                    D0    D1    D2    D3
       lv       :               ID*   ID    A0   A1
                                                 D0   D1

       // sv-sv sequence (hw_stall_sv_sv)
       sv_busy  :   1     1     1     0     0    0
       sv       :   A0    A1    A2    A3
                    D0    D1    D2    D3
       sv       :               ID*   ID    A0   A1
                                            D0   D1

    */

    reg rv_ld<uint1_t>;    // set during data phases of load
    reg rv_st<uint1_t>;    // set during phases of store
    reg rv_elem<uint2_t>;  // iteration counter and vector index
    reg rv_addr<addr>;     // address counter
    reg rv_data<v4w32>;     // partial result of load, buffer for store
    reg rv_idx<uint2>;     // index of load destination reg
    reg idx<uint2>;
    reg p_dm_ad<w32>;


    process process_result() {

        dmw_rd = xdm_rd;
        dmh_rd = p_dm_ad[1]? (xdm_rd[3]::xdm_rd[2]) : (xdm_rd[1]::xdm_rd[0]);
        uint2_t dm_ad2 = p_dm_ad;
        dmb_rd = xdm_rd[dm_ad2];

        w32 w0 = 0;
        lv_write_idx = 0;
        if (rv_ld) {
            v4w32 tmp_data = rv_data;
            if (rv_elem > 0) {
               tmp_data[rv_elem] = xdm_rd;
               rv_data = tmp_data;
            } else {
               tmp_data[rv_elem] = xdm_rd;
               V[rv_idx] = vw_ld = /* dmv_rd = */ tmp_data;
               lv_write = 1;
               lv_write_idx = idx;
            }
        }
        if (dmv_st) // save to be stored data
            rv_data = dmv_wr;
    }



    process process_request() {

        // copy signals for plain DMw load/store
        xdm_ad = dm_ad[31:2];
        p_dm_ad = dm_ad;
        xdm_ld = dmw_ld | dmh_ld | dmb_ld;

        if(dmb_st){
            xdm_wr = dmb_wr::dmb_wr::dmb_wr::dmb_wr;
            uint2_t dm_ad2 = dm_ad;
            xdm_we = ((uint4_t)1)<<dm_ad2;
        }

        if(dmh_st){
            xdm_wr = dmh_wr ::dmh_wr;
            xdm_we = dm_ad[1]? "1100": "0011";
        }

        if(dmw_st){
            xdm_wr = dmw_wr;
            xdm_we = (uint4_t)"1111";
        }

        rv_ld = 0;
        rv_st = 0;
        if (dmv_ld) {             // cycle 0 of load
            rv_addr = dm_ad[31:2] + 1;
            xdm_ld = 1;
            rv_ld = 1;
            rv_elem = 3;
            rv_idx = tv_idx;
        }
        if (rv_ld && rv_elem > 0) { // cycles 1 .. 3 of load
            xdm_ad = rv_addr;
            rv_addr = rv_addr + 1;
            xdm_ld = 1;
            rv_ld = 1;
            rv_elem = rv_elem - 1;
        }

        if (dmv_st) {             // cycle 0 of store
            rv_addr = dm_ad[31:2] + 1;
            xdm_wr = dmv_wr[3];
            xdm_we = (uint4_t)"1111";
            rv_st = 1;
            rv_elem = 2;
        }
        if (rv_st && rv_elem >= 0) { // cycles 1 .. 3 of store
            xdm_ad = rv_addr;
            rv_addr = rv_addr + 1 ;
            xdm_wr = rv_data[rv_elem];
            xdm_we = (uint4_t)"1111";
            rv_st = rv_elem > 0;
            if (rv_elem >0) {
            rv_elem = rv_elem - 1;
            }
        }

        lv_dpcy = dmv_ld || rv_elem > 0;
        lv_busy = dmv_ld || rv_ld && rv_elem>1;
        sv_busy = dmv_st || rv_st && rv_elem>0;

        lv_idx  = dmv_ld ? tv_idx : rv_idx;
        idx     = dmv_ld ? tv_idx : rv_idx;
    }

    void dbg_access_DMb(unsigned a, w08& v, bool read) {
        dbg_access_XDM(a[31:2],a[1:0] , v, read);
    }

}



