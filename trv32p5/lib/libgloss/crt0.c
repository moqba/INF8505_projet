/*
-- File : crt0.c
--
-- Contents : Startup routine to call main
--
-- Copyright (c) 2014-2020 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/


#include <stdlib.h>

#if defined(__cplusplus) || defined(__ndl__)
extern "C" {
#endif

typedef void (*thunk)();
extern thunk _ctors_start;   // first element
extern thunk _ctors_end;     // past-the-last element
extern thunk _dtors_start;   // first element
extern thunk _dtors_end;     // past-the-last element

// the compiler is allowed to consider _start and _end as distinct, but they
// may be overlayed in reality; access one of them through a global variable to
// prevent optimization of the initial _start/_end comparison
thunk* _ctors_end_indir   = &_ctors_end;
thunk* _dtors_start_indir = &_dtors_start;

static inline void _init() {
    // constructors are called in reverse order of the list
    for (thunk* t = _ctors_end_indir; t-- != &_ctors_start; )
        (*t)();
}

static void _fini() {
    // destructors in forward order
    for (thunk* t = _dtors_start_indir; t != &_dtors_end; ++t)
        (*t)();
}

int main(int argc, char* argv[]);

int _start(int argc, char* argv[]) {
    atexit(_fini);
    _init();
    exit(main(argc,argv));
    return 0; // (unreachable, but needed for noodle)
}

#if defined(__cplusplus) || defined(__ndl__)
} // extern "C"
#endif
