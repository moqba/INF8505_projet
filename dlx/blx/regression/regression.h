/*
-- Regression parameters.
--
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/


// helper macros
#ifdef __chess__
#define ASIP_NATIVE(ASIP,NATIVE) ASIP
#else
#define ASIP_NATIVE(ASIP,NATIVE) NATIVE
#endif

#ifdef __chess__
#include "limits.h" // defines __ENDIANNESS
#else
//#include "endian.h"
//#define __ENDIANNESS __BYTE_ORDER
// endian.h exists only on Linux
// But x86_64 is little endian:
#define __LITTLE_ENDIAN        1234
#define __BIG_ENDIAN        4321
#define __ENDIANNESS    __LITTLE_ENDIAN
#endif

// regression parameters for blx (a 32-bit core)

// Available types
#define HAS_CHAR
#define HAS_SHORT
#define HAS_INT
#define HAS_LONG
#define HAS_LONG_LONG

// integers type parameters (natural size of the ASIP; typically int).
#define INT_        int
#define INT_X0AAA   0x0aaaaaaa
#define INT_X8000   0x80000000 /*SINT_MIN*/
#define INT_X7FFF   0x7fffffff /*SINT_MAX*/
#define INT_XFFFF   0xffffffff /*UINT_MAX*/
#define INT_X1000   0x10000000
#define INT_XCDEF   0xFCFDFEFF
#define INT_X3210   0x03020100
#define INT_NBIT    32
#define INT_MAXSH   31

#define INT_SE(a)   (a)
#define INT_ZE(a)   (a)

// "double int" type parameters (twice the natual size of the ASIP; typically long or long long).
#define DINT_        long long
#define DINT_SSUFFIX  LL
#define DINT_USUFFIX ULL
#define DINT_X0AAA   0x0aaaaaaaaaaaaaaaLL
#define DINT_X8000   0x8000000000000000LL /*SDINT_MIN*/
#define DINT_X7FFF   0x7fffffffffffffffLL /*SDINT_MAX*/
#define DINT_XFFFF   0xffffffffffffffffLL /*UDINT_MAX*/
#define DINT_X1000   0x1000000000000000LL
#define DINT_NBIT    64
#define DINT_MAXSH   63
#define DINT_SE(a)   (a)
#define DINT_ZE(a)   (a)

// char type parameters
#ifdef HAS_CHAR
#define CHAR_NBIT   8
#define CHAR_ZE(a)  (a)
#define CHAR_SE(a)  (a)
#define CHAR_X8000  0x80 /*SCHAR_MIN*/
#define CHAR_X7FFF  0x7f /*SCHAR_MAX*/
#define CHAR_XFFFF  0xff /*UCHAR_MAX*/

#if (CHAR_NBIT<=8)
    #define CHAR_TST_T char
#else
    #define CHAR_TST_T int
#endif

#endif

// short type parameters
#ifdef HAS_SHORT
#define SHRT_NBIT   16
#define SHRT_ZE(a)  (a)
#define SHRT_SE(a)  (a)
#define SHRT_X8000  0x8000 /*SSHRT_MIN*/
#define SHRT_X7FFF  0x7fff /*SSHRT_MAX*/
#define SHRT_XFFFF  0xffff /*USHRT_MAX*/
#endif

// long type parameters
#define LNG_        long
#define LNG_X0AAA   0x0aaaaaaa
#define LNG_X8000   0x80000000 /*SLNG_MIN*/
#define LNG_X7FFF   0x7fffffff /*SLNG_MAX*/
#define LNG_XFFFF   0xffffffff /*ULNG_MAX*/
#define LNG_X1000   0x10000000
#define LNG_NBIT    32
#define LNG_MAXSH   31
#define LNG_SE(a)   (a)
#define LNG_ZE(a)   (a)

// long long type parameters
#ifdef HAS_LONG_LONG
#define LLNG_NBIT   64
#define LLNG_ZE(a)  (a)
#define LLNG_SE(a)  (a)
#define LLNG_X8000  0x8000000000000000LL /*SLLNG_MIN*/
#define LLNG_X7FFF  0x7fffffffffffffffLL /*SLLNG_MAX*/
#define LLNG_XFFFF  0xffffffffffffffffLL /*ULLNG_MAX*/
#endif

// Avoid that uninitialized regs are spilled as this gives ISS vs. RTL diffs
inline void init_regs() { }
