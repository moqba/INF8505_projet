/*
-- File : dlx_rewrite.h
--
-- Contents : Chess rewrite rules for the DLX processor.
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model 
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

#endif /* _dlx_rewrite_h */

