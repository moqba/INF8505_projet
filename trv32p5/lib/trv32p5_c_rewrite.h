/*
-- File : trv32p5_c_rewrite.h
--
-- Contents : Rewrite rules for the trv32p5 processor.
--
-- Copyright (c) 2019-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

#ifndef INCLUDED_TRV32P5_C_REWRITE_H_
#define INCLUDED_TRV32P5_C_REWRITE_H_

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ Set-Compare Rewrite Rules
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ Signed 32b Arguments

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
// ~~~ Unsigned 32b Arguments

// signed <> unsigned is nil
// unordered compares (== !=) ignore signedness

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
// ~~~ Set-Compare Simplifications

// For some special cases, replace two-instruction set-compare functions with
// simpler single-instruction versions, for example if one of the operands
// is a constant that fits into the signed 12-bit value range of the immediate
// argument of the slti[u] instructions.

// Assumption: all set-compare intrinsics except for sne/seq are inlined and
// use slt(..), hence we rewrite only slt(..).

// sle(a,imm) = 1 ^ (imm < a) where (imm+1) fits into signed 12-bit immediate
// rewrite as --> slt(a,imm+1)
chess_rewrite   signed int slei_to_slti_inc_s32_rule(  signed int a,   signed int b) chess_manifest(chess_const(a) && -2049 <= a && a < 2047) { return 1 ^ slt(a,b); } -> { return slt(b,a+1); }
chess_rewrite   signed int slei_to_slti_inc_u32_rule(unsigned int a, unsigned int b) chess_manifest(chess_const(a) &&               a < 2047) { return 1 ^ slt(a,b); } -> { return slt(b,a+1); }

// slt instruction formats: reg-reg, reg-imm
// Rewrite slt(imm,reg) to !slt(reg,imm+1) if (imm+1) fits into 12-bit signed
// Unless imm==0, which we obtain from reading x0
chess_rewrite   signed int slt_immreg_s32_rule(  signed int a,   signed int b) chess_manifest(chess_const(a) && -2049 <= a && a < 2047 && a != 0) { return slt(a,b); } -> { return 1 ^ slt(b,a+1); }
chess_rewrite   signed int slt_immreg_u32_rule(unsigned int a, unsigned int b) chess_manifest(chess_const(a) &&               a < 2047 && a != 0) { return slt(a,b); } -> { return 1 ^ slt(b,a+1); }

// The above rewrite rules might introduce redundant xor1 operations.
chess_rewrite   signed int slt_xor1_xor1_s32_rule(  signed int a,   signed int b) { return slt(a,b) ^ 1 ^ 1; } -> { return slt(a,b); }
chess_rewrite   signed int slt_xor1_xor1_u32_rule(unsigned int a, unsigned int b) { return slt(a,b) ^ 1 ^ 1; } -> { return slt(a,b); }


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ mul+mulh[u] rules
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Upcast ([u]int64)(int32) of operands bundled with multiplication
// Only needed for signed operands that require sign extension.

chess_rewrite   signed long long lmul_s_rule (  signed int a,   signed int b) { return (  signed long long)a * (  signed long long)b; } -> { return lmul(a,b); }
chess_rewrite   signed long long lmul_u_rule (  signed int a,   signed int b) { return (unsigned long long)a * (unsigned long long)b; } -> { return lmul(a,b); }


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ Mask If Less Than Zero Rules
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

chess_rewrite   signed int s32_mask_if_lt0_rule(  signed int a) { return (a < 0) ? -1 : 0; } -> { return a >> 31; }


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ Division-by-Constant Rules
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

chess_rewrite   signed int divide_by_ct(  signed int x, const   signed int d) chess_const(d) { return x / d; } -> { return sdiv_by_ct1(x,d); }

chess_rewrite unsigned int divide_by_ct(unsigned int x, const unsigned int d) chess_const(d) { return x / d; } -> { return udiv_by_ct1(x,d); }

#endif // INCLUDED_TRV32P5_C_REWRITE_H_
