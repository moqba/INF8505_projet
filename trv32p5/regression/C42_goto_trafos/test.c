/*
-- Test goto transformations.
--
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

#include "regression.h"

int forward(int k)
{
    chess_message("// forward(" << k << ')');
    UNKNOWN(k);
    int z = 0;
    if (k) goto L;
    z += 2;
L:  z += 3;
    chess_report(z);
    return z;
}

int backward(int k)
{
    chess_message("// backward(" << k << ')');
    UNKNOWN(k);
    int z = 0;
L:  z += 2;
    k--;
    if (k > 0) goto L;
    z += 3;
    chess_report(z);
    return z;
}

int nested_forward(int k)
{
    chess_message("// nested_forward(" << k << ')');
    UNKNOWN(k);
    int z = 0;
    {
        z += 10;
        if (k) goto L;
        z += 20;
    }
    z += 2;
    {
        z += 100;
L:      z += 200;
        z += 300;
    }
    chess_report(z);
    return z;
}

int nested_backward(int k)
{
    chess_message("// nested_backward(" << k << ')');
    UNKNOWN(k);
    int z = 0;
    {
L:      z += 100;
    }
    k--;
    {
        z += 200;
        if (k > 0) goto L;
        z += 300;
    }
    chess_report(z);
    return z;
}

int conditional_nested_forward(int k, int l)
{
    chess_message("// conditional_nested_forward(" << k << ", " << l << ')');
    UNKNOWN(k); UNKNOWN(l);
    int z = 0;
    if (k) {
        z += 100;
        goto L;
        z += 200; // dead code
    }
    z += 3;
    if (l) {
        z += 1000;
L:      z += 2000;
    }
    chess_report(z);
    return z;
}

int conditional_nested_backward(int k, int l)
{
    chess_message("// conditional_nested_backward(" << k << ", " << l << ')');
    UNKNOWN(k); UNKNOWN(l);
    int z = 0;
    if (k) {
        z += 100;
L:      z += 200;
    }
    l--;
    if (l) {
        z += 1000;
        goto L;
        z += 3000; // dead code
    }
    chess_report(z);
    return z;
}

int out_then(int k)
{
    chess_message("// out_then(" << k << ')');
    UNKNOWN(k);
    int z = 0;
    if (k) {
        goto L;
    } else {
        z += 12;
    }
    z += 333;
L:  z += 100;
    chess_report(z);
    return z;
}

int in_then(int k, int l)
{
    chess_message("// in_then(" << k << ", " << l << ')');
    UNKNOWN(k); UNKNOWN(l);
    int z = 0;
    if (k) goto L;
    z += 2;
    if (l) {
        z += 30;
L:      z += 40;
    } else {
        z += 200;
    }
    z += 5;
    chess_report(z);
    return z;
}

int out_double_then(int k, int l)
{
    chess_message("// out_double_then(" << k << ", " << l << ')');
    UNKNOWN(k); UNKNOWN(l);
    int z = 0;
    if (k) {
        if (l) {
            z += 100;
            goto L;
        } else {
            z += 200;
        }
    } else {
        z += 3000;
    }
    z += 2;
L:  z += 5;
    chess_report(z);
    return z;
}

int in_double_then(int k, int l, int m)
{
    chess_message("// in_double_then(" << k << ", " << l << ", " << m << ')');
    UNKNOWN(k); UNKNOWN(l); UNKNOWN(m);
    int z = 0;
    if (k) goto L;
    z += 2;
    if (l) {
        if (m) {
            z += 100;
L:          z += 200;
        } else {
            z += 3000;
        }
    } else {
        z += 400;
    }
    z += 5;
    chess_report(z);
    return z;
}

int out_else(int k, int l)
{
    chess_message("// out_else(" << k << ", " << l << ')');
    UNKNOWN(k); UNKNOWN(l);
    int z = 0;
    if (k) {
        z += 12;
    } else {
        if (l) goto L;
    }
    z += 333;
L:  z += 100;
    chess_report(z);
    return z;
}

int in_else(int k, int l)
{
    chess_message("// in_else(" << k << ", " << l << ')');
    UNKNOWN(k); UNKNOWN(l);
    int z = 0;
    if (k) goto L;
    z += 2;
    if (l) {
        z += 100;
    } else {
        z += 200;
L:      z += 300;
    }
    z += 5;
    chess_report(z);
    return z;
}

int out_double_else(int k, int l)
{
    chess_message("// out_double_else(" << k << ", " << l << ')');
    UNKNOWN(k); UNKNOWN(l);
    int z = 0;
    if (k) {
        z += 20;
    } else {
        if (l) {
            z += 200;
            goto L;
        } else {
            z += 300;
        }
    }
    z += 2;
L:  z += 5;
    chess_report(z);
    return z;
}

int in_double_else(int k, int l, int m)
{
    chess_message("// in_double_else(" << k << ", " << l << ", " << m << ')');
    UNKNOWN(k); UNKNOWN(l); UNKNOWN(m);
    int z = 0;
    if (k) goto L;
    z += 2;
    if (l) {
        z += 20;
    } else {
        if (m) {
            z += 100;
        } else {
            z += 200;
L:          z += 300;
        }
    }
    z += 5;
    chess_report(z);
    return z;
}

int four_way(int k, int l)
{
    chess_message("// four_way(" << k << ", " << l << ')');
    UNKNOWN(k); UNKNOWN(l);
    int z = 0;
    if (k) {
        z += 10;
    } else {
        if (l) {
            z += 20;
        } else {
            goto L;
        }
    }
    z += 2;
    if (k) {
        if (l) {
            z += 100;
        } else {
            z += 200;
L:          z += 300;
        }
    } else {
        z += 1000;
    }
    z += 5;
    chess_report(z);
    return z;
}

int then_else(int k, int l)
{
    chess_message("// then_else(" << k << ", " << l << ')');
    UNKNOWN(k); UNKNOWN(l);
    int z = 0;
    if (k) {
        z += 10;
        if (l) goto L;
        z += 20;
    } else {
        z += 300;
L:      z += 400;
    }
    z += 5;
    chess_report(z);
    return z;
}

int else_then(int k, int l)
{
    chess_message("// else_then(" << k << ", " << l << ')');
    UNKNOWN(k); UNKNOWN(l);
    int z = 0;
    if (k) {
        z += 10;
L:      z += 20;
        l--;
    } else {
        z += 100;
        if (l > 0) goto L;
        z += 200;
    }
    z += 5;
    chess_report(z);
    return z;
}

int out_do(int k, int l)
{
    chess_message("// out_do(" << k << ", " << l << ')');
    UNKNOWN(k); UNKNOWN(l);
    int z = 0;
    do {
        z += 100;
        if (k) goto L;
        z += 200;
    } while (l--);
    z += 3;
L:  z += 5;
    chess_report(z);
    return z;
}

int in_do(int k, int l)
{
    chess_message("// forward(" << k << ", " << l << ')');
    UNKNOWN(k); UNKNOWN(l);
    int z = 0;
    do {
        z += 10;
L:      z += 30;
        l--;
    } while (l > 0);
    l = 2;
    k--;
    z += 100;
    if (k) goto L;
    z += 5;
    chess_report(z);
    return z;
}

int out_while(int k, int l)
{
    chess_message("// out_while(" << k << ", " << l << ')');
    UNKNOWN(k); UNKNOWN(l);
    int z = 0;
    while (l--) {
        z += 10;
        if (k) goto L;
        z += 40;
    }
    z += 100;
L:  z += 5;
    chess_report(z);
    return z;
}

int in_while(int k, int l)
{
    chess_message("// in_while(" << k << ", " << l << ')');
    UNKNOWN(k); UNKNOWN(l);
    int z = 0;
    while (l > 0) {
        z += 10;
L:      z += 20;
        l--;
    }
    l = 2;
    k--;
    z += 100;
    if (k) goto L;
    z += 5;
    chess_report(z);
    return z;
}

int alternating_gotos(int a, int b, int c, int d, int e, int f)
{
    chess_message("// alternating_gotos(" <<
                  a << ", " << b << ", " << c << ", " <<
                  d << ", " << e << ", " << f << ')');
    UNKNOWN(a); UNKNOWN(b); UNKNOWN(c); UNKNOWN(d); UNKNOWN(e); UNKNOWN(f);

    int z = 0;
    if (a) goto L;
    z |= 0x001;
    if (b) goto K;
    z |= 0x002;
    if (c) goto L;
    z |= 0x004;
    if (d) goto K;
    z |= 0x008;
    if (e) goto L;
    z |= 0x010;
    if (f) goto K;
    z |= 0x020;
L:  z |= 0x100;
K:  z |= 0x400;
    chess_report(z);
    return z;
}

// split up calls to avoid amnesia from hanging
int alternating_gotos_A() { return alternating_gotos(1, 0, 0, 0, 0, 0); }
int alternating_gotos_B() { return alternating_gotos(0, 1, 0, 0, 0, 0); }
int alternating_gotos_C() { return alternating_gotos(0, 0, 1, 0, 0, 0); }
int alternating_gotos_D() { return alternating_gotos(0, 0, 0, 1, 0, 0); }
int alternating_gotos_E() { return alternating_gotos(0, 0, 0, 0, 1, 0); }
int alternating_gotos_F() { return alternating_gotos(0, 0, 0, 0, 0, 1); }
int alternating_gotos_G() { return alternating_gotos(0, 0, 0, 0, 0, 0); }
int alternating_gotos_H() { return alternating_gotos(0, 1, 0, 0, 1, 0); }

int multiple_gotos(int k, int l)
{
    chess_message("// multiple_gotos(" << k << ", " << l << ')');
    UNKNOWN(k); UNKNOWN(l);
    int z = 0;
    if (k) {
        z += 10;
        goto K;
    } else {
        z += 30;
    }
    z +=  50;
L:  z += 100;
    l--;
    if (k) {
        z += 1000;
        if (l) goto L;
    } else {
        z += 3000;
        if (l) goto L;
    }
K:  z += 5;
    chess_report(z);
    return z;
}

int goto_loop(int k, int l)
{
    chess_message("// goto_loop(" << k << ", " << l << ')');
    UNKNOWN(k); UNKNOWN(l);
    int z = 0;
    if (k) {
        z += 10;
        goto L;
    }
    z += 30;
    do {
L:      z += 100;
    } while (l--);
    z += 5;
    chess_report(z);
    return z;
}

int main()
{
    forward(0);
    forward(1);

    backward(0);
    backward(1);

    nested_forward(0);
    nested_forward(1);

    nested_backward(0);
    nested_backward(1);

    conditional_nested_forward(0, 0);
    conditional_nested_forward(0, 1);
    conditional_nested_forward(1, 0);
    conditional_nested_forward(1, 1);

    conditional_nested_backward(0, 1);
    conditional_nested_backward(1, 1);
    conditional_nested_backward(0, 4);
    conditional_nested_backward(1, 4);

    out_then(0);
    out_then(1);

    in_then(0, 0);
    in_then(0, 1);
    in_then(1, 0);
    in_then(1, 1);

    out_double_then(0, 0);
    out_double_then(0, 1);
    out_double_then(1, 0);
    out_double_then(1, 1);

    in_double_then(0, 0, 1);
    in_double_then(0, 0, 0);
    in_double_then(0, 1, 1);
    in_double_then(0, 1, 1);
    in_double_then(1, 0, 0);
    in_double_then(1, 0, 1);
    in_double_then(1, 1, 0);
    in_double_then(1, 1, 1);

    out_else(0, 0);
    out_else(0, 1);
    out_else(1, 0);
    out_else(1, 1);

    in_else(0, 0);
    in_else(0, 1);
    in_else(1, 0);
    in_else(1, 1);

    out_double_else(0, 0);
    out_double_else(0, 1);
    out_double_else(1, 0);
    out_double_else(1, 1);

    in_double_else(0, 0, 0);
    in_double_else(0, 0, 1);
    in_double_else(0, 1, 0);
    in_double_else(0, 1, 1);
    in_double_else(1, 0, 0);
    in_double_else(1, 0, 1);
    in_double_else(1, 1, 0);
    in_double_else(1, 1, 1);

    four_way(0, 0);
    four_way(0, 1);
    four_way(1, 0);
    four_way(1, 1);

    then_else(0, 0);
    then_else(0, 1);
    then_else(1, 0);
    then_else(1, 1);

    else_then(0, 1);
    else_then(1, 1);
    else_then(0, 4);
    else_then(1, 4);

    out_do(0, 0);
    out_do(1, 0);
    out_do(0, 4);
    out_do(1, 4);

    in_do(1, 1);
    in_do(1, 4);
    in_do(5, 1);
    in_do(5, 4);

    out_while(0, 0);
    out_while(1, 0);
    out_while(0, 4);
    out_while(1, 4);

    in_while(1, 1);
    in_while(1, 4);
    in_while(5, 1);
    in_while(5, 4);

    alternating_gotos_A();
    alternating_gotos_B();
    alternating_gotos_C();
    alternating_gotos_D();
    alternating_gotos_E();
    alternating_gotos_F();
    alternating_gotos_G();
    alternating_gotos_H();

    multiple_gotos(0, 1);
    multiple_gotos(1, 1);
    multiple_gotos(0, 4);
    multiple_gotos(1, 4);

    goto_loop(0, 0);
    goto_loop(0, 4);
    goto_loop(1, 0);
    goto_loop(1, 4);
    return 0;
}
