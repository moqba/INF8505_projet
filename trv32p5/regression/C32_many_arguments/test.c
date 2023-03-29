/*
-- Test: pass arguments via registers and stack
--
-- Copyright (c) 2014 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

#include "regression.h"

// These #defines must be set externally (via always include or -D command line arguments)
//
// #define HAS_CHAR
// #define HAS_SHORT
// #define HAS_INT
// #define HAS_LONG
// #define HAS_LONG_LONG

//skip one arg (s|t|u) to create a difference

#ifndef DISABLE_PART1

#define TEST_FUNC(TYPE, SKIP)                                                                  \
NEVER_INLINE                                                                                   \
int TYPE##26(TYPE a, TYPE b, TYPE c, TYPE d, TYPE e, TYPE f, TYPE g, TYPE h, TYPE i, TYPE j,   \
             TYPE k, TYPE l, TYPE m, TYPE n, TYPE o, TYPE p, TYPE q, TYPE r, TYPE s, TYPE t,   \
             TYPE u, TYPE v, TYPE w, TYPE x, TYPE y, TYPE z)                                   \
{                                                                                              \
    return (int)a + b + c + d + e + f + g + h + i + j + k + l + m + n + o + p + q + r +        \
           (SKIP != 0 ? s : 0) + (SKIP != 1 ? t : 0) + (SKIP != 2 ? u : 0) +                   \
           (SKIP != 3 ? v : 0) + (SKIP != 4 ? w : 0) +                                         \
           x + y + z;                                                                          \
}                                                                                              \
void test_##TYPE##26()                                                                         \
{                                                                                              \
    chess_message("// test_"#TYPE"26");                                                        \
    chess_report(TYPE##26( 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,                              \
                          10, 11, 12, 13, 14, 15, 16, 17, 18, 19,                              \
                          20, 21, 22, 23, 24, 25));                                            \
}


#ifdef HAS_CHAR
TEST_FUNC(char, 0)
#endif

#ifdef HAS_SHORT
TEST_FUNC(short, 1)
#endif

#ifdef HAS_INT
TEST_FUNC(int, 2)
#endif

#ifdef HAS_LONG
TEST_FUNC(long, 3)
#endif

#ifdef HAS_LONG_LONG
typedef long long llong;
TEST_FUNC(llong, 4)
#endif

NEVER_INLINE
int ptr26(int* a, int* b, int* c, int* d, int* e, int* f, int* g, int* h,
          int* i, int* j, int* k, int* l, int* m, int* n, int* o, int* p,
          int* q, int* r, int* s, int* t, int* u, int* v, int* w, int* x,
          int* y, int* z)
{
    return *a + *b + *c + *d + *e + *f + *g +    *h +    *i + *j + *k + *l + *m +
           *n + *o + *p + *q + *r + *s + *t + /* *u + */ *v + *w + *x + *y + *z;
}
void test_ptr26()
{
    chess_message("// test_ptr26");
    static int A[] = {
         0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
        10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
        20, 21, 22, 23, 24, 25
    };
    chess_report(ptr26(A +  0, A +  1, A +  2, A +  3, A +  4, A +  5, A +  6, A +  7, A +  8, A +  9,
                       A + 10, A + 11, A + 12, A + 13, A + 14, A + 15, A + 16, A + 17, A + 18, A + 19,
                       A + 20, A + 21, A + 22, A + 23, A + 24, A + 25));
}


NEVER_INLINE
int mixed_int_ptr(int a, int b,
                  int* i, int* j, int* k, int* l, int* m, int* n, int* o, int* p,
                  int* q, int* r, int* s, int* t, int* u, int* v, int* w, int* x,
                  int* y, int* z,
                  int c, int d, int e)
{
    return a + *i + *p + *u + *z + d + e;
}
void test_mixed_int_ptr()
{
    chess_message("// test_mixed_int_ptr");

    int A[124]; // large stack frame
    A[ 10] =  100;
    A[ 20] =  200;
    A[ 30] =  300;
    A[ 40] =  400;
    A[ 50] =  500;
    A[ 60] =  600;
    A[ 70] =  700;
    A[ 80] =  800;
    A[ 90] =  900;
    A[100] = 1000;

    chess_report(mixed_int_ptr(0, 1,
                               A + 10, A +  20, A + 30, A + 40, A + 50, A + 60, A + 70, A + 80,
                               A + 10, A +  20, A + 30, A + 40, A + 50, A + 60, A + 70, A + 80,
                               A + 90, A + 100,
                               2, 3, 4));
}

#ifdef HAS_CHAR
typedef char      tst_char;
#else
typedef int       tst_char;
#endif

#ifdef HAS_SHORT
typedef short     tst_short;
#else
typedef int       tst_char;
#endif

#ifdef HAS_LONG
typedef long      tst_long;
#else
typedef int       tst_long;
#endif

#ifdef HAS_LONG_LONG
typedef long long tst_llong;
#else
typedef int       tst_llong;
#endif

NEVER_INLINE
tst_long mixed26(tst_char a, tst_char b, int c, int d, LNG_ e, tst_short f, int g, int h, int i, int j,
                 int k, tst_llong l, int m, int n, tst_llong o, int p, int* q, int r, tst_long *s, int t,
                 int u, int v, int w, tst_long x, int& y, int z)
{
    return a + b + c + d + e + f +  g + h +  i + j +
           k + l + m + n + o + p + *q + r + *s + t +
           u + v + w + x + y + z;
}
void test_mixed26()
{
    chess_message("// test_int26");
    int       y =  24;
    int       q = 230;
    tst_llong l = 432;
    tst_long  s = 102;
    chess_report(mixed26( 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
                         10,  l, 12, 13, 14, 15, &q, 17, &s, 19,
                         20, 21, 22, 23,  y, 25));
}
void test_mixed()
{
    test_mixed_int_ptr();
    test_mixed26();
}
#endif // DISABLE_PART1


