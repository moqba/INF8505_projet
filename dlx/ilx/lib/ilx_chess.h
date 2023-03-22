/*
-- File : ilx_chess.h
--
-- Contents : Chess specific header-file for the ILX processor.
--
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/



#ifndef _ilx_chess_h
#define _ilx_chess_h

#include "ilx.h"

// properties of short types

class signed   char  property( 8 bit signed);
class unsigned char  property( 8 bit unsigned);
class signed   short property(16 bit signed);
class unsigned short property(16 bit unsigned);
chess_properties {
    default_inline_generation : do_generate; // new in 18R1 -- will become the default later on

 // type promotions

    promotion w32            : transitory  { addr };
    promotion int16p         : strong  { w32 } ...;

    promotion signed short   : strong  { w16, w32 }
                               transitory { addr }
                               exclude { w32 extend_zero(w16) };

    promotion signed char    : strong  { w08, w16, w32 }
                               transitory { addr }
                               exclude { w32 extend_zero(w08),
                                       w32 extend_zero(w16) };

    promotion unsigned short : strong { w16, w32 }
                               transitory { addr }
                               exclude { w32 extend_sign(w16) };

    promotion unsigned char  : strong  { w08, w16, w32 }
                               transitory { addr }
                               exclude { w32 extend_sign(w08),
                                         w32 extend_sign(w16) };

    promotion bool : strong { w32 } ...;
    

 // declaration of built-in type representations

    representation int, unsigned   : w32;
    representation char            : signed char;
    representation long            : int;
    representation unsigned long   : unsigned;

    representation void*           : w32;

 // general properties

    default_memory                 : DMb;
    spill_memory                   : DMb, DMh, DMw;
    static_memory                  : DMb_stat;
    stack_pointer                  : SP;
    sp_location                    : free;
    sp_offset_type                 : int16;
    pointer_index_type             : int16;
    pointer_postmodify_type        : int5;
    link_register                  : LR;
    status_register                : MC;
    reserved                       : R0;  // compiler must not write to R0
    breakpoint_focus_stage         : 2;
    rewrite_condition_speculation_maximum : 6;
    no_redundant_loads             : DMb, DMh, DMw;

 // ABI
    argument_registers             : R4, R5, R6, R7, R8, R9, R10, R11, R12, R13, R14;
    argument_registers_return      : R2, R3;
    allow_callee_saved_inputs;

  // interleaved threading
    reserved                       : EN, TK;
    register_context_switch_on_interrupt;

 // optimisation
    bitfield_underlying_type       : short, int;
    complements                    : bool eqz(w32), bool nez(w32);
}

#include "ilx_host.h"
#include "ilx_mutex.h"
#include "ilx_int.h"
#include "ilx_longlong.h"
#include "ilx_const.h"
#include "ilx_mcpy.h"
#include "ilx_bitfield.h"
#include "ilx_float.h"
#include "ilx_double.h"

#include "ilx_rewrite.h"
#endif // _ilx_chess_h
