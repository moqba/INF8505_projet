/*
-- File : trv32p5.p
--
-- Contents : Definition of the trv32p5 primitives.
--
-- Copyright (c) 2019-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

#include "trv32p5_define.h"

w32 add(w32 a, w32 b) { return a + b; }
w32 sub(w32 a, w32 b) { return a - b; }

w32 slt (w32 a, w32 b) { return a <  b; }
w32 sltu(w32 a, w32 b) { return (uint32_t)a <  (uint32_t)b; }

w32 seq0(w32 a) { return a == 0; }
w32 sne0(w32 a) { return a != 0; }

w32 mul(w32 a, w32 b) { return a * b; }

w32 mulh(w32 a, w32 b) {
  int64_t p = a * b;
  return p[63:32];
}

w32 mulhsu(w32 a, w32 b) {
  int64_t p = a * (uint32_t)b;
  return p[63:32];
}

w32 mulhu(w32 a, w32 b) {
  int64_t p = (uint32_t)a * (uint32_t)b;
  return p[63:32];
}

w32 band (w32 a, w32 b) { return a & b; }
w32 bor  (w32 a, w32 b) { return a | b; }
w32 bxor (w32 a, w32 b) { return a ^ b; }

bool eq  (w32 a, w32 b) { return a == b;  }
bool ne  (w32 a, w32 b) { return a != b;  }
bool lt  (w32 a, w32 b) { return a <  b; }
bool ge  (w32 a, w32 b) { return a >= b; }
bool ltu (w32 a, w32 b) { return (uint32_t)a <  (uint32_t)b; }
bool geu (w32 a, w32 b) { return (uint32_t)a >= (uint32_t)b; }

w32 sra (w32 a, w32 b) { return a           >> b[4:0]; }
w32 sll (w32 a, w32 b) { return (uint32_t)a << b[4:0]; }
w32 srl (w32 a, w32 b) { return (uint32_t)a >> b[4:0]; }

w32 sext(w08 a) { return a; }
w32 zext(w08 a) { return (uint8_t)a; }
w32 sext(w16 a) { return a; }
w32 zext(w16 a) { return (uint16_t)a; }

void nop() { }

#ifdef __go__
addr incr1(addr a) { return a + 1; }
addr incr4(addr a) { return a + 4; }
#endif

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~ RTL optimized

// mode[1] == 1: opa is signed
// mode[0] == 1: opb is signed
void mul_hw(w32 opa, w32 opb, t2u mode, w32 & pl, w32 & ph) {
  int33_t a = (mode[1] & opa[31]) :: opa;
  int33_t b = (mode[0] & opb[31]) :: opb;
  int66_t r = a * b;
  pl = r[31:0];
  ph = r[63:32];
}

#include "div.p"

#ifndef TRV32P5_NO_IO
class v4u8 property (vector u08[4]);
// Comment out to (temporarily) disable the DM/PM IO interfaces e.g. during
// design exploration, when changing the memory width.
// If DMb/PMb nML memories are large (> 2**31 bytes), you might need to use
// Go options like 'c_memory_models' or 'mem_size' for HDL generation (see Go
// options file).

// NOTE During ISA exploration, we recommend to disable the IO interfaces until
// your ISA/uArch is stable, then decide if you need them.
#include "dm.p"
#endif

#include "userext.p"
