/*
-- Test aggregate initializers.
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

void* escape_ptr;

#ifdef HAS_CHAR
char test_sc()
{
    const int n = 5;
    static char A[n] = { 10, -50, 75, -10, 5 };
    escape_ptr = A; clobber();
    char t = 0;
    for (int i = 0; i < n; ++i) {
        t += A[i];
    }
    return t;
}
unsigned char test_uc()
{
    const int n = 5;
    static unsigned char A[n] = { 100, 50, 25, 10, 5 };
    escape_ptr = A; clobber();
    unsigned char t = 0;
    for (int i = 0; i < n; ++i) {
        t += A[i];
    }
    return t;
}
#endif

#ifdef HAS_SHORT
short test_ss()
{
    const int n = 5;
    static short A[n] = { 100, -50, 25, -10, 5 };
    escape_ptr = A; clobber();
    short t = 0;
    for (int i = 0; i < n; ++i) {
        t += A[i];
    }
    return t;
}
unsigned short test_us()
{
    const int n = 5;
    static unsigned short A[n] = { 100, 50, 25, 10, 5 };
    escape_ptr = A; clobber();
    unsigned short t = 0;
    for (int i = 0; i < n; ++i) {
        t += A[i];
    }
    return t;
}
#endif

#ifdef HAS_INT
int test_si()
{
    const int n = 5;
    static int A[n] = { -100, 200, -50, 10, -5 };
    escape_ptr = A; clobber();
    int t = 0;
    for (int i = 0; i < n; ++i) {
        t += A[i];
    }
    return t;
}
unsigned test_ui()
{
    const int n = 5;
    static unsigned A[n] = { 100, 200, 1000, 10000, 20000 };
    escape_ptr = A; clobber();
    unsigned t = 0;
    for (int i = 0; i < n; ++i) {
        t += A[i];
    }
    return t;
}
#endif

#ifdef HAS_LONG
long test_sl()
{
    const int n = 5;
    static long A[n] = { -10000, 20000, 1000, -5555, 5 };
    escape_ptr = A; clobber();
    long t = 0;
    for (int i = 0; i < n; ++i) {
        t += A[i];
    }
    return t;
}
unsigned long test_ul()
{
    const int n = 5;
    static unsigned long A[n] = { 5000, 20000, 1000, 5555, 5 };
    escape_ptr = A; clobber();
    unsigned long t = 0;
    for (int i = 0; i < n; ++i) {
        t += A[i];
    }
    return t;
}
#endif

#ifdef HAS_LONG_LONG
long long test_sll()
{
    const int n = 5;
    static long long A[n] = { -10000, 20000, 1000, -5555, 5 };
    escape_ptr = A; clobber();
    long long t = 0;
    for (int i = 0; i < n; ++i) {
        t += A[i];
    }
    return t;
}
unsigned long long test_ull()
{
    const int n = 5;
    static unsigned long long A[n] = { 5000, 20000, 1000, 5555, 5 };
    escape_ptr = A; clobber();
    unsigned long long t = 0;
    for (int i = 0; i < n; ++i) {
        t += A[i];
    }
    return t;
}
#endif

int main()
{
#ifdef HAS_CHAR
    static char res_sc;
    res_sc = test_sc();
    chess_report(res_sc);
    static unsigned char res_uc;
    res_uc = test_uc();
    chess_report(res_uc);
#endif

#ifdef HAS_SHORT
    static short res_ss;
    res_ss = test_ss();
    chess_report(res_ss);
    static unsigned short res_us;
    res_us = test_us();
    chess_report(res_us);
#endif

#ifdef HAS_INT
    static int res_si;
    res_si = test_si();
    chess_report(res_si);
    static unsigned res_ui;
    res_ui = test_ui();
    chess_report(res_ui);
#endif

#ifdef HAS_LONG
    static long res_sl;
    res_sl = test_sl();
    chess_report(res_sl);
    static unsigned long res_ul;
    res_ul = test_ul();
    chess_report(res_ul);
#endif

#ifdef HAS_LONG_LONG
    static long long res_sll;
    res_sll = test_sll();
    chess_report(res_sll);
    static unsigned long long res_ull;
    res_ull = test_ull();
    chess_report(res_ull);
#endif
    return 0;
}
