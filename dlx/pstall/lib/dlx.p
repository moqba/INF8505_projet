/*
-- File : dlx.p
--
-- Contents : Definition of the DLX primitives.
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

w32 band(w32 a, w32 b) { return a &  b; }
w32 bor (w32 a, w32 b) { return a |  b; }
w32 bxor(w32 a, w32 b) { return a ^  b; }

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

#include "clb.p"
w32 clb(w32 a) {
  w32 tmp = a < 0 ? ~a : a;
  return clb32_hier(tmp);
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





#if defined(__go__)
addr incr1(addr a) { return a + 1; }
addr incr4(addr a) { return a + 4; }
#endif




#include "dlx_div.p"


// DLX_NI: No IO Interface
#ifndef DLX_NI
#include "dlx_io.p"
#endif

