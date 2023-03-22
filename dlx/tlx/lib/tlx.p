/*
-- File : tlx.p
--
-- Contents : Definition of the TLX primitives.
--
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

#include "tlx_define.h"



w32 add(w32 a, w32 b, uint1& co)
{
    uint33_t aa = (uint32_t)a;
    uint33_t bb = (uint32_t)b;
    uint33_t rr = aa + bb;
    co = rr[32];
    return rr[31:0];
}

w32 add(w32 a, w32 b) { return a + b; }

w32 sub(w32 a, w32 b, uint1& co)
{
    uint33_t aa = (uint32_t)a;
    uint33_t bb = (uint32_t)b;
    uint33_t rr = aa - bb;
    co = rr[32];
    return rr[31:0];
}

w32 addx(w32 a, w32 b, uint1 ci, uint1& co)
{
    uint33_t aa = (uint32_t)a;
    uint33_t bb = (uint32_t)b;
    uint33_t rr = aa + bb + ci;
    co = rr[32];
    return rr[31:0];
}

w32 subx(w32 a, w32 b, uint1 ci, uint1& co)
{
    uint33_t aa = (uint32_t)a;
    uint33_t bb = (uint32_t)b;
    uint33_t rr = aa - bb - ci;
    co = rr[32];
    return rr[31:0];
}

w32 band (w32 a, w32 b) { return a &  b; }
w32 bor  (w32 a, w32 b) { return a |  b; }
w32 bxor (w32 a, w32 b) { return a ^ b; }

w32 sge (w32 a, w32 b) { return a >= b; }
w32 sgt (w32 a, w32 b) { return a >  b; }
w32 sle (w32 a, w32 b) { return a <= b; }
w32 slt (w32 a, w32 b) { return a <  b; }
w32 seq (w32 a, w32 b) { return a == b; }
w32 sne (w32 a, w32 b) { return a != b; }

w32 sgeu(w32 a, w32 b) { return (uint32_t)a >= (uint32_t)b; }
w32 sgtu(w32 a, w32 b) { return (uint32_t)a >  (uint32_t)b; }
w32 sleu(w32 a, w32 b) { return (uint32_t)a <= (uint32_t)b; }
w32 sltu(w32 a, w32 b) { return (uint32_t)a <  (uint32_t)b; }

w32 sra (w32 a, w32 b) { return a           >> b[4:0]; }
w32 sll (w32 a, w32 b) { return (uint32_t)a << b[4:0]; }
w32 srl (w32 a, w32 b) { return (uint32_t)a >> b[4:0]; }

w32 xtd (w32 a, w32 b) {
    uint5_t f = 32 - b;
    return (a << f) >> f;
}

w32 mul(w32 a, w32 b)   { return a * b; }

void lmulss(w32 a, w32 b, w32& lo, w32& hi)
{
    int64_t p = a * b;
    lo = p[31:0];
    hi = p[63:32];
}

void lmulsu(w32 a, w32 b, w32& lo, w32& hi)
{
    int64_t p = a * (uint32_t)b;
    lo = p[31:0];
    hi = p[63:32];
}

void lmuluu(w32 a, w32 b, w32& lo, w32& hi)
{
    int64_t p = (uint32_t)a * (uint32_t)b;
    lo = p[31:0];
    hi = p[63:32];
}

w32 clb (w32 a) // count number of identical leading bits
{
    uint6_t r;
    w32 tmp = a < 0 ? ~a : a;
    if      (tmp[31: 0] == 0) r = 32;
    else if (tmp[31: 1] == 0) r = 31;
    else if (tmp[31: 2] == 0) r = 30;
    else if (tmp[31: 3] == 0) r = 29;
    else if (tmp[31: 4] == 0) r = 28;
    else if (tmp[31: 5] == 0) r = 27;
    else if (tmp[31: 6] == 0) r = 26;
    else if (tmp[31: 7] == 0) r = 25;
    else if (tmp[31: 8] == 0) r = 24;
    else if (tmp[31: 9] == 0) r = 23;

    else if (tmp[31:10] == 0) r = 22;
    else if (tmp[31:11] == 0) r = 21;
    else if (tmp[31:12] == 0) r = 20;
    else if (tmp[31:13] == 0) r = 19;
    else if (tmp[31:14] == 0) r = 18;
    else if (tmp[31:15] == 0) r = 17;
    else if (tmp[31:16] == 0) r = 16;
    else if (tmp[31:17] == 0) r = 15;
    else if (tmp[31:18] == 0) r = 14;
    else if (tmp[31:19] == 0) r = 13;

    else if (tmp[31:20] == 0) r = 12;
    else if (tmp[31:21] == 0) r = 11;
    else if (tmp[31:22] == 0) r = 10;
    else if (tmp[31:23] == 0) r =  9;
    else if (tmp[31:24] == 0) r =  8;
    else if (tmp[31:25] == 0) r =  7;
    else if (tmp[31:26] == 0) r =  6;
    else if (tmp[31:27] == 0) r =  5;
    else if (tmp[31:28] == 0) r =  4;
    else if (tmp[31:29] == 0) r =  3;

    else if (tmp[31:30] == 0) r =  2;
    else                      r =  1;

    return r;
}

w32 extend_sign(w08 a) { return a; }
w32 extend_zero(w08 a) { return (uint8_t)a; }
w32 extend_sign(w16 a) { return a; }
w32 extend_zero(w16 a) { return (uint16_t)a; }
w08 extract_w08(w32 a) { return a[7:0]; }
w16 extract_w16(w32 a) { return a[15:0]; }

bool eqz(w32 a) { return a == 0; }
bool nez(w32 a) { return a != 0; }

void nop() { }

w32 pcadd(w32 a, w32 b) { return a + b; }
#if defined(__go__)
addr incr1(addr a) { return a + 1; }
#endif

    uint2 incr(uint2 a) { return a + 1; }

#include "tlx_div.p"
#include "tlx_irq.p"
#if defined(TLX_HAS_ADAPTERS)
wait_state_nop;
#include "tlx_io_dm.p"
#include "tlx_io_pm.p"
#else
// TLX_NI_FAST: No IO Interface
#ifndef TLX_NI_FAST
#include "tlx_io.p"
#endif
#endif

