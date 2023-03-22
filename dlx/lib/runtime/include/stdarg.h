/*
-- File: stdarg.h
--
-- Contents: ISO C99 Standard, 7.15 Variable arguments <stdarg.h>
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model 
-- captures an ASIP Designer Design Technique. The model and all associated 
-- documentation are proprietary to Synopsys, Inc. and may only be used 
-- pursuant to the terms and conditions of a written license agreement with 
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution 
-- of the Synopsys processor model or the associated  documentation is 
-- strictly prohibited. 
*/


#ifndef __clang__

#ifndef _STDARG_H
#define _STDARG_H

#include <stdint.h>

// This file describes a number of typical situations that may arise for
// processors developed with the Chess/Checkers tool suite. Select the
// situation as found on the target processor by defining STDARG_STACK_SCHEME
// to any of the following values:

// 0 : Stack growing up, one alignment
// 1 : Stack growing up, all alignments are a power of 2
// 2 : Stack growing up, any alignment
// 3 : Stack growing down (includes pseudo-static), one alignment
// 4 : Stack growing down (includes pseudo-static), all alignments are a power
//     of 2 
// 5 : Stack growing down (includes pseudo-static), any alignment

#define STDARG_STACK_SCHEME 1

typedef void* va_list;
// This assumes the stack to be on the default_memory.
// If not, or if there are multiple stacks, a pointer to a specific memory will
// have to be used.

inline void* chess_va_start() property(functional);
// To be extended in the upcoming support for multiple stacks.

#define va_start(va,parmN) (va) = chess_va_start()
// Note that the "last named (stack) argument" (parmN) is NOT used in Chess,
// though it may be required for native compilation.
// Chess does not require any named arguments, or if there are, these may all
// be passed via registers.  The presence of ... variable arguments does not
// affect the argument passing of named arguments (which may in turn be
// annotated as required).

#define va_copy(d,s) (d) = (s);

#define va_end(va) (void)0

#ifndef STDARG_STACK_SCHEME
#error "STDARG_STACK_SCHEME not defined"
#endif

// Accessing the "next" variable argument depends on how the stack is
// organised; in particular growing up or down (incl. pseudo-static).
// In general alignment constraints must be met, but often these can be
// simplified:
// - nothing at all if there's only one alignment on the stack
//   (usually but not necessarily 1);
// - simple masking if all possible alignments are powers of 2
//   (note that negating the alignment directly gives the appropriate mask);
// - modulo calculations are very rarely needed.

// Requires the type `uintptr_t' which can hold and manipulate pointer values.


// STACK GROWING UP -- sp_location : free (or top possibly -N)
//  stack offsets are negative
//  va_start points at the lowest named argument (if any)
//   and therefore above the highest actual variable argument
//  next va_arg is done by first aligning and decrementing the pointer,
//   only then can the object be accessed

// - one alignment:

#if STDARG_STACK_SCHEME == 0
#define va_arg(va,TT) (*(TT*)(va = (TT*)va - 1 ))
#endif

// - power of 2 alignment:

#if STDARG_STACK_SCHEME == 1
#define va_arg(va,TT) (*(TT*)(va = (TT*)((uintptr_t)va & -chess_alignof(TT)) - 1))
#endif

// - any alignment:

#if STDARG_STACK_SCHEME == 2
#define va_arg(va,TT) (*(TT*)(va = (TT*)((uintptr_t)va - (uintptr_t)va % chess_alignof(TT)) - 1))
#endif

// STACK GROWING DOWN -- sp_location : bottom (possibly +N) or pseudo-static
//  stack offsets are positive
//  va_start points above the highest named argument (if any)
//   and therefore at the lowest actual variable argument
//  next va_arg is done by first aligning the pointer, remembering the value
//   for accessing this object, then incrementing the pointer for the next

extern va_list chess_storage(chess_inline) _va_tmp;
// An ordinary inline function, declaring a local _va_tmp is also possible,
// but this advanced feature minimises the difference with the "up" version,
// e.g., it allows to continue using automaticly scaled (TT*) + 1, in stead
// of having to perform the sizeof(TT) explicitly as well.

// - one alignment:

#if STDARG_STACK_SCHEME == 3
#define va_arg(va,TT) (_va_tmp = va, \
			va = chess_dont_warn_dead((TT*)_va_tmp + 1), \
			*(TT*)_va_tmp)
#endif

// - power of 2 alignment:

#if STDARG_STACK_SCHEME == 4
#define va_arg(va,TT) (_va_tmp = (va_list)(((uintptr_t)va + chess_alignof(TT)-1) & -chess_alignof(TT)), \
			va = chess_dont_warn_dead((TT*)_va_tmp + 1), \
			*(TT*)_va_tmp)
#endif

// - any alignment:

#if STDARG_STACK_SCHEME == 5
#define va_arg(va,TT) (_va_tmp = (va_list)((uintptr_t)va % chess_alignof(TT) ? (uintptr_t)va + chess_alignof(TT) - (uintptr_t)va % chess_alignof(TT) : va), \
			va = chess_dont_warn_dead((TT*)_va_tmp + 1), \
			*(TT*)_va_tmp)
#endif

#endif /* stdarg.h */
#else
# include_next "stdarg.h"
#endif // __clang__
