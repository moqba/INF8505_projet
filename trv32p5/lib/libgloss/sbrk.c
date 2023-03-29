/*
-- File : sbrk.c
--
-- Contents : Implementation of sbrk system call (heap memory)
--
-- Copyright (c) 2014-2020 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/


#include <stddef.h>

#define HEAP_SIZE 1048576

#if defined(__cplusplus) || defined(__ndl__)
extern "C" {
#endif

static char _heap[HEAP_SIZE];
static char* _heap_current = _heap;

void* _sbrk(ptrdiff_t incr) {
    incr = (incr+7) & ~7ul;

    ptrdiff_t dif = &_heap[HEAP_SIZE] - _heap_current;

    if (incr > dif) {
        return 0;
    }

    char* old_heap = _heap_current;

    _heap_current = old_heap + incr;

    return (void*)old_heap;
}

#if defined(__cplusplus) || defined(__ndl__)
} // extern "C"
#endif
