/*
-- Copyright (c) 2019-2020 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

pc_offset_in_addend
/*This option reduces the number of relocator rules for relative jumps. Instead of creating a new
relocator rule for every jump instruction that has a different chess_pc_offset value, the PC offset
adjustment is put in the addend value.*/


relocate_relative_addresses
/* By default, the compiler will not add relocators for relative offsets that are known at compile time
(like the offset of a relative jump inside a function). In case code changes are still required at linktime,
this option must be enabled. */

// immediate for ALU, used for absolute address loading
0 : ((symbol_addr_AR  + addend ) & 4095)  :  t12s [11..0]@0 in t8u[4]      // with default addend 0

1 : ((symbol_addr_AR  + addend )  >> 12 ) :  t20s_rp12 [19..0]@0 in t8u[4] nostrict      // with default addend 0