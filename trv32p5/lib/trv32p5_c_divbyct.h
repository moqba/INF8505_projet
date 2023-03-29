/*
-- File : trv32p5_c_divbyct.h
--
-- Contents : Division by constant
--
-- Copyright (c) 2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

#ifndef INCLUDED_TRV32P5_C_DIVBYCT_H_
#define INCLUDED_TRV32P5_C_DIVBYCT_H_

// NOTE There are multiple implementation patterns for integer divisions by a
// constant. The choice is ISA specific. Please check the Chess Compiler
// Modeling manual for more details (Section 'Integer Division by a Constant').

promotion void signed_div_magic(int d, int& m, int& s, bool& addsub) property(dont_generate)
    property(signed_div_magic) = undefined;
promotion void unsigned_div_magic(unsigned d, unsigned& m, int& s, bool& add) property(dont_generate)
    property(unsigned_div_magic) = undefined;

// signed division
inline int sdiv_by_ct1(int x, const int d) property(dont_generate) {
  int m; int s; bool add;
  signed_div_magic(d, m, s, add);

  int q = mulh(x, m);
  if (add) q += d < 0 ? -x : x;
  q >>= s;    // post shift
  int t = (d < 0 ? q : x) < 0;
  return q + t;
}

// unsigned division
inline unsigned udiv_by_ct1(unsigned x, const unsigned d) property(dont_generate) {
  unsigned m; int s; bool add;
  unsigned_div_magic(d, m, s, add);

  unsigned q = mulh(x,m);
  if (add) {
    q += (x - q) >> 1;
    return q >> (s - 1);
  } else {
    return q >> s;
  }
}

#endif /* INCLUDED_TRV32P5_C_DIVBYCT_H_ */
