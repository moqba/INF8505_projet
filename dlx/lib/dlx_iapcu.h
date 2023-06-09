// File generated by checkers version 09R1 6.2.6, Tue Aug 18 09:25:04 2009
// Copyright(c) 1996-2009 Target Compiler Technologies NV
// All rights reserved.
// checkers -B -M -cdlx_ia.ccf dlx

// Processor: dlx

#ifndef __Mdl_dlx_iapcu_user_c__
#define __Mdl_dlx_iapcu_user_c__

#include "checkers_enum.h"
#include "Mdl_dlx.h"
#include "dlx_define.h"

// This functions is called at the end of simulating an instruction and
// must set the program counter to the value for the next step. It has the
// following signature:
// 
// inline void <processor>_user_next_pc(<processor>* mdl, unsigned next_pc,
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

inline void dlx_user_next_pc(dlx* mdl, unsigned next_pc, unsigned nw, Checkers_next_pc_type npt)
{
    /* User code here */
    mdl->PC = next_pc;
}

inline unsigned dlx_loop_end(dlx* mdl, unsigned nw)
{
#ifdef DLX_HAS_ZLOOP
    // zloops are inner-most loops
    unsigned pc = mdl->PC.value();
    unsigned ze = mdl->ZE.value();
    if (ze == pc) { // is this a zloop end?
        unsigned zc = mdl->ZC.value();
        if (zc == 1) { // done
            unsigned zd = mdl->ZD.value();
            mdl->ZC = zd; // restore count register (zloop_count_invariant)
            return mdl->PC.to_unsigned() + nw; // exit loop
        } else {
            mdl->ZC = zc - 1;
            unsigned zs = mdl->ZS.value();
            return zs; // jump back
        }
    }
#endif
#ifdef DLX_HAS_DOLOOP
    int lfra = mdl->LF.value();
    if (lfra < 3) {
        if (mdl->LC[lfra].value() != 1) {  // jump back
            mdl->LC[lfra] = mdl->LC[lfra].value() - 1;
            return mdl->LS[lfra].value();
        }
        else { // exit loop
            mdl->LF = lfra - 1;
        }
    }
#endif

    return mdl->PC.to_unsigned() + nw;
}

#endif

