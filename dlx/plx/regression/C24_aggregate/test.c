/*
-- Test aggregate initializers.
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/


unsigned short test_us()
{
    const int n = 5;
    static unsigned short A[n] = { 100, 50, 25, 10, 5 };
    unsigned short t = 0;
    for (int i = 0; i<n; i++)
       t += A[i];
    return t;
}


int test_si()
{
    const int n = 5;
    static int A[n] = { -100, 200, -50, 10, -5 };
    int t = 0;
    for (int i = 0; i<n; i++)
       t += A[i];
    return t;
}


unsigned test_ui()
{
    const int n = 5;
    static unsigned A[n] = { 100, 200, 1000, 10000, 20000 };
    unsigned t = 0;
    for (int i = 0; i<n; i++)
       t += A[i];
    return t;
}


long test_sl()
{
    const int n = 5;
    static long long A[n] = { 100000LL, -200000LL, 10000000LL, -55555LL ,
    5LL };
    long t = 0;
    for (int i = 0; i<n; i++)
       t += A[i];
    return t;
}


unsigned long test_ul()
{
    const int n = 5;
    static unsigned long long A[n] = { 100000ULL, 200000ULL, 10000000ULL,
    55555ULL , 5ULL };
    unsigned long t = 0;
    for (int i = 0; i<n; i++)
       t += A[i];
    return t;
}


int main()
{
    static unsigned short res_us;
    res_us = test_us();
    chess_report( res_us );

    static int res_si;
    res_si = test_si();
    chess_report( res_si );

    static unsigned res_ui;
    res_ui = test_ui();
    chess_report( res_ui );

    static long res_sl;
    res_sl = test_sl();
    chess_report( res_sl );

    static unsigned long res_ul;
    res_ul = test_ul();
    chess_report( res_ul );

    return 0;
}
