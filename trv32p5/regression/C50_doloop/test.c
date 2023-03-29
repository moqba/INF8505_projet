/*
-- Test doloop reduction.
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

#define N 260 // enough to prevent full loop unrolling

extern "C++" int dlp_do_ss(int x)
{
    chess_message("// dlp_do_ss(" << x << ')');
    UNKNOWN(x);

    int i;

    i = 0;
    do {
        i++;
        x++; UNKNOWN(x);
    } while (i < N);
    chess_report(x);

    i = N;
    do {
        i--;
        x++; UNKNOWN(x);
    } while (i > 0);
    chess_report(x);

    i = 0;
    do {
        i += 2;
        x++; UNKNOWN(x);
    } while (i <= N);
    chess_report(x);

    i = 0;
    do {
        i += 2;
        x++; UNKNOWN(x);
    } while (i <= N + 1);
    chess_report(x);

    i = N;
    do {
        i -= 3;
        x++; UNKNOWN(x);
    } while (i >= 0);
    chess_report(x);

    i = N + 1;
    do {
        i -= 3;
        x++; UNKNOWN(x);
    } while (i >= 0);
    chess_report(x);

    i = N + 2;
    do {
        i -= 3;
        x++; UNKNOWN(x);
    } while (i >= 0);
    chess_report(x);

    i = N + 3;
    do {
        i -= 3;
        x++; UNKNOWN(x);
    } while (i >= 0);
    chess_report(x);

    return x;
}

extern "C++" unsigned dlp_do_us(unsigned x)
{
    chess_message("// dlp_do_us(" << x << ')');
    UNKNOWN(x);
    unsigned i;

    i = 0;
    do {
        i++;
        x++; UNKNOWN(x);
    } while (i < N);
    chess_report(x);

    i = N;
    do {
        i--;
        x++; UNKNOWN(x);
    } while (i);
    chess_report(x);

    i = 0;
    do {
        i += 2;
        x++; UNKNOWN(x);
    } while (i <= N);
    chess_report(x);

    i = 0;
    do {
        i += 2;
        x++; UNKNOWN(x);
    } while (i <= N + 1);
    chess_report(x);

    i = N;
    do {
        i -= 2;
        x++; UNKNOWN(x);
    } while (i != 0);
    chess_report(x);

    return x;
}

extern "C++" int dlp_do_ss(int x, int start, int stop)
{
    chess_message("// dlp_do_ss(" << x << start << ", " << stop << ')');
    UNKNOWN(x); UNKNOWN(start); UNKNOWN(stop);
    int i;

    i = start;
    do {
        i++;
        x++; UNKNOWN(x);
    } while (i < stop);
    chess_report(x);

    i = start;
    do {
        i++;
        x++; UNKNOWN(x);
    } while (i <= stop);
    chess_report(x);

    i = stop;
    do {
        i--;
        x++; UNKNOWN(x);
    } while (i > start);
    chess_report(x);

    i = stop;
    do {
        i--;
        x++; UNKNOWN(x);
    } while (i >= start);
    chess_report(x);

    i = start;
    do {
        i += 4;
        x++; UNKNOWN(x);
    } while (i < stop);
    chess_report(x);

    return x;
}

extern "C++" int dlp_do_us(unsigned x, unsigned start, unsigned stop)
{
    chess_message("// dlp_do_us(" << x << start << ", " << stop << ')');
    UNKNOWN(x); UNKNOWN(start); UNKNOWN(stop);
    unsigned i;

    i = start;
    do {
        i++;
        x++; UNKNOWN(x);
    } while (i < stop);
    chess_report(x);

    i = start;
    do {
        i++;
        x++; UNKNOWN(x);
    } while (i <= stop);
    chess_report(x);

    i = stop;
    do {
        i--;
        x++; UNKNOWN(x);
    } while (i > start);
    chess_report(x);

    i = stop;
    do {
        i--;
        chess_report(i);
        x++; UNKNOWN(x);
    } while (i > start);
    chess_report(x);

    i = start;
    do {
        i += 4;
        x++; UNKNOWN(x);
    } while (i < stop);
    chess_report(x);

    return x;
}

extern "C++" int dlp_while(int x)
{
    chess_message("// dlp_while(" << x << ')');
    UNKNOWN(x);
    int i;

    i = 0;
    while (i < N) {
        i++;
        x++; UNKNOWN(x);
    }
    chess_report(x);

    i = N;
    while (i > 0) {
        i--;
        x++; UNKNOWN(x);
    }
    chess_report(x);

    i = 0;
    while (i <= N) {
        i += 2;
        x++; UNKNOWN(x);
    }
    chess_report(x);

    i = 0;
    while (i <= N + 1) {
        i += 2;
        x++; UNKNOWN(x);
    }
    chess_report(x);

    i = N;
    while (i >= 0) {
        i -= 3;
        x++; UNKNOWN(x);
    }
    chess_report(x);

    i = N + 1;
    while (i >= 0) {
        i -= 3;
        x++; UNKNOWN(x);
    }
    chess_report(x);

    i = N + 2;
    while (i >= 0) {
        i -= 3;
        x++; UNKNOWN(x);
    }
    chess_report(x);

    i = N + 3;
    while (i >= 0) {
        i -= 3;
        x++; UNKNOWN(x);
    }
    chess_report(x);

    return x;
}

extern "C++" int dlp_while(int x, int start, int stop)
{
    chess_message("// dlp_while(" << x << ", " << start << ", " << stop << ')');
    UNKNOWN(x); UNKNOWN(start); UNKNOWN(stop);
    int i;

    i = start;
    while (i < stop) {
        i++;
        x++; UNKNOWN(x);
    }
    chess_report(x);

    i = start;
    while (i <= stop) {
        i++;
        x++; UNKNOWN(x);
    }
    chess_report(x);

    i = stop;
    while (i > start) {
        i--;
        x++; UNKNOWN(x);
    }
    chess_report(x);

    i = stop;
    while (i >= start) {
        i--;
        x++; UNKNOWN(x);
    }
    chess_report(x);

    i = start;
    while (i < stop) {
        i += 4;
        x++; UNKNOWN(x);
    }
    chess_report(x);

    return x;
}

extern "C++" int dlp_for(int x)
{
    chess_message("// dlp_for(" << x << ')');
    UNKNOWN(x);

    for (int i = 0; i < N; i++) {
        x++; UNKNOWN(x);
    }
    chess_report(x);

    for (int i = N; i > 0; i--) {
        x++; UNKNOWN(x);
    }
    chess_report(x);

    for (int i = 0; i <= N; i += 2) {
        x++; UNKNOWN(x);
    }
    chess_report(x);

    for (int i = 0; i <= N + 1; i += 2) {
        x++; UNKNOWN(x);
    }
    chess_report(x);

    for (int i = N; i >= 0; i -= 3) {
        x++; UNKNOWN(x);
    }
    chess_report(x);

    for (int i = N + 1; i >= 0; i -= 3) {
        x++; UNKNOWN(x);
    }
    chess_report(x);

    for (int i = N + 2; i >= 0; i -= 3) {
        x++; UNKNOWN(x);
    }
    chess_report(x);

    for (int i = N + 3; i >= 0; i -= 3) {
        x++; UNKNOWN(x);
    }
    chess_report(x);

    return x;
}

extern "C++" int dlp_for(int x, int start, int stop)
{
    chess_message("// dlp_for(" << x << ", " << start << ", " << stop << ')');
    UNKNOWN(x); UNKNOWN(start); UNKNOWN(stop);

    for (int i = start; i < stop; i++) {
        x++; UNKNOWN(x);
    }
    chess_report(x);

    for (int i = start; i <= stop; i++) {
        x++; UNKNOWN(x);
    }
    chess_report(x);

    for (int i = stop; i > start; i--) {
        x++; UNKNOWN(x);
    }
    chess_report(x);

    for (int i = stop; i >= start; i--) {
        x++; UNKNOWN(x);
    }
    chess_report(x);

    for (int i = start; i < stop; i += 4) {
        x++; UNKNOWN(x);
    }
    chess_report(x);

    return x;
}

int dlp_nest_2(int x, int i_start, int i_stop, int j_start, int j_stop)
{
    chess_message("// dlp_nest_2(" << x     << ", " <<
            i_start << ", " << i_stop << ", " <<
            j_start << ", " << j_stop << ')');
    UNKNOWN(x);
    UNKNOWN(i_start); UNKNOWN(i_stop);
    UNKNOWN(j_start); UNKNOWN(j_stop);

    for (int i = i_start; i < i_stop; ++i) {
        for (int j = j_start; j < j_stop; ++j) {
            x++; UNKNOWN(x);
        }
        x += 123; UNKNOWN(x);
    }
    chess_report(x);
    return x;
}

int dlp_nest_3(int x,
        int i_start, int i_stop,
        int j_start, int j_stop,
        int k_start, int k_stop)
{
    chess_message("// dlp_nest_2(" << x     << ", " <<
            i_start << ", " << i_stop << ", " <<
            j_start << ", " << j_stop << ", " <<
            k_start << ", " << k_stop << ')');
    UNKNOWN(x);
    UNKNOWN(i_start); UNKNOWN(i_stop);
    UNKNOWN(j_start); UNKNOWN(j_stop);
    UNKNOWN(k_start); UNKNOWN(k_stop);

    for (int i = i_start; i < i_stop; ++i) {
        for (int j = j_start; j < j_stop; ++j) {
            for (int k = k_start; k < k_stop; ++k) {
                x++; UNKNOWN(x);
            }
            x += 13; UNKNOWN(x);
        }
        x += 577; UNKNOWN(x);
    }
    chess_report(x);
    return x;
}

int main()
{
    dlp_do_ss(1000);
    dlp_do_us(1000);

    dlp_do_ss(1100, 10, 20);
    dlp_do_ss(1200,  0,  1);
    dlp_do_ss(1400,-20,-15);

    dlp_do_us(1100, 10, 20);
    dlp_do_us(1200,  0,  1);

    dlp_while(2000);
    dlp_while(2100, 10, 20);
    dlp_while(2200,  0,  1);
    dlp_while(2300,  1,  0);
    dlp_while(2400,-20,-15);

    dlp_for(3000);
    dlp_for(3100, 10, 20);
    dlp_for(3200,  0,  1);
    dlp_for(3300,  1,  0);
    dlp_for(3400,-20,-15);

    dlp_nest_2(1000, 0, 1,  0,  1);
    dlp_nest_2(1000, 4, 6, 10, 20);

    dlp_nest_3(1000, 0, 1, 2, 3, 4,  5);
    dlp_nest_3(1000, 0, 2, 4, 6, 8, 10);
    return 0;
}
