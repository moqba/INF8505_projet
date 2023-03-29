/*
-- File : trv32p5_iapcu.h
--
-- Contents : PCU model for Instruction Accurate ISS
--
-- Copyright (c) 2019-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

#ifndef INCLUDE_TRV32P5_IAPCU_H_
#define INCLUDE_TRV32P5_IAPCU_H_

#include "checkers_declspec.h"
#include "checkers_enum.h"
#include "Mdl_trv32p5.h"

// This functions is called at the end of simulating an instruction and
// must set the program counter to the value for the next step. It has the
// following signature:
//
// inline void <processor>_user_next_pc(<processor>* mdl, AddressType next_pc,
//                                      unsigned nw,
//                                      Checkers_next_pc_type npt);
//
// 'mdl' is a pointer to the processor model. 'next_pc' is the next program
// counter value as calculated during simulation of the current
// instruction. 'nw' is the number of words of the instruction being
// executed. 'npt' is an enum indicating how the 'next_pc' value was
// calculated. Possible values are:
//
// npt_increment : 'next_pc' is the address of the next instruction on the
//     increment path.
//
// npt_jump : 'next_pc' is the target address of a (un)conditional
//     jump. For conditional jumps this can be the actual target address or
//     the address of the next instruction on the increment path.
//
// npt_call : 'next_pc' is the target address of a (un)conditional
//     call. For conditional calls this can be the actual target address or
//     the address of the next instruction on the increment path.
//
// npt_loop_end : 'next_pc' is the result of the 'end-of-loop' functions
//     and can be address of the first instruction in the loop or of the
//     first instruction after the loop.
//
// npt_cntrl : 'next_pc' is the result of another controller instruction
//     (type 4 above).
//
// npt_delay_slot : 'next_pc' is the address of the next instruction in the
//     delay slots of an instruction. 'npt' is set to 'npt_delay_slot' for
//     all but the last delay-slot instruction. For this last delay-slot
//     instruction 'npt' is set according to the type of the instruction
//     having the delay slots. (e.g. to npt_jump for a jump with delay
//     slots).

inline void trv32p5_user_next_pc(trv32p5* mdl, AddressType next_pc, unsigned nw, Checkers_next_pc_type npt)
{
  /* User code here */
  next_pc &= ~1; // mask LSB, as per RISC-V spec
  mdl->PC = next_pc;

  // PC_{stage} registers hold address of instruction in {stage}
  // IA-ISS has no stages, hence use the same value
  mdl->PC_ID = next_pc;
  mdl->PC_EX = next_pc;
}

#endif // INCLUDE_TRV32P5_IAPCU_H_
