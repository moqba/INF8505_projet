/*
-- Test conversion expressions.
--
-- Copyright (c) 2014 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

// These #defines must be set externally (via always include or -D command line arguments)
//
// #define HAS_CHAR
// #define HAS_SHORT
// #define HAS_INT
// #define HAS_LONG
// #define HAS_LONG_LONG
// #define CHAR_NBIT       8

#include "regression.h"

#if defined(HAS_CHAR)
  #if (CHAR_NBIT <= 8)
    #define C_CONVERSIONS                       \
          signed char sc = a; chess_report(sc); \
        unsigned char uc = a; chess_report(uc);

  #else // (CHAR_NBIT <= 8)
    #ifdef __chess__
       #define SC_CONV_LARGE   signed char sc = a;   signed int si = sc; chess_report(si);
       #define UC_CONV_LARGE unsigned char uc = a; unsigned int ui = uc; chess_report(ui);
    #else
       #define SC_CONV_LARGE   signed int si = CHAR_SE(a); chess_report(si);
       #define UC_CONV_LARGE unsigned int ui = CHAR_ZE(a); chess_report(ui);
    #endif

    #define C_CONVERSIONS                                                          \
        int      b = CHAR_SE((int)     a);                                         \
        unsigned c = CHAR_ZE((unsigned)a);                                         \
        if ((b >= -128) && (b <= 127)) {   signed char sc = a; chess_report(sc); } \
        else                           {   SC_CONV_LARGE }                         \
        if ((c >= 0)    && (c <= 255)) { unsigned char uc = a; chess_report(uc); } \
        else                           {   UC_CONV_LARGE }
  #endif // (CHAR_NBIT<=8)
#else // HAS_CHAR
    #define C_CONVERSIONS
#endif

#ifdef HAS_SHORT
    #define S_CONVERSIONS                        \
          signed short ss = a; chess_report(ss); \
        unsigned short us = a; chess_report(us);
#else
    #define S_CONVERSIONS
#endif

#ifdef HAS_INT
    #define I_CONVERSIONS                      \
          signed int si = a; chess_report(si); \
        unsigned int ui = a; chess_report(ui);
#else
    #define I_CONVERSIONS
#endif

#ifdef HAS_LONG
    #define L_CONVERSIONS                       \
          signed long sl = a; chess_report(sl); \
        unsigned long ul = a; chess_report(ul);
#else
    #define L_CONVERSIONS
#endif

#ifdef HAS_LONG_LONG
    #define LL_CONVERSIONS                             \
          signed long long sll = a; chess_report(sll); \
        unsigned long long ull = a; chess_report(ull);
#else
    #define LL_CONVERSIONS
#endif


#define ALL_CONVERSIONS \
    C_CONVERSIONS \
    S_CONVERSIONS \
    I_CONVERSIONS \
    L_CONVERSIONS \
    LL_CONVERSIONS


#if defined(HAS_CHAR)
void cast_from_sgn_char(signed CHAR_TST_T a)
{
    chess_message("// cast_from_sgn_char(" << (int)a << ')');
    UNKNOWN(a);
    ALL_CONVERSIONS
}
void cast_from_uns_char(unsigned CHAR_TST_T a)
{
    chess_message("// cast_from_uns_char(" << (unsigned)a << ')');
    UNKNOWN(a);
    ALL_CONVERSIONS
}
#endif

#ifdef HAS_SHORT
void cast_from_sgn_short(signed short a)
{
    chess_message("// cast_from_sgn_short(" << a << ')');
    UNKNOWN(a);
    ALL_CONVERSIONS
}
void cast_from_uns_short(unsigned short a)
{
    chess_message("// cast_from_uns_short(" << a << ')');
    UNKNOWN(a);
    ALL_CONVERSIONS
}
#endif

#ifdef HAS_INT
void cast_from_sgn_int(signed int a)
{
    chess_message("// cast_from_sgn_int(" << a << ')');
    UNKNOWN(a);
    ALL_CONVERSIONS
}
void cast_from_uns_int(unsigned int a)
{
    chess_message("// cast_from_uns_int(" << a << ')');
    UNKNOWN(a);
    ALL_CONVERSIONS
}
#endif

#ifdef HAS_LONG
void cast_from_sgn_long(signed long a)
{
    chess_message("// cast_from_sgn_long(" << a << ')');
    UNKNOWN(a);
    ALL_CONVERSIONS
}
void cast_from_uns_long(unsigned long a)
{
    chess_message("// cast_from_uns_long(" << a << ')');
    UNKNOWN(a);
    ALL_CONVERSIONS
}
#endif

#ifdef HAS_LONG_LONG
void cast_from_sgn_long_long(signed long long a)
{
    chess_message("// cast_from_sgn_long_long(" << a << ')');
    UNKNOWN(a);
    ALL_CONVERSIONS
}
void cast_from_uns_long_long(unsigned long long a)
{
    chess_message("// cast_from_uns_long_long(" << a << ')');
    UNKNOWN(a);
    ALL_CONVERSIONS
}
#endif

int main()
{
#ifdef HAS_CHAR
    cast_from_sgn_char(                10 );
    cast_from_sgn_char(               -20 );
    cast_from_sgn_char(CHAR_SE(CHAR_X8000));
    cast_from_sgn_char(CHAR_SE(CHAR_X7FFF));
    cast_from_sgn_char(CHAR_SE(CHAR_XFFFF));

    cast_from_uns_char(                10 );
    cast_from_uns_char(                20 );
    cast_from_uns_char(CHAR_ZE(CHAR_X8000));
    cast_from_uns_char(CHAR_ZE(CHAR_X7FFF));
    cast_from_uns_char(CHAR_ZE(CHAR_XFFFF));
#endif

#ifdef HAS_SHORT
    cast_from_sgn_short(                10 );
    cast_from_sgn_short(               -20 );
    cast_from_sgn_short(SHRT_SE(SHRT_X8000));
    cast_from_sgn_short(SHRT_SE(SHRT_X7FFF));
    cast_from_sgn_short(SHRT_SE(SHRT_XFFFF));

    cast_from_uns_short(                10 );
    cast_from_uns_short(                20 );
    cast_from_uns_short(SHRT_ZE(SHRT_X8000));
    cast_from_uns_short(SHRT_ZE(SHRT_X7FFF));
    cast_from_uns_short(SHRT_ZE(SHRT_XFFFF));
#endif

#ifdef HAS_INT
    cast_from_sgn_int(              10 );
    cast_from_sgn_int(             -20 );
    cast_from_sgn_int(INT_SE(INT_X8000));
    cast_from_sgn_int(INT_SE(INT_X7FFF));
    cast_from_sgn_int(INT_SE(INT_XFFFF));

    cast_from_uns_int(              10 );
    cast_from_uns_int(              20 );
    cast_from_uns_int(INT_ZE(INT_X8000));
    cast_from_uns_int(INT_ZE(INT_X7FFF));
    cast_from_uns_int(INT_ZE(INT_XFFFF));
#endif

#ifdef HAS_LONG
    cast_from_sgn_long(              10 );
    cast_from_sgn_long(             -20 );
    cast_from_sgn_long(LNG_SE(LNG_X8000));
    cast_from_sgn_long(LNG_SE(LNG_X7FFF));
    cast_from_sgn_long(LNG_SE(LNG_XFFFF));

    cast_from_uns_long(              10 );
    cast_from_uns_long(              20 );
    cast_from_uns_long(LNG_ZE(LNG_X8000));
    cast_from_uns_long(LNG_ZE(LNG_X7FFF));
    cast_from_uns_long(LNG_ZE(LNG_XFFFF));
#endif

#ifdef HAS_LONG_LONG
    cast_from_sgn_long_long(                10 );
    cast_from_sgn_long_long(               -20 );
    cast_from_sgn_long_long(LLNG_SE(LLNG_X8000));
    cast_from_sgn_long_long(LLNG_SE(LLNG_X7FFF));
    cast_from_sgn_long_long(LLNG_SE(LLNG_XFFFF));

    cast_from_uns_long_long(                10 );
    cast_from_uns_long_long(                20 );
    cast_from_uns_long_long(LLNG_ZE(LLNG_X8000));
    cast_from_uns_long_long(LLNG_ZE(LLNG_X7FFF));
    cast_from_uns_long_long(LLNG_ZE(LLNG_XFFFF));
#endif
    return 0;
}
