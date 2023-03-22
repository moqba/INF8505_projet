/*
-- File : ilx_mutex.h
--
-- Contents : Application layer for mutual exclusion (i.e. critical sections).
--
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/




#ifndef _ilx_mutex_h
#define _ilx_mutex_h

inline assembly bool tk_test_and_set() clobbers() property(volatile functional loop_free)
{
    asm_begin
        tk_test_and_set r2
    asm_end
}

inline assembly void tk_clear() clobbers() property(volatile functional loop_free)
{
    asm_begin
        tk_clear
    asm_end
}

inline void mtx_acquire() property(dont_generate_native) { while(tk_test_and_set()) ; }
inline void mtx_release() property(dont_generate_native) { tk_clear(); }

promotion int  load_rsvd(volatile int*     ) = w32  load_rsvd(addr);
promotion int store_cond(volatile int*, int) = w32 store_cond(addr,w32);

#endif /* _ilx_mutex_h */