void spill_registers() {}

int gi[12];
NEVER_INLINE
int gint14(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j,
           int k, int l, int m, int n)
{
    return a + b + c + d + e + f + g + h + i + j + k + l + m + n +
           gi[0] + gi[1] + gi[2] + gi[3] /* + gi[ 4]*/ + gi[5] +
           gi[6] + gi[7] + gi[8] + gi[9]    + gi[10]   + gi[11];
}
void test_gint14()
{
    chess_message("// test_gint14");

    gi[ 0] = 14; gi[ 1] = 15; gi[2] = 16; gi[3] = 17; gi[4] = 18;
    gi[ 5] = 19; gi[ 6] = 20; gi[7] = 21; gi[8] = 22; gi[9] = 23;
    gi[10] = 24; gi[11] = 25;

    chess_report(gint14(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13));
}

short gs[12];
NEVER_INLINE
short gshort14(short a, short b, short c, short d, short e, short f, short g, short h, short i, short j,
               short k, short l, short m, short n)
{
    spill_registers();
    return a + b + c + d + e + f + g + h + i + j + k + l + m + n +
           gs[0] + gs[1] + gs[2] + gs[3] + gs[ 4] /* + gs[5] */ +
           gs[6] + gs[7] + gs[8] + gs[9] + gs[10]    + gs[11];
}
void test_gshort14()
{
    chess_message("// test_gshort14");

    gs[ 0] = 14; gs[ 1] = 15; gs[2] = 16; gs[3] = 17; gs[4] = 18;
    gs[ 5] = 19; gs[ 6] = 20; gs[7] = 21; gs[8] = 22; gs[9] = 23;
    gs[10] = 24; gs[11] = 25;

    chess_report(gshort14(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13));
}

int* gp[20];
NEVER_INLINE
int gptr6(int* a, int* b, int* c, int* d, int* e, int* f)
{
    spill_registers(); // will introduce spilling of argument registers
    return *a + *b + *c + *d + *e + *f +
           *gp[ 0] + *gp[ 1] + *gp[ 2] + *gp[ 3] +   *gp[ 4] +
           *gp[ 5] + *gp[ 6] + *gp[ 7] + *gp[ 8] +   *gp[ 9] +
           *gp[10] + *gp[11] + *gp[12] + *gp[13] + /**gp[14] +*/
           *gp[15] + *gp[16] + *gp[17] + *gp[18] +   *gp[19];
}
void test_gptr6()
{
    chess_message("// test_gptr6");

    static int A[] = {
         0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
        10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
        20, 21, 22, 23, 24, 25
    };

    gp[ 0] = A +  6; gp[ 1] = A +  7; gp[ 2] = A +  8; gp[ 3] = A +  9; gp[ 4] = A + 10;
    gp[ 5] = A + 11; gp[ 6] = A + 12; gp[ 7] = A + 13; gp[ 8] = A + 14; gp[ 9] = A + 15;
    gp[10] = A + 16; gp[11] = A + 17; gp[12] = A + 18; gp[13] = A + 19; gp[14] = A + 20;
    gp[15] = A + 21; gp[16] = A + 22; gp[17] = A + 23; gp[18] = A + 24; gp[19] = A + 25;

    chess_report(gptr6(A + 0, A + 1, A + 2, A + 3, A + 4, A + 5));
}

int gmi[3];
int* gmp[13];
NEVER_INLINE
short gmixed(int a, int b, int* i, int* j, int* k, int* l, int* m)
{
    return a + *i + *gmp[2] + *gmp[7] + *gmp[12] + gmi[1] + gmi[2];
}
void test_gmixed()
{
    chess_message("// test_gmixed");

    int A[124]; // large stack frame
    A[ 10] =  100;
    A[ 20] =  200;
    A[ 30] =  300;
    A[ 40] =  400;
    A[ 50] =  500;
    A[ 60] =  600;
    A[ 70] =  700;
    A[ 80] =  800;
    A[ 90] =  900;
    A[100] = 1000;

    gmp[ 0] = A + 60; gmp[ 1] = A + 70; gmp[ 2] = A + 80; gmp[3] = A + 10; gmp[4] = A + 20;
    gmp[ 5] = A + 30; gmp[ 6] = A + 40; gmp[ 7] = A + 50; gmp[8] = A + 60; gmp[9] = A + 70;
    gmp[10] = A + 80; gmp[11] = A + 90; gmp[12] = A + 100;

    gmi[0] = 2; gmi[1] = 3; gmi[2] = 4;

    chess_report(gmixed(0, 1, A + 10, A + 20, A + 30, A + 40, A + 50));
}


int main()
{
#ifndef DISABLE_PART1
    #ifdef HAS_CHAR
    test_char26();
    #endif

    #ifdef HAS_SHORT
    test_short26();
    #endif

    #ifdef HAS_INT
    test_int26();
    #endif

    #ifdef HAS_LONG
    test_long26();
    #endif

    #ifdef HAS_LONG_LONG
    test_llong26();
    #endif

    test_ptr26();
    test_mixed();
#endif

    test_gint14();
    test_gshort14();
    test_gptr6();
    test_gmixed();
    return 0;
}
