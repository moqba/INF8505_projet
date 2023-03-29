/*
-- Test conversion expressions.
--
-- Copyright (c) 2014 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

#include "regression.h"

// These #defines must be set externally (via always include or -D command line arguments)
//
// #define HAS_CHAR
// #define HAS_SHORT
// #define HAS_INT
// #define HAS_LONG
// #define HAS_LONG_LONG
// #define CHAR_NBIT       8

#include <limits.h>

#define NOINLINE [[gnu::noinline]]

typedef   signed char           sc;
typedef unsigned char           uc;
typedef   signed short          ss;
typedef unsigned short          us;
typedef   signed int            si;
typedef unsigned int            ui;
typedef   signed long           sl;
typedef unsigned long           ul;
typedef   signed long long      sll;
typedef unsigned long long      ull;

NOINLINE sc  cast_sc_reg_sc_reg (sc a)   { sc  b = a; return b; }
NOINLINE uc  cast_uc_reg_sc_reg (sc a)   { uc  b = a; return b; }
NOINLINE ss  cast_ss_reg_sc_reg (sc a)   { ss  b = a; return b; }
NOINLINE us  cast_us_reg_sc_reg (sc a)   { us  b = a; return b; }
NOINLINE si  cast_si_reg_sc_reg (sc a)   { si  b = a; return b; }
NOINLINE ui  cast_ui_reg_sc_reg (sc a)   { ui  b = a; return b; }
NOINLINE sl  cast_sl_reg_sc_reg (sc a)   { sl  b = a; return b; }
NOINLINE ul  cast_ul_reg_sc_reg (sc a)   { ul  b = a; return b; }
NOINLINE sll cast_sll_reg_sc_reg(sc a)   { sll b = a; return b; }
NOINLINE ull cast_ull_reg_sc_reg(sc a)   { ull b = a; return b; }

NOINLINE void cast_sc_mem_sc_reg (sc a, sc * b)   { *b = a; }
NOINLINE void cast_uc_mem_sc_reg (sc a, uc * b)   { *b = a; }
NOINLINE void cast_ss_mem_sc_reg (sc a, ss * b)   { *b = a; }
NOINLINE void cast_us_mem_sc_reg (sc a, us * b)   { *b = a; }
NOINLINE void cast_si_mem_sc_reg (sc a, si * b)   { *b = a; }
NOINLINE void cast_ui_mem_sc_reg (sc a, ui * b)   { *b = a; }
NOINLINE void cast_sl_mem_sc_reg (sc a, sl * b)   { *b = a; }
NOINLINE void cast_ul_mem_sc_reg (sc a, ul * b)   { *b = a; }
NOINLINE void cast_sll_mem_sc_reg(sc a, sll * b)  { *b = a; }
NOINLINE void cast_ull_mem_sc_reg(sc a, ull * b)  { *b = a; }

NOINLINE sc  cast_sc_reg_sc_mem (sc * a) { sc  b = *a; return b; }
NOINLINE uc  cast_uc_reg_sc_mem (sc * a) { uc  b = *a; return b; }
NOINLINE ss  cast_ss_reg_sc_mem (sc * a) { ss  b = *a; return b; }
NOINLINE us  cast_us_reg_sc_mem (sc * a) { us  b = *a; return b; }
NOINLINE si  cast_si_reg_sc_mem (sc * a) { si  b = *a; return b; }
NOINLINE ui  cast_ui_reg_sc_mem (sc * a) { ui  b = *a; return b; }
NOINLINE sl  cast_sl_reg_sc_mem (sc * a) { sl  b = *a; return b; }
NOINLINE ul  cast_ul_reg_sc_mem (sc * a) { ul  b = *a; return b; }
NOINLINE sll cast_sll_reg_sc_mem(sc * a) { sll b = *a; return b; }
NOINLINE ull cast_ull_reg_sc_mem(sc * a) { ull b = *a; return b; }


NOINLINE sc  cast_sc_reg_uc_reg (uc a)   { sc  b = a; return b; }
NOINLINE uc  cast_uc_reg_uc_reg (uc a)   { uc  b = a; return b; }
NOINLINE ss  cast_ss_reg_uc_reg (uc a)   { ss  b = a; return b; }
NOINLINE us  cast_us_reg_uc_reg (uc a)   { us  b = a; return b; }
NOINLINE si  cast_si_reg_uc_reg (uc a)   { si  b = a; return b; }
NOINLINE ui  cast_ui_reg_uc_reg (uc a)   { ui  b = a; return b; }
NOINLINE sl  cast_sl_reg_uc_reg (uc a)   { sl  b = a; return b; }
NOINLINE ul  cast_ul_reg_uc_reg (uc a)   { ul  b = a; return b; }
NOINLINE sll cast_sll_reg_uc_reg(uc a)   { sll b = a; return b; }
NOINLINE ull cast_ull_reg_uc_reg(uc a)   { ull b = a; return b; }

NOINLINE void cast_sc_mem_uc_reg (uc a, sc * b)   { *b = a; }
NOINLINE void cast_uc_mem_uc_reg (uc a, uc * b)   { *b = a; }
NOINLINE void cast_ss_mem_uc_reg (uc a, ss * b)   { *b = a; }
NOINLINE void cast_us_mem_uc_reg (uc a, us * b)   { *b = a; }
NOINLINE void cast_si_mem_uc_reg (uc a, si * b)   { *b = a; }
NOINLINE void cast_ui_mem_uc_reg (uc a, ui * b)   { *b = a; }
NOINLINE void cast_sl_mem_uc_reg (uc a, sl * b)   { *b = a; }
NOINLINE void cast_ul_mem_uc_reg (uc a, ul * b)   { *b = a; }
NOINLINE void cast_sll_mem_uc_reg (uc a, sll * b) { *b = a; }
NOINLINE void cast_ull_mem_uc_reg (uc a, ull * b) { *b = a; }

NOINLINE sc  cast_sc_reg_uc_mem (uc * a) { sc  b = *a; return b; }
NOINLINE uc  cast_uc_reg_uc_mem (uc * a) { uc  b = *a; return b; }
NOINLINE ss  cast_ss_reg_uc_mem (uc * a) { ss  b = *a; return b; }
NOINLINE us  cast_us_reg_uc_mem (uc * a) { us  b = *a; return b; }
NOINLINE si  cast_si_reg_uc_mem (uc * a) { si  b = *a; return b; }
NOINLINE ui  cast_ui_reg_uc_mem (uc * a) { ui  b = *a; return b; }
NOINLINE sl  cast_sl_reg_uc_mem (uc * a) { sl  b = *a; return b; }
NOINLINE ul  cast_ul_reg_uc_mem (uc * a) { ul  b = *a; return b; }
NOINLINE sll cast_sll_reg_uc_mem(uc * a) { sll b = *a; return b; }
NOINLINE ull cast_ull_reg_uc_mem(uc * a) { ull b = *a; return b; }



NOINLINE sc  cast_sc_reg_ss_reg (ss a)   { sc  b = a; return b; }
NOINLINE uc  cast_uc_reg_ss_reg (ss a)   { uc  b = a; return b; }
NOINLINE ss  cast_ss_reg_ss_reg (ss a)   { ss  b = a; return b; }
NOINLINE us  cast_us_reg_ss_reg (ss a)   { us  b = a; return b; }
NOINLINE si  cast_si_reg_ss_reg (ss a)   { si  b = a; return b; }
NOINLINE ui  cast_ui_reg_ss_reg (ss a)   { ui  b = a; return b; }
NOINLINE sl  cast_sl_reg_ss_reg (ss a)   { sl  b = a; return b; }
NOINLINE ul  cast_ul_reg_ss_reg (ss a)   { ul  b = a; return b; }
NOINLINE sll cast_sll_reg_ss_reg(ss a)   { sll b = a; return b; }
NOINLINE ull cast_ull_reg_ss_reg(ss a)   { ull b = a; return b; }

NOINLINE void cast_sc_mem_ss_reg (ss a, sc * b)   { *b = a; }
NOINLINE void cast_uc_mem_ss_reg (ss a, uc * b)   { *b = a; }
NOINLINE void cast_ss_mem_ss_reg (ss a, ss * b)   { *b = a; }
NOINLINE void cast_us_mem_ss_reg (ss a, us * b)   { *b = a; }
NOINLINE void cast_si_mem_ss_reg (ss a, si * b)   { *b = a; }
NOINLINE void cast_ui_mem_ss_reg (ss a, ui * b)   { *b = a; }
NOINLINE void cast_sl_mem_ss_reg (ss a, sl * b)   { *b = a; }
NOINLINE void cast_ul_mem_ss_reg (ss a, ul * b)   { *b = a; }
NOINLINE void cast_sll_mem_ss_reg (ss a, sll * b) { *b = a; }
NOINLINE void cast_ull_mem_ss_reg (ss a, ull * b) { *b = a; }

NOINLINE sc  cast_sc_reg_ss_mem (ss * a) { sc  b = *a; return b; }
NOINLINE uc  cast_uc_reg_ss_mem (ss * a) { uc  b = *a; return b; }
NOINLINE ss  cast_ss_reg_ss_mem (ss * a) { ss  b = *a; return b; }
NOINLINE us  cast_us_reg_ss_mem (ss * a) { us  b = *a; return b; }
NOINLINE si  cast_si_reg_ss_mem (ss * a) { si  b = *a; return b; }
NOINLINE ui  cast_ui_reg_ss_mem (ss * a) { ui  b = *a; return b; }
NOINLINE sl  cast_sl_reg_ss_mem (ss * a) { sl  b = *a; return b; }
NOINLINE ul  cast_ul_reg_ss_mem (ss * a) { ul  b = *a; return b; }
NOINLINE sll cast_sll_reg_ss_mem(ss * a) { sll b = *a; return b; }
NOINLINE ull cast_ull_reg_ss_mem(ss * a) { ull b = *a; return b; }


NOINLINE sc  cast_sc_reg_us_reg (us a)   { sc  b = a; return b; }
NOINLINE uc  cast_uc_reg_us_reg (us a)   { uc  b = a; return b; }
NOINLINE ss  cast_ss_reg_us_reg (us a)   { ss  b = a; return b; }
NOINLINE us  cast_us_reg_us_reg (us a)   { us  b = a; return b; }
NOINLINE si  cast_si_reg_us_reg (us a)   { si  b = a; return b; }
NOINLINE ui  cast_ui_reg_us_reg (us a)   { ui  b = a; return b; }
NOINLINE sl  cast_sl_reg_us_reg (us a)   { sl  b = a; return b; }
NOINLINE ul  cast_ul_reg_us_reg (us a)   { ul  b = a; return b; }
NOINLINE sll cast_sll_reg_us_reg(us a)   { sll b = a; return b; }
NOINLINE ull cast_ull_reg_us_reg(us a)   { ull b = a; return b; }

NOINLINE void cast_sc_mem_us_reg (us a, sc * b)   { *b = a; }
NOINLINE void cast_uc_mem_us_reg (us a, uc * b)   { *b = a; }
NOINLINE void cast_ss_mem_us_reg (us a, ss * b)   { *b = a; }
NOINLINE void cast_us_mem_us_reg (us a, us * b)   { *b = a; }
NOINLINE void cast_si_mem_us_reg (us a, si * b)   { *b = a; }
NOINLINE void cast_ui_mem_us_reg (us a, ui * b)   { *b = a; }
NOINLINE void cast_sl_mem_us_reg (us a, sl * b)   { *b = a; }
NOINLINE void cast_ul_mem_us_reg (us a, ul * b)   { *b = a; }
NOINLINE void cast_sll_mem_us_reg (us a, sll * b) { *b = a; }
NOINLINE void cast_ull_mem_us_reg (us a, ull * b) { *b = a; }

NOINLINE sc  cast_sc_reg_us_mem (us * a) { sc  b = *a; return b; }
NOINLINE uc  cast_uc_reg_us_mem (us * a) { uc  b = *a; return b; }
NOINLINE ss  cast_ss_reg_us_mem (us * a) { ss  b = *a; return b; }
NOINLINE us  cast_us_reg_us_mem (us * a) { us  b = *a; return b; }
NOINLINE si  cast_si_reg_us_mem (us * a) { si  b = *a; return b; }
NOINLINE ui  cast_ui_reg_us_mem (us * a) { ui  b = *a; return b; }
NOINLINE sl  cast_sl_reg_us_mem (us * a) { sl  b = *a; return b; }
NOINLINE ul  cast_ul_reg_us_mem (us * a) { ul  b = *a; return b; }
NOINLINE sll cast_sll_reg_us_mem(us * a) { sll b = *a; return b; }
NOINLINE ull cast_ull_reg_us_mem(us * a) { ull b = *a; return b; }


NOINLINE sc  cast_sc_reg_si_reg (si a)   { sc  b = a; return b; }
NOINLINE uc  cast_uc_reg_si_reg (si a)   { uc  b = a; return b; }
NOINLINE ss  cast_ss_reg_si_reg (si a)   { ss  b = a; return b; }
NOINLINE us  cast_us_reg_si_reg (si a)   { us  b = a; return b; }
NOINLINE si  cast_si_reg_si_reg (si a)   { si  b = a; return b; }
NOINLINE ui  cast_ui_reg_si_reg (si a)   { ui  b = a; return b; }
NOINLINE sl  cast_sl_reg_si_reg (si a)   { sl  b = a; return b; }
NOINLINE ul  cast_ul_reg_si_reg (si a)   { ul  b = a; return b; }
NOINLINE sll cast_sll_reg_si_reg(si a)   { sll b = a; return b; }
NOINLINE ull cast_ull_reg_si_reg(si a)   { ull b = a; return b; }

NOINLINE void cast_sc_mem_si_reg (si a, sc * b)   { *b = a; }
NOINLINE void cast_uc_mem_si_reg (si a, uc * b)   { *b = a; }
NOINLINE void cast_ss_mem_si_reg (si a, ss * b)   { *b = a; }
NOINLINE void cast_us_mem_si_reg (si a, us * b)   { *b = a; }
NOINLINE void cast_si_mem_si_reg (si a, si * b)   { *b = a; }
NOINLINE void cast_ui_mem_si_reg (si a, ui * b)   { *b = a; }
NOINLINE void cast_sl_mem_si_reg (si a, sl * b)   { *b = a; }
NOINLINE void cast_ul_mem_si_reg (si a, ul * b)   { *b = a; }
NOINLINE void cast_sll_mem_si_reg (si a, sll * b) { *b = a; }
NOINLINE void cast_ull_mem_si_reg (si a, ull * b) { *b = a; }

NOINLINE sc  cast_sc_reg_si_mem (si * a) { sc  b = *a; return b; }
NOINLINE uc  cast_uc_reg_si_mem (si * a) { uc  b = *a; return b; }
NOINLINE ss  cast_ss_reg_si_mem (si * a) { ss  b = *a; return b; }
NOINLINE us  cast_us_reg_si_mem (si * a) { us  b = *a; return b; }
NOINLINE si  cast_si_reg_si_mem (si * a) { si  b = *a; return b; }
NOINLINE ui  cast_ui_reg_si_mem (si * a) { ui  b = *a; return b; }
NOINLINE sl  cast_sl_reg_si_mem (si * a) { sl  b = *a; return b; }
NOINLINE ul  cast_ul_reg_si_mem (si * a) { ul  b = *a; return b; }
NOINLINE sll cast_sll_reg_si_mem(si * a) { sll b = *a; return b; }
NOINLINE ull cast_ull_reg_si_mem(si * a) { ull b = *a; return b; }


NOINLINE sc  cast_sc_reg_ui_reg (ui a)   { sc  b = a; return b; }
NOINLINE uc  cast_uc_reg_ui_reg (ui a)   { uc  b = a; return b; }
NOINLINE ss  cast_ss_reg_ui_reg (ui a)   { ss  b = a; return b; }
NOINLINE us  cast_us_reg_ui_reg (ui a)   { us  b = a; return b; }
NOINLINE si  cast_si_reg_ui_reg (ui a)   { si  b = a; return b; }
NOINLINE ui  cast_ui_reg_ui_reg (ui a)   { ui  b = a; return b; }
NOINLINE sl  cast_sl_reg_ui_reg (ui a)   { sl  b = a; return b; }
NOINLINE ul  cast_ul_reg_ui_reg (ui a)   { ul  b = a; return b; }
NOINLINE sll cast_sll_reg_ui_reg(ui a)   { sll b = a; return b; }
NOINLINE ull cast_ull_reg_ui_reg(ui a)   { ull b = a; return b; }

NOINLINE void cast_sc_mem_ui_reg (ui a, sc * b)   { *b = a; }
NOINLINE void cast_uc_mem_ui_reg (ui a, uc * b)   { *b = a; }
NOINLINE void cast_ss_mem_ui_reg (ui a, ss * b)   { *b = a; }
NOINLINE void cast_us_mem_ui_reg (ui a, us * b)   { *b = a; }
NOINLINE void cast_si_mem_ui_reg (ui a, si * b)   { *b = a; }
NOINLINE void cast_ui_mem_ui_reg (ui a, ui * b)   { *b = a; }
NOINLINE void cast_sl_mem_ui_reg (ui a, sl * b)   { *b = a; }
NOINLINE void cast_ul_mem_ui_reg (ui a, ul * b)   { *b = a; }
NOINLINE void cast_sll_mem_ui_reg (ui a, sll * b) { *b = a; }
NOINLINE void cast_ull_mem_ui_reg (ui a, ull * b) { *b = a; }

NOINLINE sc  cast_sc_reg_ui_mem (ui * a) { sc  b = *a; return b; }
NOINLINE uc  cast_uc_reg_ui_mem (ui * a) { uc  b = *a; return b; }
NOINLINE ss  cast_ss_reg_ui_mem (ui * a) { ss  b = *a; return b; }
NOINLINE us  cast_us_reg_ui_mem (ui * a) { us  b = *a; return b; }
NOINLINE si  cast_si_reg_ui_mem (ui * a) { si  b = *a; return b; }
NOINLINE ui  cast_ui_reg_ui_mem (ui * a) { ui  b = *a; return b; }
NOINLINE sl  cast_sl_reg_ui_mem (ui * a) { sl  b = *a; return b; }
NOINLINE ul  cast_ul_reg_ui_mem (ui * a) { ul  b = *a; return b; }
NOINLINE sll cast_sll_reg_ui_mem(ui * a) { sll b = *a; return b; }
NOINLINE ull cast_ull_reg_ui_mem(ui * a) { ull b = *a; return b; }


NOINLINE sc  cast_sc_reg_sl_reg (sl a)   { sc  b = a; return b; }
NOINLINE uc  cast_uc_reg_sl_reg (sl a)   { uc  b = a; return b; }
NOINLINE ss  cast_ss_reg_sl_reg (sl a)   { ss  b = a; return b; }
NOINLINE us  cast_us_reg_sl_reg (sl a)   { us  b = a; return b; }
NOINLINE si  cast_si_reg_sl_reg (sl a)   { si  b = a; return b; }
NOINLINE ui  cast_ui_reg_sl_reg (sl a)   { ui  b = a; return b; }
NOINLINE sl  cast_sl_reg_sl_reg (sl a)   { sl  b = a; return b; }
NOINLINE ul  cast_ul_reg_sl_reg (sl a)   { ul  b = a; return b; }
NOINLINE sll cast_sll_reg_sl_reg(sl a)   { sll b = a; return b; }
NOINLINE ull cast_ull_reg_sl_reg(sl a)   { ull b = a; return b; }

NOINLINE void cast_sc_mem_sl_reg (sl a, sc * b)   { *b = a; }
NOINLINE void cast_uc_mem_sl_reg (sl a, uc * b)   { *b = a; }
NOINLINE void cast_ss_mem_sl_reg (sl a, ss * b)   { *b = a; }
NOINLINE void cast_us_mem_sl_reg (sl a, us * b)   { *b = a; }
NOINLINE void cast_si_mem_sl_reg (sl a, si * b)   { *b = a; }
NOINLINE void cast_ui_mem_sl_reg (sl a, ui * b)   { *b = a; }
NOINLINE void cast_sl_mem_sl_reg (sl a, sl * b)   { *b = a; }
NOINLINE void cast_ul_mem_sl_reg (sl a, ul * b)   { *b = a; }
NOINLINE void cast_sll_mem_sl_reg (sl a, sll * b) { *b = a; }
NOINLINE void cast_ull_mem_sl_reg (sl a, ull * b) { *b = a; }

NOINLINE sc  cast_sc_reg_sl_mem (sl * a) { sc  b = *a; return b; }
NOINLINE uc  cast_uc_reg_sl_mem (sl * a) { uc  b = *a; return b; }
NOINLINE ss  cast_ss_reg_sl_mem (sl * a) { ss  b = *a; return b; }
NOINLINE us  cast_us_reg_sl_mem (sl * a) { us  b = *a; return b; }
NOINLINE si  cast_si_reg_sl_mem (sl * a) { si  b = *a; return b; }
NOINLINE ui  cast_ui_reg_sl_mem (sl * a) { ui  b = *a; return b; }
NOINLINE sl  cast_sl_reg_sl_mem (sl * a) { sl  b = *a; return b; }
NOINLINE ul  cast_ul_reg_sl_mem (sl * a) { ul  b = *a; return b; }
NOINLINE sll cast_sll_reg_sl_mem(sl * a) { sll b = *a; return b; }
NOINLINE ull cast_ull_reg_sl_mem(sl * a) { ull b = *a; return b; }


NOINLINE sc  cast_sc_reg_ul_reg (ul a)   { sc  b = a; return b; }
NOINLINE uc  cast_uc_reg_ul_reg (ul a)   { uc  b = a; return b; }
NOINLINE ss  cast_ss_reg_ul_reg (ul a)   { ss  b = a; return b; }
NOINLINE us  cast_us_reg_ul_reg (ul a)   { us  b = a; return b; }
NOINLINE si  cast_si_reg_ul_reg (ul a)   { si  b = a; return b; }
NOINLINE ui  cast_ui_reg_ul_reg (ul a)   { ui  b = a; return b; }
NOINLINE sl  cast_sl_reg_ul_reg (ul a)   { sl  b = a; return b; }
NOINLINE ul  cast_ul_reg_ul_reg (ul a)   { ul  b = a; return b; }
NOINLINE sll cast_sll_reg_ul_reg(ul a)   { sll b = a; return b; }
NOINLINE ull cast_ull_reg_ul_reg(ul a)   { ull b = a; return b; }

NOINLINE void cast_sc_mem_ul_reg (ul a, sc * b)   { *b = a; }
NOINLINE void cast_uc_mem_ul_reg (ul a, uc * b)   { *b = a; }
NOINLINE void cast_ss_mem_ul_reg (ul a, ss * b)   { *b = a; }
NOINLINE void cast_us_mem_ul_reg (ul a, us * b)   { *b = a; }
NOINLINE void cast_si_mem_ul_reg (ul a, si * b)   { *b = a; }
NOINLINE void cast_ui_mem_ul_reg (ul a, ui * b)   { *b = a; }
NOINLINE void cast_sl_mem_ul_reg (ul a, sl * b)   { *b = a; }
NOINLINE void cast_ul_mem_ul_reg (ul a, ul * b)   { *b = a; }
NOINLINE void cast_sll_mem_ul_reg (ul a, sll * b) { *b = a; }
NOINLINE void cast_ull_mem_ul_reg (ul a, ull * b) { *b = a; }

NOINLINE sc  cast_sc_reg_ul_mem (ul * a) { sc  b = *a; return b; }
NOINLINE uc  cast_uc_reg_ul_mem (ul * a) { uc  b = *a; return b; }
NOINLINE ss  cast_ss_reg_ul_mem (ul * a) { ss  b = *a; return b; }
NOINLINE us  cast_us_reg_ul_mem (ul * a) { us  b = *a; return b; }
NOINLINE si  cast_si_reg_ul_mem (ul * a) { si  b = *a; return b; }
NOINLINE ui  cast_ui_reg_ul_mem (ul * a) { ui  b = *a; return b; }
NOINLINE sl  cast_sl_reg_ul_mem (ul * a) { sl  b = *a; return b; }
NOINLINE ul  cast_ul_reg_ul_mem (ul * a) { ul  b = *a; return b; }
NOINLINE sll cast_sll_reg_ul_mem(ul * a) { sll b = *a; return b; }
NOINLINE ull cast_ull_reg_ul_mem(ul * a) { ull b = *a; return b; }


NOINLINE sc  cast_sc_reg_sll_reg (sll a)   { sc  b = a; return b; }
NOINLINE uc  cast_uc_reg_sll_reg (sll a)   { uc  b = a; return b; }
NOINLINE ss  cast_ss_reg_sll_reg (sll a)   { ss  b = a; return b; }
NOINLINE us  cast_us_reg_sll_reg (sll a)   { us  b = a; return b; }
NOINLINE si  cast_si_reg_sll_reg (sll a)   { si  b = a; return b; }
NOINLINE ui  cast_ui_reg_sll_reg (sll a)   { ui  b = a; return b; }
NOINLINE sl  cast_sl_reg_sll_reg (sll a)   { sl  b = a; return b; }
NOINLINE ul  cast_ul_reg_sll_reg (sll a)   { ul  b = a; return b; }
NOINLINE sll cast_sll_reg_sll_reg(sll a)   { sll b = a; return b; }
NOINLINE ull cast_ull_reg_sll_reg(sll a)   { ull b = a; return b; }

NOINLINE void cast_sc_mem_sll_reg (sll a, sc * b)   { *b = a; }
NOINLINE void cast_uc_mem_sll_reg (sll a, uc * b)   { *b = a; }
NOINLINE void cast_ss_mem_sll_reg (sll a, ss * b)   { *b = a; }
NOINLINE void cast_us_mem_sll_reg (sll a, us * b)   { *b = a; }
NOINLINE void cast_si_mem_sll_reg (sll a, si * b)   { *b = a; }
NOINLINE void cast_ui_mem_sll_reg (sll a, ui * b)   { *b = a; }
NOINLINE void cast_sl_mem_sll_reg (sll a, sl * b)   { *b = a; }
NOINLINE void cast_ul_mem_sll_reg (sll a, ul * b)   { *b = a; }
NOINLINE void cast_sll_mem_sll_reg (sll a, sll * b) { *b = a; }
NOINLINE void cast_ull_mem_sll_reg (sll a, ull * b) { *b = a; }

NOINLINE sc  cast_sc_reg_sll_mem (sll * a) { sc  b = *a; return b; }
NOINLINE uc  cast_uc_reg_sll_mem (sll * a) { uc  b = *a; return b; }
NOINLINE ss  cast_ss_reg_sll_mem (sll * a) { ss  b = *a; return b; }
NOINLINE us  cast_us_reg_sll_mem (sll * a) { us  b = *a; return b; }
NOINLINE si  cast_si_reg_sll_mem (sll * a) { si  b = *a; return b; }
NOINLINE ui  cast_ui_reg_sll_mem (sll * a) { ui  b = *a; return b; }
NOINLINE sl  cast_sl_reg_sll_mem (sll * a) { sl  b = *a; return b; }
NOINLINE ul  cast_ul_reg_sll_mem (sll * a) { ul  b = *a; return b; }
NOINLINE sll cast_sll_reg_sll_mem(sll * a) { sll b = *a; return b; }
NOINLINE ull cast_ull_reg_sll_mem(sll * a) { ull b = *a; return b; }


NOINLINE sc  cast_sc_reg_ull_reg (ull a)   { sc  b = a; return b; }
NOINLINE uc  cast_uc_reg_ull_reg (ull a)   { uc  b = a; return b; }
NOINLINE ss  cast_ss_reg_ull_reg (ull a)   { ss  b = a; return b; }
NOINLINE us  cast_us_reg_ull_reg (ull a)   { us  b = a; return b; }
NOINLINE si  cast_si_reg_ull_reg (ull a)   { si  b = a; return b; }
NOINLINE ui  cast_ui_reg_ull_reg (ull a)   { ui  b = a; return b; }
NOINLINE sl  cast_sl_reg_ull_reg (ull a)   { sl  b = a; return b; }
NOINLINE ul  cast_ul_reg_ull_reg (ull a)   { ul  b = a; return b; }
NOINLINE sll cast_sll_reg_ull_reg(ull a)   { sll b = a; return b; }
NOINLINE ull cast_ull_reg_ull_reg(ull a)   { ull b = a; return b; }

NOINLINE void cast_sc_mem_ull_reg (ull a, sc * b)   { *b = a; }
NOINLINE void cast_uc_mem_ull_reg (ull a, uc * b)   { *b = a; }
NOINLINE void cast_ss_mem_ull_reg (ull a, ss * b)   { *b = a; }
NOINLINE void cast_us_mem_ull_reg (ull a, us * b)   { *b = a; }
NOINLINE void cast_si_mem_ull_reg (ull a, si * b)   { *b = a; }
NOINLINE void cast_ui_mem_ull_reg (ull a, ui * b)   { *b = a; }
NOINLINE void cast_sl_mem_ull_reg (ull a, sl * b)   { *b = a; }
NOINLINE void cast_ul_mem_ull_reg (ull a, ul * b)   { *b = a; }
NOINLINE void cast_sll_mem_ull_reg (ull a, sll * b) { *b = a; }
NOINLINE void cast_ull_mem_ull_reg (ull a, ull * b) { *b = a; }

NOINLINE sc  cast_sc_reg_ull_mem (ull * a) { sc  b = *a; return b; }
NOINLINE uc  cast_uc_reg_ull_mem (ull * a) { uc  b = *a; return b; }
NOINLINE ss  cast_ss_reg_ull_mem (ull * a) { ss  b = *a; return b; }
NOINLINE us  cast_us_reg_ull_mem (ull * a) { us  b = *a; return b; }
NOINLINE si  cast_si_reg_ull_mem (ull * a) { si  b = *a; return b; }
NOINLINE ui  cast_ui_reg_ull_mem (ull * a) { ui  b = *a; return b; }
NOINLINE sl  cast_sl_reg_ull_mem (ull * a) { sl  b = *a; return b; }
NOINLINE ul  cast_ul_reg_ull_mem (ull * a) { ul  b = *a; return b; }
NOINLINE sll cast_sll_reg_ull_mem(ull * a) { sll b = *a; return b; }
NOINLINE ull cast_ull_reg_ull_mem(ull * a) { ull b = *a; return b; }



void cast_from_sgn_char(signed CHAR_TST_T a)
{
  chess_message("// cast_from_sgn_char(" << (int)a << ')');

  chess_report(cast_sc_reg_sc_reg(a));
  chess_report(cast_uc_reg_sc_reg(a));
  chess_report(cast_ss_reg_sc_reg(a));
  chess_report(cast_us_reg_sc_reg(a));
  chess_report(cast_si_reg_sc_reg(a));
  chess_report(cast_ui_reg_sc_reg(a));
  chess_report(cast_sl_reg_sc_reg(a));
  chess_report(cast_ul_reg_sc_reg(a));
  chess_report(cast_sll_reg_sc_reg(a));
  chess_report(cast_ull_reg_sc_reg(a));

  { sc b; cast_sc_mem_sc_reg(a,&b); chess_report(b); }
  { uc b; cast_uc_mem_sc_reg(a,&b); chess_report(b); }
  { ss b; cast_ss_mem_sc_reg(a,&b); chess_report(b); }
  { us b; cast_us_mem_sc_reg(a,&b); chess_report(b); }
  { si b; cast_si_mem_sc_reg(a,&b); chess_report(b); }
  { ui b; cast_ui_mem_sc_reg(a,&b); chess_report(b); }
  { sl b; cast_sl_mem_sc_reg(a,&b); chess_report(b); }
  { ul b; cast_ul_mem_sc_reg(a,&b); chess_report(b); }
  { sll b; cast_sll_mem_sc_reg(a,&b); chess_report(b); }
  { ull b; cast_ull_mem_sc_reg(a,&b); chess_report(b); }

  chess_report(cast_sc_reg_sc_mem(&a));
  chess_report(cast_uc_reg_sc_mem(&a));
  chess_report(cast_ss_reg_sc_mem(&a));
  chess_report(cast_us_reg_sc_mem(&a));
  chess_report(cast_si_reg_sc_mem(&a));
  chess_report(cast_ui_reg_sc_mem(&a));
  chess_report(cast_sl_reg_sc_mem(&a));
  chess_report(cast_ul_reg_sc_mem(&a));
  chess_report(cast_sll_reg_sc_mem(&a));
  chess_report(cast_ull_reg_sc_mem(&a));
}
void cast_from_uns_char(unsigned CHAR_TST_T a)
{
    chess_message("// cast_from_uns_char(" << (unsigned)a << ')');

    chess_report(cast_sc_reg_uc_reg(a));
    chess_report(cast_uc_reg_uc_reg(a));
    chess_report(cast_ss_reg_uc_reg(a));
    chess_report(cast_us_reg_uc_reg(a));
    chess_report(cast_si_reg_uc_reg(a));
    chess_report(cast_ui_reg_uc_reg(a));
    chess_report(cast_sl_reg_uc_reg(a));
    chess_report(cast_ul_reg_uc_reg(a));
    chess_report(cast_sll_reg_uc_reg(a));
    chess_report(cast_ull_reg_uc_reg(a));

    { sc b; cast_sc_mem_uc_reg(a,&b); chess_report(b); }
    { uc b; cast_uc_mem_uc_reg(a,&b); chess_report(b); }
    { ss b; cast_ss_mem_uc_reg(a,&b); chess_report(b); }
    { us b; cast_us_mem_uc_reg(a,&b); chess_report(b); }
    { si b; cast_si_mem_uc_reg(a,&b); chess_report(b); }
    { ui b; cast_ui_mem_uc_reg(a,&b); chess_report(b); }
    { sl b; cast_sl_mem_uc_reg(a,&b); chess_report(b); }
    { ul b; cast_ul_mem_uc_reg(a,&b); chess_report(b); }
    { sll b; cast_sll_mem_uc_reg(a,&b); chess_report(b); }
    { ull b; cast_ull_mem_uc_reg(a,&b); chess_report(b); }

    chess_report(cast_sc_reg_uc_mem(&a));
    chess_report(cast_uc_reg_uc_mem(&a));
    chess_report(cast_ss_reg_uc_mem(&a));
    chess_report(cast_us_reg_uc_mem(&a));
    chess_report(cast_si_reg_uc_mem(&a));
    chess_report(cast_ui_reg_uc_mem(&a));
    chess_report(cast_sl_reg_uc_mem(&a));
    chess_report(cast_ul_reg_uc_mem(&a));
    chess_report(cast_sll_reg_uc_mem(&a));
    chess_report(cast_ull_reg_uc_mem(&a));
}

void cast_from_sgn_short(signed short a)
{
    chess_message("// cast_from_sgn_short(" << a << ')');

    chess_report(cast_sc_reg_ss_reg(a));
    chess_report(cast_uc_reg_ss_reg(a));
    chess_report(cast_ss_reg_ss_reg(a));
    chess_report(cast_us_reg_ss_reg(a));
    chess_report(cast_si_reg_ss_reg(a));
    chess_report(cast_ui_reg_ss_reg(a));
    chess_report(cast_sl_reg_ss_reg(a));
    chess_report(cast_ul_reg_ss_reg(a));
    chess_report(cast_sll_reg_ss_reg(a));
    chess_report(cast_ull_reg_ss_reg(a));

    { sc b; cast_sc_mem_ss_reg(a,&b); chess_report(b); }
    { uc b; cast_uc_mem_ss_reg(a,&b); chess_report(b); }
    { ss b; cast_ss_mem_ss_reg(a,&b); chess_report(b); }
    { us b; cast_us_mem_ss_reg(a,&b); chess_report(b); }
    { si b; cast_si_mem_ss_reg(a,&b); chess_report(b); }
    { ui b; cast_ui_mem_ss_reg(a,&b); chess_report(b); }
    { sl b; cast_sl_mem_ss_reg(a,&b); chess_report(b); }
    { ul b; cast_ul_mem_ss_reg(a,&b); chess_report(b); }
    { sll b; cast_sll_mem_ss_reg(a,&b); chess_report(b); }
    { ull b; cast_ull_mem_ss_reg(a,&b); chess_report(b); }

    chess_report(cast_sc_reg_ss_mem(&a));
    chess_report(cast_uc_reg_ss_mem(&a));
    chess_report(cast_ss_reg_ss_mem(&a));
    chess_report(cast_us_reg_ss_mem(&a));
    chess_report(cast_si_reg_ss_mem(&a));
    chess_report(cast_ui_reg_ss_mem(&a));
    chess_report(cast_sl_reg_ss_mem(&a));
    chess_report(cast_ul_reg_ss_mem(&a));
    chess_report(cast_sll_reg_ss_mem(&a));
    chess_report(cast_ull_reg_ss_mem(&a));
}
void cast_from_uns_short(unsigned short a)
{
    chess_message("// cast_from_uns_short(" << a << ')');

    chess_report(cast_sc_reg_us_reg(a));
    chess_report(cast_uc_reg_us_reg(a));
    chess_report(cast_ss_reg_us_reg(a));
    chess_report(cast_us_reg_us_reg(a));
    chess_report(cast_si_reg_us_reg(a));
    chess_report(cast_ui_reg_us_reg(a));
    chess_report(cast_sl_reg_us_reg(a));
    chess_report(cast_ul_reg_us_reg(a));
    chess_report(cast_sll_reg_us_reg(a));
    chess_report(cast_ull_reg_us_reg(a));

    { sc b; cast_sc_mem_us_reg(a,&b); chess_report(b); }
    { uc b; cast_uc_mem_us_reg(a,&b); chess_report(b); }
    { ss b; cast_ss_mem_us_reg(a,&b); chess_report(b); }
    { us b; cast_us_mem_us_reg(a,&b); chess_report(b); }
    { si b; cast_si_mem_us_reg(a,&b); chess_report(b); }
    { ui b; cast_ui_mem_us_reg(a,&b); chess_report(b); }
    { sl b; cast_sl_mem_us_reg(a,&b); chess_report(b); }
    { ul b; cast_ul_mem_us_reg(a,&b); chess_report(b); }
    { sll b; cast_sll_mem_us_reg(a,&b); chess_report(b); }
    { ull b; cast_ull_mem_us_reg(a,&b); chess_report(b); }

    chess_report(cast_sc_reg_us_mem(&a));
    chess_report(cast_uc_reg_us_mem(&a));
    chess_report(cast_ss_reg_us_mem(&a));
    chess_report(cast_us_reg_us_mem(&a));
    chess_report(cast_si_reg_us_mem(&a));
    chess_report(cast_ui_reg_us_mem(&a));
    chess_report(cast_sl_reg_us_mem(&a));
    chess_report(cast_ul_reg_us_mem(&a));
    chess_report(cast_sll_reg_us_mem(&a));
    chess_report(cast_ull_reg_us_mem(&a));
}

void cast_from_sgn_int(signed int a)
{
    chess_message("// cast_from_sgn_int(" << a << ')');

    chess_report(cast_sc_reg_si_reg(a));
    chess_report(cast_uc_reg_si_reg(a));
    chess_report(cast_ss_reg_si_reg(a));
    chess_report(cast_us_reg_si_reg(a));
    chess_report(cast_si_reg_si_reg(a));
    chess_report(cast_ui_reg_si_reg(a));
    chess_report(cast_sl_reg_si_reg(a));
    chess_report(cast_ul_reg_si_reg(a));
    chess_report(cast_sll_reg_si_reg(a));
    chess_report(cast_ull_reg_si_reg(a));

    { sc b; cast_sc_mem_si_reg(a,&b); chess_report(b); }
    { uc b; cast_uc_mem_si_reg(a,&b); chess_report(b); }
    { ss b; cast_ss_mem_si_reg(a,&b); chess_report(b); }
    { us b; cast_us_mem_si_reg(a,&b); chess_report(b); }
    { si b; cast_si_mem_si_reg(a,&b); chess_report(b); }
    { ui b; cast_ui_mem_si_reg(a,&b); chess_report(b); }
    { sl b; cast_sl_mem_si_reg(a,&b); chess_report(b); }
    { ul b; cast_ul_mem_si_reg(a,&b); chess_report(b); }
    { sll b; cast_sll_mem_si_reg(a,&b); chess_report(b); }
    { ull b; cast_ull_mem_si_reg(a,&b); chess_report(b); }

    chess_report(cast_sc_reg_si_mem(&a));
    chess_report(cast_uc_reg_si_mem(&a));
    chess_report(cast_ss_reg_si_mem(&a));
    chess_report(cast_us_reg_si_mem(&a));
    chess_report(cast_si_reg_si_mem(&a));
    chess_report(cast_ui_reg_si_mem(&a));
    chess_report(cast_sl_reg_si_mem(&a));
    chess_report(cast_ul_reg_si_mem(&a));
    chess_report(cast_sll_reg_si_mem(&a));
    chess_report(cast_ull_reg_si_mem(&a));
}
void cast_from_uns_int(unsigned int a)
{
    chess_message("// cast_from_uns_int(" << a << ')');

    chess_report(cast_sc_reg_ui_reg(a));
    chess_report(cast_uc_reg_ui_reg(a));
    chess_report(cast_ss_reg_ui_reg(a));
    chess_report(cast_us_reg_ui_reg(a));
    chess_report(cast_si_reg_ui_reg(a));
    chess_report(cast_ui_reg_ui_reg(a));
    chess_report(cast_sl_reg_ui_reg(a));
    chess_report(cast_ul_reg_ui_reg(a));
    chess_report(cast_sll_reg_ui_reg(a));
    chess_report(cast_ull_reg_ui_reg(a));

    { sc b; cast_sc_mem_ui_reg(a,&b); chess_report(b); }
    { uc b; cast_uc_mem_ui_reg(a,&b); chess_report(b); }
    { ss b; cast_ss_mem_ui_reg(a,&b); chess_report(b); }
    { us b; cast_us_mem_ui_reg(a,&b); chess_report(b); }
    { si b; cast_si_mem_ui_reg(a,&b); chess_report(b); }
    { ui b; cast_ui_mem_ui_reg(a,&b); chess_report(b); }
    { sl b; cast_sl_mem_ui_reg(a,&b); chess_report(b); }
    { ul b; cast_ul_mem_ui_reg(a,&b); chess_report(b); }
    { sll b; cast_sll_mem_ui_reg(a,&b); chess_report(b); }
    { ull b; cast_ull_mem_ui_reg(a,&b); chess_report(b); }

    chess_report(cast_sc_reg_ui_mem(&a));
    chess_report(cast_uc_reg_ui_mem(&a));
    chess_report(cast_ss_reg_ui_mem(&a));
    chess_report(cast_us_reg_ui_mem(&a));
    chess_report(cast_si_reg_ui_mem(&a));
    chess_report(cast_ui_reg_ui_mem(&a));
    chess_report(cast_sl_reg_ui_mem(&a));
    chess_report(cast_ul_reg_ui_mem(&a));
    chess_report(cast_sll_reg_ui_mem(&a));
    chess_report(cast_ull_reg_ui_mem(&a));
}

void cast_from_sgn_long(signed long a)
{
    chess_message("// cast_from_sgn_long(" << a << ')');

    chess_report(cast_sc_reg_sl_reg(a));
    chess_report(cast_uc_reg_sl_reg(a));
    chess_report(cast_ss_reg_sl_reg(a));
    chess_report(cast_us_reg_sl_reg(a));
    chess_report(cast_si_reg_sl_reg(a));
    chess_report(cast_ui_reg_sl_reg(a));
    chess_report(cast_sl_reg_sl_reg(a));
    chess_report(cast_ul_reg_sl_reg(a));
    chess_report(cast_sll_reg_sl_reg(a));
    chess_report(cast_ull_reg_sl_reg(a));

    { sc b; cast_sc_mem_sl_reg(a,&b); chess_report(b); }
    { uc b; cast_uc_mem_sl_reg(a,&b); chess_report(b); }
    { ss b; cast_ss_mem_sl_reg(a,&b); chess_report(b); }
    { us b; cast_us_mem_sl_reg(a,&b); chess_report(b); }
    { si b; cast_si_mem_sl_reg(a,&b); chess_report(b); }
    { ui b; cast_ui_mem_sl_reg(a,&b); chess_report(b); }
    { sl b; cast_sl_mem_sl_reg(a,&b); chess_report(b); }
    { ul b; cast_ul_mem_sl_reg(a,&b); chess_report(b); }
    { sll b; cast_sll_mem_sl_reg(a,&b); chess_report(b); }
    { ull b; cast_ull_mem_sl_reg(a,&b); chess_report(b); }

    chess_report(cast_sc_reg_sl_mem(&a));
    chess_report(cast_uc_reg_sl_mem(&a));
    chess_report(cast_ss_reg_sl_mem(&a));
    chess_report(cast_us_reg_sl_mem(&a));
    chess_report(cast_si_reg_sl_mem(&a));
    chess_report(cast_ui_reg_sl_mem(&a));
    chess_report(cast_sl_reg_sl_mem(&a));
    chess_report(cast_ul_reg_sl_mem(&a));
    chess_report(cast_sll_reg_sl_mem(&a));
    chess_report(cast_ull_reg_sl_mem(&a));
}
void cast_from_uns_long(unsigned long a)
{
    chess_message("// cast_from_uns_long(" << a << ')');

    chess_report(cast_sc_reg_ul_reg(a));
    chess_report(cast_uc_reg_ul_reg(a));
    chess_report(cast_ss_reg_ul_reg(a));
    chess_report(cast_us_reg_ul_reg(a));
    chess_report(cast_si_reg_ul_reg(a));
    chess_report(cast_ui_reg_ul_reg(a));
    chess_report(cast_sl_reg_ul_reg(a));
    chess_report(cast_ul_reg_ul_reg(a));
    chess_report(cast_sll_reg_ul_reg(a));
    chess_report(cast_ull_reg_ul_reg(a));

    { sc b; cast_sc_mem_ul_reg(a,&b); chess_report(b); }
    { uc b; cast_uc_mem_ul_reg(a,&b); chess_report(b); }
    { ss b; cast_ss_mem_ul_reg(a,&b); chess_report(b); }
    { us b; cast_us_mem_ul_reg(a,&b); chess_report(b); }
    { si b; cast_si_mem_ul_reg(a,&b); chess_report(b); }
    { ui b; cast_ui_mem_ul_reg(a,&b); chess_report(b); }
    { sl b; cast_sl_mem_ul_reg(a,&b); chess_report(b); }
    { ul b; cast_ul_mem_ul_reg(a,&b); chess_report(b); }
    { sll b; cast_sll_mem_ul_reg(a,&b); chess_report(b); }
    { ull b; cast_ull_mem_ul_reg(a,&b); chess_report(b); }

    chess_report(cast_sc_reg_ul_mem(&a));
    chess_report(cast_uc_reg_ul_mem(&a));
    chess_report(cast_ss_reg_ul_mem(&a));
    chess_report(cast_us_reg_ul_mem(&a));
    chess_report(cast_si_reg_ul_mem(&a));
    chess_report(cast_ui_reg_ul_mem(&a));
    chess_report(cast_sl_reg_ul_mem(&a));
    chess_report(cast_ul_reg_ul_mem(&a));
    chess_report(cast_sll_reg_ul_mem(&a));
    chess_report(cast_ull_reg_ul_mem(&a));
}

void cast_from_sgn_long_long(signed long long a)
{
    chess_message("// cast_from_sgn_long_long(" << a << ')');

    chess_report(cast_sc_reg_sll_reg(a));
    chess_report(cast_uc_reg_sll_reg(a));
    chess_report(cast_ss_reg_sll_reg(a));
    chess_report(cast_us_reg_sll_reg(a));
    chess_report(cast_si_reg_sll_reg(a));
    chess_report(cast_ui_reg_sll_reg(a));
    chess_report(cast_sl_reg_sll_reg(a));
    chess_report(cast_ul_reg_sll_reg(a));
    chess_report(cast_sll_reg_sll_reg(a));
    chess_report(cast_ull_reg_sll_reg(a));

    { sc b; cast_sc_mem_sll_reg(a,&b); chess_report(b); }
    { uc b; cast_uc_mem_sll_reg(a,&b); chess_report(b); }
    { ss b; cast_ss_mem_sll_reg(a,&b); chess_report(b); }
    { us b; cast_us_mem_sll_reg(a,&b); chess_report(b); }
    { si b; cast_si_mem_sll_reg(a,&b); chess_report(b); }
    { ui b; cast_ui_mem_sll_reg(a,&b); chess_report(b); }
    { sl b; cast_sl_mem_sll_reg(a,&b); chess_report(b); }
    { ul b; cast_ul_mem_sll_reg(a,&b); chess_report(b); }
    { sll b; cast_sll_mem_sll_reg(a,&b); chess_report(b); }
    { ull b; cast_ull_mem_sll_reg(a,&b); chess_report(b); }

    chess_report(cast_sc_reg_sll_mem(&a));
    chess_report(cast_uc_reg_sll_mem(&a));
    chess_report(cast_ss_reg_sll_mem(&a));
    chess_report(cast_us_reg_sll_mem(&a));
    chess_report(cast_si_reg_sll_mem(&a));
    chess_report(cast_ui_reg_sll_mem(&a));
    chess_report(cast_sl_reg_sll_mem(&a));
    chess_report(cast_ul_reg_sll_mem(&a));
    chess_report(cast_sll_reg_sll_mem(&a));
    chess_report(cast_ull_reg_sll_mem(&a));
}
void cast_from_uns_long_long(unsigned long long a)
{
    chess_message("// cast_from_uns_long_long(" << a << ')');

    chess_report(cast_sc_reg_ull_reg(a));
    chess_report(cast_uc_reg_ull_reg(a));
    chess_report(cast_ss_reg_ull_reg(a));
    chess_report(cast_us_reg_ull_reg(a));
    chess_report(cast_si_reg_ull_reg(a));
    chess_report(cast_ui_reg_ull_reg(a));
    chess_report(cast_sl_reg_ull_reg(a));
    chess_report(cast_ul_reg_ull_reg(a));
    chess_report(cast_sll_reg_ull_reg(a));
    chess_report(cast_ull_reg_ull_reg(a));

    { sc b; cast_sc_mem_ull_reg(a,&b); chess_report(b); }
    { uc b; cast_uc_mem_ull_reg(a,&b); chess_report(b); }
    { ss b; cast_ss_mem_ull_reg(a,&b); chess_report(b); }
    { us b; cast_us_mem_ull_reg(a,&b); chess_report(b); }
    { si b; cast_si_mem_ull_reg(a,&b); chess_report(b); }
    { ui b; cast_ui_mem_ull_reg(a,&b); chess_report(b); }
    { sl b; cast_sl_mem_ull_reg(a,&b); chess_report(b); }
    { ul b; cast_ul_mem_ull_reg(a,&b); chess_report(b); }
    { sll b; cast_sll_mem_ull_reg(a,&b); chess_report(b); }
    { ull b; cast_ull_mem_ull_reg(a,&b); chess_report(b); }

    chess_report(cast_sc_reg_ull_mem(&a));
    chess_report(cast_uc_reg_ull_mem(&a));
    chess_report(cast_ss_reg_ull_mem(&a));
    chess_report(cast_us_reg_ull_mem(&a));
    chess_report(cast_si_reg_ull_mem(&a));
    chess_report(cast_ui_reg_ull_mem(&a));
    chess_report(cast_sl_reg_ull_mem(&a));
    chess_report(cast_ul_reg_ull_mem(&a));
    chess_report(cast_sll_reg_ull_mem(&a));
    chess_report(cast_ull_reg_ull_mem(&a));
}

int main()
{
    #ifdef HAS_CHAR
        cast_from_sgn_char(                 10  );
        cast_from_sgn_char(                -20  );
        cast_from_sgn_char( CHAR_SE(CHAR_X8000) );
        cast_from_sgn_char( CHAR_SE(CHAR_X7FFF) );
        cast_from_sgn_char( CHAR_SE(CHAR_XFFFF) );

        cast_from_uns_char(                 10  );
        cast_from_uns_char(                 20  );
        cast_from_uns_char( CHAR_ZE(CHAR_X8000) );
        cast_from_uns_char( CHAR_ZE(CHAR_X7FFF) );
        cast_from_uns_char( CHAR_ZE(CHAR_XFFFF) );
    #endif

    #ifdef HAS_SHORT
        cast_from_sgn_short(                 10  );
        cast_from_sgn_short(                -20  );
        cast_from_sgn_short( SHRT_SE(SHRT_X8000) );
        cast_from_sgn_short( SHRT_SE(SHRT_X7FFF) );
        cast_from_sgn_short( SHRT_SE(SHRT_XFFFF) );

        cast_from_uns_short(                 10  );
        cast_from_uns_short(                 20  );
        cast_from_uns_short( SHRT_ZE(SHRT_X8000) );
        cast_from_uns_short( SHRT_ZE(SHRT_X7FFF) );
        cast_from_uns_short( SHRT_ZE(SHRT_XFFFF) );
    #endif

    #ifdef HAS_INT
        cast_from_sgn_int(               10  );
        cast_from_sgn_int(              -20  );
        cast_from_sgn_int( INT_SE(INT_X8000) );
        cast_from_sgn_int( INT_SE(INT_X7FFF) );
        cast_from_sgn_int( INT_SE(INT_XFFFF) );

        cast_from_uns_int(               10  );
        cast_from_uns_int(               20  );
        cast_from_uns_int( INT_ZE(INT_X8000) );
        cast_from_uns_int( INT_ZE(INT_X7FFF) );
        cast_from_uns_int( INT_ZE(INT_XFFFF) );
    #endif

    #ifdef HAS_LONG
        cast_from_sgn_long(               10  );
        cast_from_sgn_long(              -20  );
        cast_from_sgn_long( LNG_SE(LNG_X8000) );
        cast_from_sgn_long( LNG_SE(LNG_X7FFF) );
        cast_from_sgn_long( LNG_SE(LNG_XFFFF) );

        cast_from_uns_long(               10  );
        cast_from_uns_long(               20  );
        cast_from_uns_long( LNG_ZE(LNG_X8000) );
        cast_from_uns_long( LNG_ZE(LNG_X7FFF) );
        cast_from_uns_long( LNG_ZE(LNG_XFFFF) );
    #endif

    #ifdef HAS_LONG_LONG
        cast_from_sgn_long_long(                 10  );
        cast_from_sgn_long_long(                -20  );
        cast_from_sgn_long_long( LLNG_SE(LLNG_X8000) );
        cast_from_sgn_long_long( LLNG_SE(LLNG_X7FFF) );
        cast_from_sgn_long_long( LLNG_SE(LLNG_XFFFF) );

        cast_from_uns_long_long(                 10  );
        cast_from_uns_long_long(                 20  );
        cast_from_uns_long_long( LLNG_ZE(LLNG_X8000) );
        cast_from_uns_long_long( LLNG_ZE(LLNG_X7FFF) );
        cast_from_uns_long_long( LLNG_ZE(LLNG_XFFFF) );
    #endif

    return 0;
}
