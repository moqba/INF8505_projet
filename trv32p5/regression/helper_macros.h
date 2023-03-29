/*
-- Helper macros's for regression tests.
--
-- Copyright (c) 2014-2020 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

// helper macro
#define CONCAT(a,b)  CONCAT_(a,b)
#define CONCAT_(a,b) a##b

// basic length of short
#if   (SHRT_NBIT==8)
#define SHRT_IMM(a) a
#elif (SHRT_NBIT==16)
#define SHRT_IMM(a) CONCAT(00,a)
#elif (SHRT_NBIT==32)
#define SHRT_IMM(a) CONCAT(000000,a)
#else
#error "SHRT_NBIT must be 8, 16 or 32"
#endif

// basic length of int
#if (INT_NBIT==16)
#define INT_4DIG_IMM(a) a
#elif (INT_NBIT==32)
#define INT_4DIG_IMM(a) CONCAT(0000,a)
#else
#error "INT_NBIT must be 16 or 32"
#endif

// endianess
#if   (__ENDIANNESS == __LITTLE_ENDIAN)
#define ENDIAN_CONCAT_SHRT(a,b) CONCAT(SHRT_IMM(a),SHRT_IMM(b))
//#define ENDIAN_CONCAT(a,b) CONCAT(a,b)
#elif (__ENDIANNESS == __BIG_ENDIAN)
#define ENDIAN_CONCAT_SHRT(a,b) CONCAT(SHRT_IMM(b),SHRT_IMM(a))
//#define ENDIAN_CONCAT(a,b) CONCAT(b,a)
#else
#error "__ENDIANNESS must be __LITTLE_ENDIAN or __BIG_ENDIAN"
#endif

// make it an hex immediate (prepend "0x")
#define HEXVAL(a)   CONCAT(CONCAT(0x,a),ULL)
#define DINT_HEX(a) CONCAT(0x,a)

// Number of shorts in a long
#if   (SHRT_NBIT*2 == LNG_NBIT)
#define LONG_ENDIAN_CONCAT_SHRT_1DIG(a) HEXVAL(ENDIAN_CONCAT_SHRT(CONCAT(2,a),CONCAT(1,a)))
#elif (SHRT_NBIT*4 == LNG_NBIT)
#define LONG_ENDIAN_CONCAT_SHRT_1DIG(a) HEXVAL(ENDIAN_CONCAT_SHRT(ENDIAN_CONCAT_SHRT(CONCAT(4,a),CONCAT(3,b)),ENDIAN_CONCAT_SHRT(CONCAT(2,a),CONCAT(1,b))))
#else
#error "short should fit 2 or 4 times in a long"
#endif

#define DINT_CONCAT_INT_4DIG(a,b) DINT_HEX(CONCAT(INT_4DIG_IMM(a),INT_4DIG_IMM(b)))
//#define UDINT_CONCAT_INT_4DIG(a,b) UDINT_HEX(ENDIAN_CONCAT(INT_4DIG_IMM(a),INT_4DIG_IMM(b)))

// Helpers to suppress certain compiler optimizations
#ifdef __chess__
  #ifdef __clang__
    // clang
    #define NEVER_INLINE __attribute__((noinline))
    #define ALWAYS_INLINE inline __attribute__((always_inline))
    ALWAYS_INLINE void clobber() { asm volatile("/**/" : : : "memory"); }
  #else
    // noodle
    #define NEVER_INLINE
    #define ALWAYS_INLINE inline
    ALWAYS_INLINE void clobber() { /* ??? */ }
  #endif
  #define UNKNOWN(x) (x) = chess_copy(x)
#else
  // native, no need to suppress optimizations
  #ifndef NEVER_INLINE
  #define NEVER_INLINE
  #endif

  #ifndef ALWAYS_INLINE
  #define ALWAYS_INLINE inline
  #endif

  #define UNKNOWN(x)

  ALWAYS_INLINE void clobber() {}

#endif

// Avoid that uninitialized regs are spilled as this gives ISS vs. RTL diffs
inline void init_regs() { }
