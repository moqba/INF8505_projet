/*
-- File : plx_io.p
--
-- Contents : Definition of the PLX IO interface.
--
-- Copyright (c) 2014-2017 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

//#define     PRINT_LRSC
#ifdef        PRINT_LRSC
#define DEBUG_PRINT_LRSC(FMT,ARGS...) DEBUG_PRINT("lrsc: "FMT, ##ARGS)
#else
#define DEBUG_PRINT_LRSC(FMT,ARGS...)
#endif

#ifdef _THREADED

#include "memsize.h"

io_interface retry (DMb, dm_ack, dm_wait)
{
    mem eDMb [DM_SIZE,1]<w08,addr> access {
        ld_edmb: edmb_rd`1` = eDMb[edm_addr]`1`;
        st_edmb: eDMb[edm_addr]`1` = edmb_wr;
    };
    mem eDMh [DM_SIZE,2]<w16,addr> alias eDMb access {
        ld_edmh: edmh_rd`1` = eDMh[edm_addr]`1`;
        st_edmh: eDMh[edm_addr]`1` = edmh_wr;
    };
    mem eDMw [DM_SIZE,4]<w32,addr> alias eDMb access {
        ld_edmw: edmw_rd`1` = eDMw[edm_addr]`1`;
        st_edmw: eDMw[edm_addr]`1` = edmw_wr;
    };

    inport  edm_ack<uint1>;

    reg r_dm_ack<uint1>;
    reg r_st1<bool>;
    reg r_st2<bool>;
    reg r_ld1<bool>;
    reg r_ld2<bool>;
    reg r_ocd_ld_DMb<bool>;
    reg r_ocd_st_DMb<bool>;
    reg r_ld_dmw<bool>;
    reg r_st_dmw<bool>;
    reg r_dm_addr<addr>;
    reg r_dmw_wr<w32>;

    process process_result() {
        dmb_rd = edmb_rd;
        dmh_rd = edmh_rd;
        dmw_rd = edmw_rd;
        if (r_ld1) ocd_data = ocd_data_w = edmb_rd;
        dm_ack = r_dm_ack;
        r_dm_ack = edm_ack;
    }
    process process_request()
    {
        // DMb access from (DBG_DMb_LOAD_INSTR|DBG_DMb_STORE_INSTR)
        r_ocd_ld_DMb = ocd_ld_DMb;
        r_ocd_st_DMb = ocd_st_DMb;
        // DMw access from DBG_EXECUTE_INSTR
        r_st_dmw  = st_dmw;
        r_ld_dmw  = ld_dmw;

        bool l_ld1 = (r_ocd_ld_DMb            | r_ld1) & !r_dm_ack; r_ld1 = l_ld1;
        bool l_st1 = (r_ocd_st_DMb            | r_st1) & !r_dm_ack; r_st1 = l_st1;
        bool l_ld2 = ((ocd_exe_DM & r_ld_dmw) | r_ld2) & !r_dm_ack; r_ld2 = l_ld2;
        bool l_st2 = ((ocd_exe_DM & r_st_dmw) | r_st2) & !r_dm_ack; r_st2 = l_st2;

        bool l_blocking = l_ld1 | l_st1 | l_ld2 | l_st2;

        if (!l_blocking) {
            r_dm_addr = dm_addr;
            if (st_dmw) r_dmw_wr = dmw_wr;
            //if (st_dmh) r_dmw_wr = dmh_wr;
            if (st_dmb) r_dmw_wr = dmb_wr;
        }

        dm_wait = l_blocking | r_ld1 | r_ld2;

        if (l_ld2 | l_st2) { stall_instr(ME); }

        edm_addr = (l_blocking) ? r_dm_addr : dm_addr;

        edmb_wr = l_st1 ? (w08)r_dmw_wr : dmb_wr;
        edmh_wr = dmh_wr;
        edmw_wr = l_st2 ?      r_dmw_wr : dmw_wr;

        st_edmb = l_st1 ? 1 : st_dmb;
        st_edmh = st_dmh;
        st_edmw = l_st2 ? 1 : st_dmw;

        ld_edmb = l_ld1 ? 1 : ld_dmb;
        ld_edmh = ld_dmh;
        ld_edmw = l_ld2 ? 1 : ld_dmw;
    }
    void dbg_access_DMb(unsigned a, w08& v, bool read)
    {
        dbg_access_eDMb(a, v, read);
    }
}


#include "plx_cache.p"

io_interface prbs() // pseudo-random binary sequence
{
    outport busy<uint1>;

    reg r_lfsr<uint16_t>;     // linear-feedback shift register
    hw_init r_lfsr = 0xace1;

    process process_result() {
#if 1
        busy = r_lfsr[0];
#ifdef PAGE0
        busy &= (get_tag(edm_addr)!=0); // DM[0:15] is private
#endif
#else
        busy = 0;
#endif
    }
    process process_request() {
        // uint1 bit = lfsr[0] ^ lfsr[2] ^ lfsr[3] ^ lfsr[5];
        // lfsr = bit::lfsr[15:1];
        uint16_t l_bit = ((r_lfsr >> 0) ^ (r_lfsr >> 2) ^ (r_lfsr >> 3) ^ (r_lfsr >> 5)) & (uint1)1;
        r_lfsr = (r_lfsr >> 1) | (l_bit << 15);
    }
}


io_interface glue(miss,busy)
{
    process process_result() {
    }
    process process_request() {
        edm_ack = (!miss & !busy);
    }
}

#if 1
io_interface lrsc(lrsc_ena,lrsc_ack)
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
        lrsc_st = 0;
        if (edm_ack) {
            if (ld_edmw & lrsc_ena) {
                r_adr = edm_addr;
                r_ctx = ctx_id;
                r_rsv = true;
                DEBUG_PRINT_LRSC("reservation on addr=%d by r_ctx=%d",edm_addr, ctx_id);
            }
            bool l_match = r_rsv & r_ctx==ctx_id & (edm_addr|3)==(r_adr|3);
            if (st_edmw & lrsc_ena) {
                if (l_match) {
                    r_ack = 1;
                    DEBUG_PRINT_LRSC("proceed store");
                } else {
                    r_ack = 0;
                    DEBUG_PRINT_LRSC("block store");
                }
            }
            if ((st_edmw|st_edmh|st_edmb) & !lrsc_ena & (edm_addr|3)==(r_adr|3)) {
                r_rsv = false;
                DEBUG_PRINT_LRSC("cancel reservation");
            }
            lrsc_st = st_edmw & (!lrsc_ena | l_match);
        }
    }
}
#else
#define lrsc_st st_edmw
#endif

io_interface banks (eDMb)
{
    mem DM0 [DM_SIZE]<w08,addr> access {
        ld0: dm0_rd `1` = DM0[dm0_addr `0`] `1`;
        st0: DM0[dm0_addr `0`] `1` = dm0_wr `0`;
    };
    mem DM1 [DM_SIZE]<w08,addr> access {
        ld1: dm1_rd `1` = DM1[dm1_addr `0`] `1`;
        st1: DM1[dm1_addr `0`] `1` = dm1_wr `0`;
    };
    mem DM2 [DM_SIZE]<w08,addr> access {
        ld2: dm2_rd `1` = DM2[dm2_addr `0`] `1`;
        st2: DM2[dm2_addr `0`] `1` = dm2_wr `0`;
    };
    mem DM3 [DM_SIZE]<w08,addr> access {
        ld3: dm3_rd `1` = DM3[dm3_addr `0`] `1`;
        st3: DM3[dm3_addr `0`] `1` = dm3_wr `0`;
    };

    reg ld0_ff<uint1_t>;
    reg ld1_ff<uint1_t>;
    reg ld2_ff<uint1_t>;
    reg ld3_ff<uint1_t>;

    reg dummy<uint1_t>;

    process process_result() {
        edmw_rd = dm0_rd::dm1_rd::dm2_rd::dm3_rd;

        edmh_rd = 0;
        if      (ld0_ff) edmh_rd = dm0_rd::dm1_rd;
        else if (ld2_ff) edmh_rd = dm2_rd::dm3_rd;

        edmb_rd = 0;
        if      (ld0_ff) edmb_rd = dm0_rd;
        else if (ld1_ff) edmb_rd = dm1_rd;
        else if (ld2_ff) edmb_rd = dm2_rd;
        else if (ld3_ff) edmb_rd = dm3_rd;
    }

    process process_request() {

        dummy = st_edmw | dummy;

        dm0_addr = edm_addr[18:2];
        dm1_addr = edm_addr[18:2];
        dm2_addr = edm_addr[18:2];
        dm3_addr = edm_addr[18:2];

        uint2_t dma2 = edm_addr[1:0];
        uint1_t tld0 = ((ld_edmb && dma2 == 0) || (ld_edmh && dma2 == 0) || ld_edmw) & edm_ack;
        uint1_t tld1 = ((ld_edmb && dma2 == 1) || (ld_edmh && dma2 == 0) || ld_edmw) & edm_ack;
        uint1_t tld2 = ((ld_edmb && dma2 == 2) || (ld_edmh && dma2 == 2) || ld_edmw) & edm_ack;
        uint1_t tld3 = ((ld_edmb && dma2 == 3) || (ld_edmh && dma2 == 2) || ld_edmw) & edm_ack;

        ld0 = tld0;
        ld1 = tld1;
        ld2 = tld2;
        ld3 = tld3;

        ld0_ff = tld0;
        ld1_ff = tld1;
        ld2_ff = tld2;
        ld3_ff = tld3;

        st0 = ((st_edmb && dma2 == 0) || (st_edmh && dma2 == 0) || lrsc_st) & edm_ack;
        st1 = ((st_edmb && dma2 == 1) || (st_edmh && dma2 == 0) || lrsc_st) & edm_ack;
        st2 = ((st_edmb && dma2 == 2) || (st_edmh && dma2 == 2) || lrsc_st) & edm_ack;
        st3 = ((st_edmb && dma2 == 3) || (st_edmh && dma2 == 2) || lrsc_st) & edm_ack;

        dm0_wr = lrsc_st ? edmw_wr[31:24] : st_edmh ? edmh_wr[15: 8] : edmb_wr;
        dm1_wr = lrsc_st ? edmw_wr[23:16] : st_edmh ? edmh_wr[ 7: 0] : edmb_wr;
        dm2_wr = lrsc_st ? edmw_wr[15: 8] : st_edmh ? edmh_wr[15: 8] : edmb_wr;
        dm3_wr = lrsc_st ? edmw_wr[ 7: 0] : st_edmh ? edmh_wr[ 7: 0] : edmb_wr;
    }

    void dbg_access_eDMb(unsigned a, w08& v, bool read)
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

#endif // _THREADED
