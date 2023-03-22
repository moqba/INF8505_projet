/*
-- File: stdlib.h
--
-- Contents : ISO C99 Standard, General utilities <stdlib.h>
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/



#ifndef _STDLIB_H
#define _STDLIB_H

#include <stddef.h>
#include <malloc.h>

// 7.20.1 Numeric conversion functions

long int strtol(const char *restrict nptr,
                char **restrict endptr,
                int base);

unsigned long int strtoul(const char * restrict nptr,
                          char ** restrict endptr,
                          int base);

inline int atoi(const char *nptr)
{
    return((int)strtol(nptr, (char **)NULL, 10));
}

inline long atol(const char *nptr)
{
    return strtol(nptr, (char **)NULL, 10);
}

// 7.20.2 Pseudo-random sequence generation functions

#define RAND_MAX 32767

int rand(void);
void srand(unsigned int seed);

// 7.20.4 Communication with the environment

inline assembly void exit(int status) property(never_returns loop_free)
    //  Move 'status' to R2, and jump to 0.
{
    asm_begin
.undef global text _main_init
    asm_text
      ori r2,r4,#0   ; move R4 to R2
      nop            ; flush pipeline in case ISS breakpoint stage is early
      nop
      nop
      nop
.stop
      nop
    asm_end
}

// 7.20.5 Searching and sorting utilities

void qsort(void *base,
           size_t nmemb,
           size_t size,
           int (*compar)(const void *, const void *));

#endif
