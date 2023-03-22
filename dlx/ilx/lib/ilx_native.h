/*
-- File : ilx_native.h
--
-- Contents :  support for native compilation
--
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model 
-- captures an ASIP Designer Design Technique. The model and all associated 
-- documentation are proprietary to Synopsys, Inc. and may only be used 
-- pursuant to the terms and conditions of a written license agreement with 
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution 
-- of the Synopsys processor model or the associated  documentation is 
-- strictly prohibited. 
*/



#ifndef _ilx_native_h
#define _ilx_native_h


#include "isg/ilx_iss_types.h"

#include "isg/ilx_chess_types.h"
#include "isg/ilx_chess_opns.h"


inline bool get_activity() { return 0; }

inline void mtx_acquire() { }
inline void mtx_release() { }

inline int  load_rsvd(volatile int* p)  { return *p; }
inline int store_cond(volatile int* p, int v) { *p=v; return true; }

inline bool get_cmd_flag() { return 0; }

// example parameter bindings

inline void set_flow_void(int, void (*fp)(), void*) { fp(); }
inline void set_flow_int(int, void (*fp)(int), void*, int a) { fp(a); }
inline void set_flow_uintR_uintR(int, void (*fp)(unsigned& a, unsigned&b), void*, unsigned& a, unsigned& b) { fp(a,b); }

#endif /* _ilx_native_h */
