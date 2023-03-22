/*
-- File : ilx_div.p
--
-- Contents : Definition of multi cycle divide unit.
--
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

void divide(w32 numerator, w32 denominator, w32& quotient, w32& remainder)
{
    quotient = (uint32_t)numerator / (uint32_t)denominator;
    remainder = (uint32_t)numerator % (uint32_t)denominator;
}

uint64_t div_step(uint64_t pa, uint32_t b)
{
    uint64_t new_pa = pa << 1;
    uint33_t diff = (uint33_t)(new_pa[63:32]) - b;
    if (diff[32] == 0) {
        new_pa[63:32] = diff;
        new_pa[0] = 1;
    }
    return new_pa;
}

#ifndef _ISS_ST

w32 div_clb(w32 a) // count number redundant leading bits
{
    uint5_t r;
    w32 tmp = a;
    if      (tmp[31: 0] == 0) r = 31;
    else if (tmp[31: 1] == 0) r = 30;
    else if (tmp[31: 2] == 0) r = 29;
    else if (tmp[31: 3] == 0) r = 28;
    else if (tmp[31: 4] == 0) r = 27;
    else if (tmp[31: 5] == 0) r = 26;
    else if (tmp[31: 6] == 0) r = 25;
    else if (tmp[31: 7] == 0) r = 24;
    else if (tmp[31: 8] == 0) r = 23;
    else if (tmp[31: 9] == 0) r = 22;

    else if (tmp[31:10] == 0) r = 21;
    else if (tmp[31:11] == 0) r = 20;
    else if (tmp[31:12] == 0) r = 19;
    else if (tmp[31:13] == 0) r = 18;
    else if (tmp[31:14] == 0) r = 17;
    else if (tmp[31:15] == 0) r = 16;
    else if (tmp[31:16] == 0) r = 15;
    else if (tmp[31:17] == 0) r = 14;
    else if (tmp[31:18] == 0) r = 13;
    else if (tmp[31:19] == 0) r = 12;

    else if (tmp[31:20] == 0) r = 11;
    else if (tmp[31:21] == 0) r = 10;
    else if (tmp[31:22] == 0) r =  9;
    else if (tmp[31:23] == 0) r =  8;
    else if (tmp[31:24] == 0) r =  7;
    else if (tmp[31:25] == 0) r =  6;
    else if (tmp[31:26] == 0) r =  5;
    else if (tmp[31:27] == 0) r =  4;
    else if (tmp[31:28] == 0) r =  3;
    else if (tmp[31:29] == 0) r =  2;

    else if (tmp[31:30] == 0) r =  1;
    else                      r =  0;

    return r;
}

multicycle_fu div
{
    reg cnt<uint6_t>;
    reg PA<uint64_t>;
    reg B<uint32_t>;
    reg C<ctxt>;

    process main () {
        uint6_t new_cnt = 0;
        // steps
        if (cnt > 1) {
            PA = div_step(PA, B);
            new_cnt = cnt - 1;
        }
        // post-amble
        if (cnt == 1) {
            uint64_t pa = PA;
            PL.context(C) = wl = pa[31:0];
            PH.context(C) = wh = pa[63:32];
            new_cnt = cnt - 1;
        }
        // pre-amble
        if (vd_divide_divA_divB_wl_wh_div_EX_sig) {
            uint5_t n = div_clb((uint32_t)divA);
            PA = (uint32_t)divA << n;
            B = divB;
            C = context_id_EX;
            new_cnt = 33 - n;
        }
        // post-amble (cnt==1) and pre-amble of new div may overlap
        cnt = new_cnt;
        div_busy_0 = (cnt > 0) && (context_id_ID == C);
        div_busy_3 = (cnt > 3) && (context_id_ID == C);
        div_busy_2 = vd_divide_divA_divB_wl_wh_div_EX_sig || (cnt > 2);
    }
}

/*

-------------------------------------
cnt              | 2  | 1    | 8    |
-------------------------------------
ctx              | 0  | 0    | 1    |
-------------------------------------
<0>div r2,r3     |    | WB   |      |
                 |    | r12= |      |
                 |    | =pa  |      |
-------------------------------------
<1>div r4,r5     | ID | EX   |      |
                 |    | pa=  |      |
-------------------------------------
<0>sw r12,-4(sp) |    |      |  ID  |
                 |    |      | =r12 |
-------------------------------------
<0>lw r12,-4(sp) |    |      |  WB  |
                 |    |      | r12= |
-------------------------------------

*/

#else

multicycle_fu div
{
    process main () {
        if (vd_divide_divA_divB_wl_wh_div_ID_sig) {
            uint64_t PA = (uint32_t)divA;
            for (uint32_t i=0; i<32; i++ )
                PA = div_step(PA, divB);
            PL = wl = PA[31:0];
            PH = wh = PA[63:32];
        }
    }
}

#endif
