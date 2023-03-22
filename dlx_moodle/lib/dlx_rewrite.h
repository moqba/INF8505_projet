/*
-- File : dlx_rewrite.h
--
-- Contents : Chess rewrite rules for the DLX processor.
--
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/




#ifndef _dlx_rewrite_h
#define _dlx_rewrite_h

chess_rewrite bool eqz_rule(int a) { return a == 0; } -> { return eqz(a); }
chess_rewrite bool nez_rule(int a) { return a != 0; } -> { return nez(a); }
chess_rewrite bool eqz_rule(unsigned a) { return a == 0; } -> { return eqz(a); }
chess_rewrite bool nez_rule(unsigned a) { return a != 0; } -> { return nez(a); }
chess_rewrite bool eqz_rule(void* a) { return a == 0; } -> { return eqz(a); }
chess_rewrite bool nez_rule(void* a) { return a != 0; } -> { return nez(a); }

chess_rewrite bool eqz_0_rule(int a) chess_manifest(a == 0) { return eqz(a); } -> { return true; }
chess_rewrite bool eqz_1_rule(int a) chess_manifest(a != 0) { return eqz(a); } -> { return false; }
chess_rewrite bool nez_0_rule(int a) chess_manifest(a == 0) { return nez(a); } -> { return false; }
chess_rewrite bool nez_1_rule(int a) chess_manifest(a != 0) { return nez(a); } -> { return true; }
chess_rewrite bool eqz_0_rule(unsigned a) chess_manifest(a == 0) { return eqz(a); } -> { return true; }
chess_rewrite bool eqz_1_rule(unsigned a) chess_manifest(a != 0) { return eqz(a); } -> { return false; }
chess_rewrite bool nez_0_rule(unsigned a) chess_manifest(a == 0) { return nez(a); } -> { return false; }
chess_rewrite bool nez_1_rule(unsigned a) chess_manifest(a != 0) { return nez(a); } -> { return true; }
chess_rewrite bool eqz_0_rule(void* a) chess_manifest(a == 0) { return eqz(a); } -> { return true; }
chess_rewrite bool eqz_1_rule(void* a) chess_manifest(a != 0) { return eqz(a); } -> { return false; }
chess_rewrite bool nez_0_rule(void* a) chess_manifest(a == 0) { return nez(a); } -> { return false; }
chess_rewrite bool nez_1_rule(void* a) chess_manifest(a != 0) { return nez(a); } -> { return true; }

chess_rewrite bool land_rule(bool a, bool b) { return a && b; } -> { return land(a,b); }

chess_rewrite bool land_0x_rule(bool b) { return land(false,b); } -> { return false; }
chess_rewrite bool land_x0_rule(bool a) { return land(a,false); } -> { return false; }
chess_rewrite bool land_11_rule() { return land(true,true); } -> { return true; }

chess_rewrite bool lor_rule(bool a, bool b) { return a || b; } -> { return lor(a,b); }

chess_rewrite bool lor_1x_rule(bool b) { return lor(true,b); } -> { return true; }
chess_rewrite bool lor_x1_rule(bool a) { return lor(a,true); } -> { return true; }
chess_rewrite bool lor_00_rule() { return lor(false,false); } -> { return false; }

chess_rewrite int bool_as_int_rule(bool a)
    { return a ? 1 : 0; } -> { return a; }

// For a manifest b, two shifts are replaced by a single sign_extend
// For a non-manifest b, first a subtraction from 32 is generated.  This can be avoided by adding the chess_const(b) predicates.
chess_rewrite int sign_extend_rule(int a, int b) //chess_const(b)
    { return a << b >> b; } -> { return sign_extend(a,32-b); }
chess_rewrite int sign_extend_rule(unsigned a, int b) //chess_const(b)
    { return (int)(a << b) >> b; } -> { return sign_extend(a,32-b); }

//-- this section is LLVM specific --
// LLVM will always generate shift-pairs for narrowing sinteger conversions (e.g. short(int)).
// Unfortunately, the internal representation is odd, requiring dedicated rewrite rules to match (pending better tool support).
chess_rewrite int sign_extend_ruleu(unsigned a, unsigned bu, int b) chess_manifest(bu == b) //llvm
    { return (int)(a << bu) >> b; } -> { return sign_extend(a,32-b); }

//NOTE
// On cores with, e.g., just a 16 bit specific instruction, the following can be used.  Note the distinct constants 16u and 16.
//chess_rewrite int sign_extend_rule(int a, int b)
//    { return a << 16 >> 16; } -> { return sign_extend16(a); }
//chess_rewrite int sign_extend_ruleu(unsigned a) //llvm
//    { return (int)(a << 16u) >> 16; } -> { return sign_extend16(a); }
//
// Also llvm tends to redistribute constant addition over the shift pair, e.g.,
//chess_rewrite int sign_extend_ruleu_add1(unsigned a) //llvm
//    { return (int)((a << 16u) + 0x10000u) >> 16; } -> { return sign_extend16(a+1); }

// On dlx, the 8 and 16 bit versions are special in that they can be either standalone or part of a memory path.
// However the generic sign_extend with a factor argument can only be done standalone.
// Reintroducing a conversion goes full circle (like when not using llvm) so that the chess_views also map.
// Actually these rules are valid in the non-llvm flow too, but whereas llvm will always produce such code, non-llvm only when explicitly written as such.
chess_rewrite int sign_extend08_rule(int a)
    { return sign_extend(a, 8); } -> { return (signed char)(a); }
chess_rewrite int sign_extend16_rule(int a)
    { return sign_extend(a,16); } -> { return (signed short)(a); }
chess_rewrite int zero_extend08_rule(int a)
    { return a & 0xffu;         } -> { return (unsigned char)(a); }
chess_rewrite int zero_extend16_rule(int a)
    { return a & 0xffffu;       } -> { return (unsigned short)(a); }

//-- end LLVM specific --

#endif /* _dlx_rewrite_h */
