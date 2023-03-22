/*
-- File : dlx_io.p
--
-- Contents : Definition of the DLX IO interface.
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model 
-- captures an ASIP Designer Design Technique. The model and all associated 
-- documentation are proprietary to Synopsys, Inc. and may only be used 
-- pursuant to the terms and conditions of a written license agreement with 
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution 
-- of the Synopsys processor model or the associated  documentation is 
-- strictly prohibited. 
*/




#include "dlx_define.h"

io_interface banks (DMb)
{
    
#define dm_bank_size 2**(DM_SIZE_NBIT-2)

    mem DM0 [dm_bank_size]<w08,addr> access {
        ld0: dm0_rd `1` = DM0[dm0_addr `0`] `1`;
        st0: DM0[dm0_addr `0`] `1` = dm0_wr `0`;
    };
    mem DM1 [dm_bank_size]<w08,addr> access {
        ld1: dm1_rd `1` = DM1[dm1_addr `0`] `1`;
        st1: DM1[dm1_addr `0`] `1` = dm1_wr `0`;
    };
    mem DM2 [dm_bank_size]<w08,addr> access {
        ld2: dm2_rd `1` = DM2[dm2_addr `0`] `1`;
        st2: DM2[dm2_addr `0`] `1` = dm2_wr `0`;
    };
    mem DM3 [dm_bank_size]<w08,addr> access {
        ld3: dm3_rd `1` = DM3[dm3_addr `0`] `1`;
        st3: DM3[dm3_addr `0`] `1` = dm3_wr `0`;
    };

    reg ld0_ff<uint1_t>;
    reg ld1_ff<uint1_t>;
    reg ld2_ff<uint1_t>;
    reg ld3_ff<uint1_t>;

    process process_result() {
        dmw_rd = dm0_rd::dm1_rd::dm2_rd::dm3_rd;

        if      (ld0_ff) dmh_rd = dm0_rd::dm1_rd;
        else if (ld2_ff) dmh_rd = dm2_rd::dm3_rd;

        if      (ld0_ff) dmb_rd = dm0_rd;
        else if (ld1_ff) dmb_rd = dm1_rd;
        else if (ld2_ff) dmb_rd = dm2_rd;
        else if (ld3_ff) dmb_rd = dm3_rd;
    }

    process process_request() {
        dm0_addr = dm_addr[DM_SIZE_NBIT-1:2];
        dm1_addr = dm_addr[DM_SIZE_NBIT-1:2];
        dm2_addr = dm_addr[DM_SIZE_NBIT-1:2];
        dm3_addr = dm_addr[DM_SIZE_NBIT-1:2];

        uint2_t dma2 = dm_addr[1:0];
        uint1_t tld0 = (ld_dmb && dma2 == 0) || (ld_dmh && dma2 == 0) || ld_dmw;
        uint1_t tld1 = (ld_dmb && dma2 == 1) || (ld_dmh && dma2 == 0) || ld_dmw;
        uint1_t tld2 = (ld_dmb && dma2 == 2) || (ld_dmh && dma2 == 2) || ld_dmw;
        uint1_t tld3 = (ld_dmb && dma2 == 3) || (ld_dmh && dma2 == 2) || ld_dmw;

        ld0 = tld0;
        ld1 = tld1;
        ld2 = tld2;
        ld3 = tld3;

        ld0_ff = tld0;
        ld1_ff = tld1;
        ld2_ff = tld2;
        ld3_ff = tld3;

        st0 = (st_dmb && dma2 == 0) || (st_dmh && dma2 == 0) || st_dmw;
        st1 = (st_dmb && dma2 == 1) || (st_dmh && dma2 == 0) || st_dmw;
        st2 = (st_dmb && dma2 == 2) || (st_dmh && dma2 == 2) || st_dmw;
        st3 = (st_dmb && dma2 == 3) || (st_dmh && dma2 == 2) || st_dmw;

        dm0_wr = st_dmw ? dmw_wr[31:24] : st_dmh ? dmh_wr[15: 8] : dmb_wr;
        dm1_wr = st_dmw ? dmw_wr[23:16] : st_dmh ? dmh_wr[ 7: 0] : dmb_wr;
        dm2_wr = st_dmw ? dmw_wr[15: 8] : st_dmh ? dmh_wr[15: 8] : dmb_wr;
        dm3_wr = st_dmw ? dmw_wr[ 7: 0] : st_dmh ? dmh_wr[ 7: 0] : dmb_wr;
    }

    void dbg_access_DMb(unsigned a, w08& v, bool read)
    {
        if (a[1:0] == 0)
            dbg_access_DM0(a[31:2], v, read);
        else if (a[1:0] == 1)
            dbg_access_DM1(a[31:2], v, read);
        else if (a[1:0] == 2)
            dbg_access_DM2(a[31:2], v, read);
        else if (a[1:0] == 3)
            dbg_access_DM3(a[31:2], v, read);
    }

}

