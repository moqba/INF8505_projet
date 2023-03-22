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

#if defined(__cplusplus) || defined(__ndl__)
extern "C" {
#endif

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

#ifdef __clang__
__attribute((always_inline,noreturn))
#endif
inline void clib_exit(int status)
{
    chess_exit(status); // signal exit to simulator

    while (1) ;         // don't continue / hardware halt
}

// see atexit.c
int __cxa_atexit(void (*func)(void*), void* arg, void* dso_handle) property(loop_free);
void __cxa_finalize(void* dso_handle);

#ifdef __clang__
__attribute((noreturn))
#endif
inline void exit(int status) {
    __cxa_finalize(NULL);
    clib_exit(status);
}

#ifdef __clang__
__attribute((noreturn))
#endif
inline void abort() { clib_exit(127); }

#ifdef __clang__
__attribute((noreturn))
#endif
inline void _Exit(int status) { clib_exit(status); }

inline int atexit( void (*func)() ) {
    return __cxa_atexit((void (*)(void*))func,NULL,NULL);
}

// 7.20.5 Searching and sorting utilities

void qsort(void *base,
	   size_t nmemb,
	   size_t size,
	   int (*compar)(const void *, const void *));

#if defined(__cplusplus) || defined(__ndl__)
} // extern "C"
#endif

#endif
