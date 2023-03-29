/*
-- Test structs.
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

struct two_ints  { int a, b;       };
struct four_ints { int a, b, c, d; };

// Add struct members with inline function
extern "C++" NEVER_INLINE int add(two_ints d)
{
    return d.a + d.b;
}

// Add struct members with called function
extern "C++" NEVER_INLINE int add(four_ints q)
{
    return q.a + q.b + q.c + q.d;
}


struct U1 {
    int i;
    two_ints d;
    four_ints q;
};

NEVER_INLINE void set_i(U1& u) {
    u.i = 10;
}
NEVER_INLINE void set_d(U1& u)
{
    u.d.a = 166;
    u.d.b = -66;
}
NEVER_INLINE void set_q(U1& u)
{
    u.q.a = 1000;
    u.q.b = 2020;
    u.q.c = 3003;
    u.q.d = 9000;
}

extern "C++" NEVER_INLINE int add(U1& u)
{
    int r = 0;
    r += u.i;
    r += u.d.a;
    r += u.d.b;
    r += u.q.a;
    r += u.q.b;
    r += u.q.c;
    r += u.q.d;
    return r;
}
extern "C++" NEVER_INLINE int add(U1* u)
{
    int r = 0;
    r += u->i;
    r += u->d.a;
    r += u->d.b;
    r += u->q.a;
    r += u->q.b;
    r += u->q.c;
    r += u->q.d;
    return r;
}

void test_U1()
{
    chess_message("// test_U1");

    static U1 u;
    set_i(u);
    set_d(u);
    set_q(u);
    chess_report(add(u));
    chess_report(add(u.d));
    chess_report(add(u.q));
    chess_report(add(&u));

    U1 v;
    set_i(v);
    set_d(v);
    set_q(v);
    chess_report(add(v));
    chess_report(add(v.d));
    chess_report(add(v.q));
    chess_report(add(&v));
}


union U2 {
    two_ints d;
    int i;
};

U2 uu = { 11, 22 };
U2 UU[4] = { { 1, 6 }, { 11, 16 }, { 101, 606 }, { 1111, 6666 } };

extern "C++" NEVER_INLINE int sum(U2& u)
{
    return u.d.a + u.d.b + u.i;
}
extern "C++" NEVER_INLINE int sum(U2 U[4])
{
    int r = 0;
    for (int i = 0; i < 4; ++i) {
        r += sum(U[i]);
    }
    return r;
}

void test_U2()
{
    chess_message("// test_U2");

    chess_report(sum(uu));
    chess_report(sum(UU));

    U2 vv;
    vv.d.a = UU[1].d.a;
    vv.d.b = UU[1].d.b;
    vv.i = -101;
    chess_report(sum(vv));
    chess_report(add(vv.d));

    U2 VV[2];
    VV[0].d.a = UU[1].d.a;
    VV[0].d.b = UU[1].d.b;
    VV[0].i = 444;
    VV[1].d.a = UU[3].d.a;
    VV[1].d.b = UU[3].d.b;
    VV[1].i = -555;
    chess_report(sum(VV[0]));
    chess_report(sum(VV[1]));
    chess_report(add(VV[0].d));
    chess_report(add(VV[1].d));
}


int main()
{
    test_U1();
    test_U2();
    return 0;
}
