/*
-- File : trv32p3_rewrite.h
--
-- Contents : Rewrite rules for the trv32p3 processor.
--
-- Copyright (c) 2019-2020 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

#ifndef INCLUDED_TRV32P3_REWRITE_H_
#define INCLUDED_TRV32P3_REWRITE_H_

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ set-compare rewrite rules
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ Signed 32b arguments

chess_rewrite   signed int slt32_sss_rule_10(  signed int a,   signed int b) { return (a <  b) ? 1 : 0; } -> { return slt (a,b); }
chess_rewrite   signed int sgt32_sss_rule_10(  signed int a,   signed int b) { return (a >  b) ? 1 : 0; } -> { return sgt (a,b); }
chess_rewrite   signed int sle32_sss_rule_10(  signed int a,   signed int b) { return (a <= b) ? 1 : 0; } -> { return sle (a,b); }
chess_rewrite   signed int sge32_sss_rule_10(  signed int a,   signed int b) { return (a >= b) ? 1 : 0; } -> { return sge (a,b); }
chess_rewrite   signed int seq32_sss_rule_10(  signed int a,   signed int b) { return (a == b) ? 1 : 0; } -> { return seq (a,b); }
chess_rewrite   signed int sne32_sss_rule_10(  signed int a,   signed int b) { return (a != b) ? 1 : 0; } -> { return sne (a,b); }

chess_rewrite   signed int slt32_sss_rule_01(  signed int a,   signed int b) { return (a <  b) ? 0 : 1; } -> { return sge (a,b); }
chess_rewrite   signed int sgt32_sss_rule_01(  signed int a,   signed int b) { return (a >  b) ? 0 : 1; } -> { return sle (a,b); }
chess_rewrite   signed int set32_sss_rule_01(  signed int a,   signed int b) { return (a <= b) ? 0 : 1; } -> { return sgt (a,b); }
chess_rewrite   signed int sge32_sss_rule_01(  signed int a,   signed int b) { return (a >= b) ? 0 : 1; } -> { return slt (a,b); }
chess_rewrite   signed int seq32_sss_rule_01(  signed int a,   signed int b) { return (a == b) ? 0 : 1; } -> { return sne (a,b); }
chess_rewrite   signed int sne32_sss_rule_01(  signed int a,   signed int b) { return (a != b) ? 0 : 1; } -> { return seq (a,b); }

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ Unsigned 32b arguments

chess_rewrite   signed int slt32_suu_rule_10(unsigned int a, unsigned int b) { return (a <  b) ? 1 : 0; } -> { return slt (a,b); }
chess_rewrite   signed int sgt32_suu_rule_10(unsigned int a, unsigned int b) { return (a >  b) ? 1 : 0; } -> { return sgt (a,b); }
chess_rewrite   signed int sle32_suu_rule_10(unsigned int a, unsigned int b) { return (a <= b) ? 1 : 0; } -> { return sle (a,b); }
chess_rewrite   signed int sge32_suu_rule_10(unsigned int a, unsigned int b) { return (a >= b) ? 1 : 0; } -> { return sge (a,b); }
chess_rewrite   signed int seq32_suu_rule_10(unsigned int a, unsigned int b) { return (a == b) ? 1 : 0; } -> { return seq ((  signed int)a,(  signed int)b); }
chess_rewrite   signed int sne32_suu_rule_10(unsigned int a, unsigned int b) { return (a != b) ? 1 : 0; } -> { return sne ((  signed int)a,(  signed int)b); }

chess_rewrite   signed int slt32_suu_rule_01(unsigned int a, unsigned int b) { return (a <  b) ? 0 : 1; } -> { return sge (a,b); }
chess_rewrite   signed int sgt32_suu_rule_01(unsigned int a, unsigned int b) { return (a >  b) ? 0 : 1; } -> { return sle (a,b); }
chess_rewrite   signed int set32_suu_rule_01(unsigned int a, unsigned int b) { return (a <= b) ? 0 : 1; } -> { return sgt (a,b); }
chess_rewrite   signed int sge32_suu_rule_01(unsigned int a, unsigned int b) { return (a >= b) ? 0 : 1; } -> { return slt (a,b); }
chess_rewrite   signed int seq32_suu_rule_01(unsigned int a, unsigned int b) { return (a == b) ? 0 : 1; } -> { return sne ((  signed int)a,(  signed int)b); }
chess_rewrite   signed int sne32_suu_rule_01(unsigned int a, unsigned int b) { return (a != b) ? 0 : 1; } -> { return seq ((  signed int)a,(  signed int)b); }

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ set-equal-zero simplifications
//
// seq, sne use two instructions, replace with single instructions seqz, snez
// for special case that one operand is zero

chess_rewrite   signed int seq0_s32_sss_rule(  signed int a,   signed int b) chess_manifest(b == 0) { return seq(a,b); } -> { return seq0(a); }
chess_rewrite   signed int sne0_s32_sss_rule(  signed int a,   signed int b) chess_manifest(b == 0) { return sne(a,b); } -> { return sne0(a); }

#endif // INCLUDED_TRV32P3_REWRITE_H_
