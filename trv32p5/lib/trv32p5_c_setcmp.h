/*
-- File : trv32p5_c_setcmp.h
--
-- Contents : Set-compare intrinsics for the trv32p5 processor.
--
-- Copyright (c) 2019-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

#ifndef INCLUDED_TRV32P5_C_SETCMP_H_
#define INCLUDED_TRV32P5_C_SETCMP_H_

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ Set-Compare Intrinsics
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// signed <> unsigned is nil (signed int <> unsigned int)
// set-cmp functions return [0,1] = fits in signed int, where signed int<>unsigned int is nil

// ordered (< > <= >=) : signed int, unsigned int variants
// unordered (== !=)   : signed int variant (sub)

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ map set-less-than(-unsigned) instructions

promotion    signed int  slt (  signed int,  signed int) = w32 slt  (w32,w32);
promotion    signed int  slt (unsigned int,unsigned int) = w32 sltu (w32,w32);

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ map set(-not)-equal-zero chess_views

promotion    signed int  seq0 (  signed int) = w32 seq0 (w32);
promotion    signed int  sne0 (  signed int) = w32 sne0 (w32);

chess_properties {
  complements: w32 seq0 (w32), w32 sne0 (w32);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ 2-operand Variants: use 2 instructions

// Assumption: slt(..) return value is 0 or 1
// Then XOR-ing with '1' is a logical not.

inline       signed int  sle  (  signed int a,   signed int b) { return slt(b,a) ^ 1; }
inline       signed int  sle  (unsigned int a, unsigned int b) { return slt(b,a) ^ 1; }

inline       signed int  sge  (  signed int a,   signed int b) { return slt(a,b) ^ 1; }
inline       signed int  sge  (unsigned int a, unsigned int b) { return slt(a,b) ^ 1; }

inline       signed int  sgt  (  signed int a,   signed int b) { return slt(b,a); }
inline       signed int  sgt  (unsigned int a, unsigned int b) { return slt(b,a); }

inline       signed int  sne  (  signed int a,   signed int b) { return sne0(a-b); }
inline       signed int  seq  (  signed int a,   signed int b) { return seq0(a-b); }

#endif // INCLUDED_TRV32P5_C_SETCMP_H_
