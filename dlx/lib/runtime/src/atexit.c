/*
-- File : atexit.c
--
-- Contents : atexit mechanism
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model 
-- captures an ASIP Designer Design Technique. The model and all associated 
-- documentation are proprietary to Synopsys, Inc. and may only be used 
-- pursuant to the terms and conditions of a written license agreement with 
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution 
-- of the Synopsys processor model or the associated  documentation is 
-- strictly prohibited. 
*/


// Also see: https://refspecs.linuxbase.org/cxxabi-1.83.html section 3.3.5 DSO Object Destruction API)

#include <stdlib.h>

#define CAPACITY 64          // atexit capacity, at the very least must be 32

typedef struct {
    void (*func)(void*);
    void* arg;
} atexit_pair;

static atexit_pair  atexits[CAPACITY];
static atexit_pair* atexit_nxt = &atexits[0];   // points to next available element

int __cxa_atexit(void (*func)(void*), void* arg, void* dso_handle) {
    if (atexit_nxt == &atexits[CAPACITY]) // atexits full?
        return -1;

    atexit_nxt->func = func;
    atexit_nxt->arg = arg;
    atexit_nxt++;
    return 0;
}

void __cxa_finalize(void* dso_handle) {
    while (atexit_nxt != &atexits[0]) {
        atexit_nxt--;
        atexit_nxt->func(atexit_nxt->arg);
    }
}
