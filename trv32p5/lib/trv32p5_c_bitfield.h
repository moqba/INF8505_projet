/*
-- File : trv32p5_c_bitfield.h
--
-- Contents : Software bitfield extraction rules for the trv32p5 processor.
--
-- Copyright (c) 2019-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

#ifndef INCLUDED_TRV32P5_C_BITFIELD_H_
#define INCLUDED_TRV32P5_C_BITFIELD_H_

inline int chess_bitfield_extract_signed(int W, int width, int lsb) property(dont_generate) {
  int V = W << (chess_bitsof(int) - (width + lsb));
  return V >> (chess_bitsof(int) - width);
}

inline unsigned chess_bitfield_extract_unsigned(int W, int width, int lsb) property(dont_generate) {
  unsigned V = W << (chess_bitsof(int) - (width + lsb));
  return V >> (chess_bitsof(int) - width);
}

inline int chess_bitfield_update(int W, int f, int width, int lsb) property(dont_generate) {
  unsigned ones = -1;
  unsigned mask1 = (ones << (width + lsb)) | ~(ones << lsb);
  unsigned mask2 = ~(ones << width);
  return W & mask1 | ((f & mask2) << lsb);
}

#endif /* INCLUDED_TRV32P5_C_BITFIELD_H_ */
