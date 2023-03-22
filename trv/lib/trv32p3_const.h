/*
-- File : trv32p3_const.h
--
-- Contents : Constant generation for the trv32p3 core.
--
-- Copyright (c) 2019-2020 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

#ifndef INCLUDED_TRV32P3_CONST_H_
#define INCLUDED_TRV32P3_CONST_H_

namespace trv32p3_primitive {
  inline void chess_convert(t20s_rp12 msb, t12u lsb, w32& L) property(big_endian)
  {
    // two-instructions sequence to generate 32b constants
    // lui  ra, imm[31:12]
    // oriu ra, ra, imm[11:0]
    // NOTE: uses bit-or instruction with unsigned immediate (custom extension)
    L = bor((w32)msb,lsb);
  }
};

chess_properties {
  convert_routing_const w32 : X;
}

#endif /* INCLUDED_TRV32P3_CONST_H_ */
