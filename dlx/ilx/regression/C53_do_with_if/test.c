/*
-- Test: doloop reduction with nested (non-doloop) control
--
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/



void for_if(int n, int a, int b)
{
    chess_message("// for_if(" << n << ", " << a << ", " << b << ')');
    for (int i = 0; i < n; i++) {
        if (a < b) {
            a++;
        } else {
            b++;
        }
    }
    chess_report(a);
    chess_report(b);
}

void for2_if(int n, int m, int a, int b)
{
    chess_message("// for2_if(" << n << ", " << m << ", " << a << ", " << b << ')');
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a < b) {
                a++;
            } else {
                b++;
            }
        }
    }
    chess_report(a);
    chess_report(b);
}

void for3_if(int n, int m, int o, int a, int b)
{
    chess_message("// for3_if(" << n << ", " << m << ", " << o << ", "
                                << a << ", " << b << ')');
    for (int i = 0; i < n; i++)  {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < o; k++) {
                if (a < b) {
                    a++;
                } else {
                    b++;
                }
            }
        }
    }
    chess_report(a);
    chess_report(b);
}

void for_do(int m, int c)
{
    chess_message("// for_do(" << m << ", " << c << ')');
    for (int i = 0; i < 5; i++) {
        int x = m;
        do {
            chess_report(x);
            x--;
        } while (x > 0 && c == 1);
    }
}

void for_do_toggle(int c)
{
    chess_message("// for_do_toggle(" << c << ')');
    int x = 0;
    for (int i = 0; i < 5; i++) {
        do { ++x; } while (c = ~c);
    }
    chess_report(x);
}

int while1_break(int* p)
{
    chess_message("// while1_break");
    int x = 0;
    while (1) {
        if (*p++) break;
        x++;
    }
    return x;
}

int while1_return(int* p)
{
    chess_message("// while1_return");
    int x = 0;
    while (1) {
        if (*p++) return x;
        x++;
    }
    //dead
}

int if_while1_return(int c, int* p, int* q)
{
    chess_message("// if_while1_return(" << c << ')');
    int x = 0;
    if (c) {
        while (1) {
            if (*p++) return x;
            x++;
        }
    } else {
        while (1) {
            if (*q++) return x;
            x++;
        }
    }
    //dead
}

int one_forloop_output(int n)
{
    static int A[10] = { -100, 200, -50, 10, -5, 20, -25, 50, 100, -75 };

    chess_message("// one_forloop_output(" << n << ')');
    if (n < 1 || n > 8) // n must be in range [1,8]
        return -1;
    int t, i;
    for (i = 1; i <= n; i++) chess_loop_range(1, 8) chess_prepare_for_pipelining {
        t = A[i] + A[i+1];
    }
    chess_report(t);
    return t;
}

int two_forloop_outputs(int n)
{
    static int A[10] = { -100, 200, -50, 10, -5, 20, -25, 50, 100, -75 };

    chess_message("// two_forloop_outputs(" << n << ')');
    if (n < 2 || n > 8)   // n must be in range [2,8]
        return -1;
    int t, s, i;
    for (i = 1; i <= n; i++) chess_loop_range(2, 8) chess_prepare_for_pipelining {
        s = A[i] + i;
        t = A[i] + n;
        t += A[i + 1];
    }
    chess_report(t);
    chess_report(s);
    return t + s;
}

int AA[] = { 0, 0, 0, 1 };

int main()
{
    for_if(30, 10, 20);
    for2_if(5, 5, 10, 20);
    for3_if(5, 5,  5, 10, 20);

    for_do(4, 0);
    for_do(4, 1);

    for_do_toggle( 0);
    for_do_toggle(~0);

    chess_report(while1_break(AA));
    chess_report(while1_return(AA + 1));
    chess_report(if_while1_return(0, AA, AA + 2));
    chess_report(if_while1_return(1, AA, AA + 2));

    one_forloop_output(2);
    one_forloop_output(5);
    one_forloop_output(7);
    two_forloop_outputs(2);
    two_forloop_outputs(5);
    two_forloop_outputs(7);

    return 0;
}
