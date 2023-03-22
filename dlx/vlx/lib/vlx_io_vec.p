/*
-- File : vlx_io_vec.p
--
-- Contents : Definition of vector loas/store using multiple 32b banks.
--
-- Copyright (c) 2021-2021 Synopsys, Inc. This processor model and the associated
-- documentation are proprietary to Synopsys, Inc.  This model may only be
-- used in accordance with the terms and conditions of a written license
-- agreement with Synopsys, Inc.  All other use, reproduction, or distribution
-- of this model are strictly prohibited.
*/
#include "vlx_define.h"

class v4w8    property(vector w08[4]);


io_interface banks (DMb)
{

#define DM_SIZE 2**(DM_SIZE_NBIT-4)

    trn xdm0_we<v4u1>;
    mem XDM0 [DM_SIZE]<v4w8,addr> access {
        xdm0_ld: xdm0_rd `1` = XDM0[xdm0_ad `0`] `1`;
        xdm0_we: XDM0[xdm0_ad `0`] `1` = xdm0_wr `0`;
    };

    trn xdm1_we<v4u1>;
    mem XDM1 [DM_SIZE]<v4w8,addr> access {
        xdm1_ld: xdm1_rd `1` = XDM1[xdm1_ad `0`] `1`;
        xdm1_we: XDM1[xdm1_ad `0`] `1` = xdm1_wr `0`;
    };

    trn xdm2_we<v4u1>;
    mem XDM2 [DM_SIZE]<v4w8,addr> access {
        xdm2_ld: xdm2_rd `1` = XDM2[xdm2_ad `0`] `1`;
        xdm2_we: XDM2[xdm2_ad `0`] `1` = xdm2_wr `0`;
    };

    trn xdm3_we<v4u1>;
    mem XDM3 [DM_SIZE]<v4w8,addr> access {
        xdm3_ld: xdm3_rd `1` = XDM3[xdm3_ad `0`] `1`;
        xdm3_we: XDM3[xdm3_ad `0`] `1` = xdm3_wr `0`;
    };

    reg p_dm_ad<w32>;

    process process_result() {

        v4w32  xdm_vrd = xdm3_rd::xdm2_rd::xdm1_rd::xdm0_rd;
        uint2_t xdm_ad_bank = p_dm_ad[3:2];   //bank selection
        uint2_t xdm_ad_byte = p_dm_ad[1:0];   //byte selection
        v4w8    xdm_rd_bank = xdm_vrd[xdm_ad_bank];

        dmv_rd = xdm_vrd;
        dmw_rd = xdm_rd_bank;
        dmh_rd = xdm_rd_bank[xdm_ad_byte[1]::"1"]::xdm_rd_bank[xdm_ad_byte[1]::"0"];
        dmb_rd = xdm_rd_bank[xdm_ad_byte];
    }

    process process_request() {
        xdm0_ld = dmv_ld;
        xdm1_ld = dmv_ld;
        xdm2_ld = dmv_ld;
        xdm3_ld = dmv_ld;

        uint4_t dmv_we = dmv_st?"1111":"0000";

        xdm0_we = dmv_we;
        xdm1_we = dmv_we;
        xdm2_we = dmv_we;
        xdm3_we = dmv_we;

        xdm0_ad = dm_ad[DM_SIZE_NBIT-1:4];
        xdm1_ad = dm_ad[DM_SIZE_NBIT-1:4];
        xdm2_ad = dm_ad[DM_SIZE_NBIT-1:4];
        xdm3_ad = dm_ad[DM_SIZE_NBIT-1:4];
        p_dm_ad = dm_ad;

        xdm0_wr = dmv_wr[0];
        xdm1_wr = dmv_wr[1];
        xdm2_wr = dmv_wr[2];
        xdm3_wr = dmv_wr[3];

        uint2_t dm_ad_bank = dm_ad[3:2];   //bank selection
        uint2_t dm_ad_byte = dm_ad[1:0];   //byte selection

        uint1_t xdm_ld = dmw_ld | dmh_ld | dmb_ld;
        uint1_t xdm_st = dmw_st | dmh_st | dmb_st;

        uint4_t xdm_we;
        w32     xdm_wr;
        if      (dmb_st)  { xdm_we = (uint4_t)1 << dm_ad_byte; xdm_wr = dmb_wr::dmb_wr::dmb_wr::dmb_wr; }
        else if (dmh_st)  { xdm_we = dm_ad[1]? "1100": "0011"; xdm_wr = dmh_wr::dmh_wr;                 }
        else   /*dmw_st*/ { xdm_we = "1111";                   xdm_wr = dmw_wr;                         }

        if (xdm_ld) {
          switch (dm_ad_bank) {
          case 0  : xdm0_ld = 1; break;
          case 1  : xdm1_ld = 1; break;
          case 2  : xdm2_ld = 1; break;
          default : xdm3_ld = 1; break;
          }
        }
        if (xdm_st) {
          switch (dm_ad_bank) {
          case 0  : xdm0_we = xdm_we; xdm0_wr = xdm_wr; break;
          case 1  : xdm1_we = xdm_we; xdm1_wr = xdm_wr; break;
          case 2  : xdm2_we = xdm_we; xdm2_wr = xdm_wr; break;
          default : xdm3_we = xdm_we; xdm3_wr = xdm_wr; break;
          }
        }
    }

    void dbg_access_DMb(unsigned a, w08& v, bool read)
    {
        if      (a[3:2] == 0)    dbg_access_XDM0(a[31:4],a[1:0] , v, read);
        else if (a[3:2] == 1)    dbg_access_XDM1(a[31:4],a[1:0] , v, read);
        else if (a[3:2] == 2)    dbg_access_XDM2(a[31:4],a[1:0] , v, read);
        else /* (a[3:2] == 3) */ dbg_access_XDM3(a[31:4],a[1:0] , v, read);
    }

}