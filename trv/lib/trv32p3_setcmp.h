/*
-- File : trv32p3_setcmp.h
--
-- Contents : Set-compare intrinsics for the trv32p3 processor.
--
-- Copyright (c) 2019-2020 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

#ifndef INCLUDED_TRV32P3_SETCMP_H_
#define INCLUDED_TRV32P3_SETCMP_H_

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ set-compare intrinsics
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// signed <> unsigned is nil (signed int <> unsigned int)
// set-cmp functions return [0,1] = fits in signed int, where signed int<>unsigned int is nil

// ordered (< > <= >=): signed int, unsigned int variants
// unordered (== !=): signed int variant (sub)

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ map set-less-than(-unsigned) instructions

promotion    signed int  slt (  signed int,  signed int) = w32 slt  (w32,w32);
promotion    signed int  slt (unsigned int,unsigned int) = w32 sltu (w32,w32);

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ map set(-not)-equal-zero chess_views

promotion    signed int  seq0 (  signed int)             = w32 seq0 (w32);
promotion    signed int  sne0 (  signed int)             = w32 sne0 (w32);

chess_properties {
  complements: w32 seq0 (w32), w32 sne0 (w32);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ 2-operand variants: use 2 instructions

namespace trv32p3_primitive {
  inline  w32  sge  (w32 a, w32 b) { return seq0 (slt  (a,b)); }
  inline  w32  sle  (w32 a, w32 b) { return seq0 (slt  (b,a)); }
  inline  w32  sgeu (w32 a, w32 b) { return seq0 (sltu (a,b)); }
  inline  w32  sleu (w32 a, w32 b) { return seq0 (sltu (b,a)); }
  inline  w32  sgt  (w32 a, w32 b) { return slt  (b,a); }
  inline  w32  sgtu (w32 a, w32 b) { return sltu (b,a); }
}

chess_properties {
  complements: w32 slt  (w32,w32), w32 sge  (w32,w32);
  complements: w32 sltu (w32,w32), w32 sgeu (w32,w32);
  complements: w32 sgt  (w32,w32), w32 sle  (w32,w32);
  complements: w32 sgtu (w32,w32), w32 sleu (w32,w32);
}

promotion    signed int  sge  (  signed int,  signed int) = w32 sge  (w32,w32);
promotion    signed int  sle  (  signed int,  signed int) = w32 sle  (w32,w32);
promotion    signed int  sgt  (  signed int,  signed int) = w32 sgt  (w32,w32);
promotion    signed int  sge  (unsigned int,unsigned int) = w32 sgeu (w32,w32);
promotion    signed int  sle  (unsigned int,unsigned int) = w32 sleu (w32,w32);
promotion    signed int  sgt  (unsigned int,unsigned int) = w32 sgtu (w32,w32);

inline       signed int  sne  (  signed int a,   signed int b) { return sne0(a-b);  }
inline       signed int  seq  (  signed int a,   signed int b) { return seq0(a-b);  }

#endif // INCLUDED_TRV32P3_SETCMP_H_
