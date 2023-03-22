/*
-- Test doloop reduction.
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/


#define N 16


void for_a(int n, int a, int b)
{
    chess_message( "// for_a(" << n << ',' << a << ',' << b << ')' );

    for (int i = 0; i < n; i++) {
        if (a < b)
            a++;
        else
            b++;
    }
    chess_report(a);
    chess_report(b);
}

void for_a(int n, int m, int a, int b)
{
    chess_message( "// for_a(" << n << ',' << m << ',' << a << ',' << b << ')' );

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a < b)
                a++;
            else
                b++;
        }
    }

    chess_report(a);
    chess_report(b);
}

void for_a(int n, int m, int o, int a, int b)
{
    chess_message( "// for_a(" << n << ',' << m << ',' << o << ','
            << a << ',' << b << ')' );

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < o; k++) {
                if (a < b)
                    a++;
                else
                    b++;
            }
        }
    }

    chess_report(a);
    chess_report(b);
}

// void for_b(int n, int m)
// {
//     chess_message( "// for_b(" << n << ',' << m << ')' );


//     for (int i = 0; i < n; i++) {
//         int x = m;
//         int y = m+1;
//         do {
//             chess_report(x);
//          x--;
//          y--;
//      } while (x > 0 && y > 0);
//     }
// }

void for_b(int n, int m, int c)
{
    chess_message( "// for_b(" << n << ',' << m << ')' );


    for (int i = 0; i < 5; i++) {
        int x = m;
        do {
            chess_report(x);
            x--;
        } while (x > 0 && c == 1);
    }
}


int main()
{
#ifdef CHESS_REGRESSION_INTERRUPTED
    dummy_isr_init();
#endif

    for_a(30,10,20);
    for_a(5,5,10,20);
    for_a(5,5,5,10,20);

    for_b(5,5,0);
    for_b(5,5,1);

    return 0;
}
