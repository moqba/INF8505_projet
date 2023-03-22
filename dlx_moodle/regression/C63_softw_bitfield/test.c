/*
-- Test bitfields with software bitfield extraction.
--
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/



struct BF1 {
    int   : 1;
    int a : 5;
    int   : 1;
    int b : 3;
};

extern "C++" int bf_add(int x, int y)
{
    BF1 bf0, bf1, bf2;
    bf1.a = x;
    bf1.b = y;
    return bf1.a + bf1.b;
}

extern "C++" void bf_set(BF1& bf, int x, int y)
{
    bf.a = x;
    bf.b = y;
}

extern "C++" int bf_add(BF1 bf)
{
    return bf.a + bf.b;
}

void test_BF1 ()
{
    chess_message("// test_BF1");

    chess_report(bf_add(6, 2));

    BF1 bf1;
    bf_set(bf1,  5,-3); chess_report(bf_add(bf1));
    bf_set(bf1, 15, 0); chess_report(bf_add(bf1));
    bf_set(bf1,-16, 0); chess_report(bf_add(bf1));
    bf_set(bf1,  0, 3); chess_report(bf_add(bf1));
    bf_set(bf1,  0,-4); chess_report(bf_add(bf1));
    bf_set(bf1, 16, 0); chess_report(bf_add(bf1)); // overflow
    bf_set(bf1,  0, 8); chess_report(bf_add(bf1)); // overflow
    bf_set(bf1, 16, 8); chess_report(bf_add(bf1)); // overflow
}



struct BF2 {
    unsigned   : 1;
    unsigned a : 5;
    unsigned   : 1;
    unsigned b : 3;
};

extern "C++" void bf_set(BF2& bf, int x, int y)
{
    bf.a = x;
    bf.b = y;
}

extern "C++" int bf_add(BF2 bf)
{
    return bf.a + bf.b;
}

void test_BF2 ()
{
    chess_message("// test_BF2");
    BF2 bf2;
    bf_set(bf2, 5, 0); chess_report(bf_add(bf2));
    bf_set(bf2, 0, 3); chess_report(bf_add(bf2));
    bf_set(bf2, 6, 4); chess_report(bf_add(bf2));
    bf_set(bf2,31, 7); chess_report(bf_add(bf2));
    bf_set(bf2,-1,-1); chess_report(bf_add(bf2));
}



struct BF3 {
    int a : 4;     // 1st word
    int b : 4;
    int c : 4;
    int d : 4;

    int e : 3;     // 2nd word
    int f : 8;
    int g : 4;

    int h : 4;     // 3rd word

    int   : 0;     // 4th word
    int i : 6;
    int j : 6;
};

BF3 gbf3;

// Reference is not supported on other than default memory
extern "C++" void bf_set(BF3& /*chess_storage(XYMEM)*/ bf)
{
    bf.a = 0;
    bf.b = 1;
    bf.c = 2;
    bf.d = 3;
    bf.e = 4;
    bf.f = 5;
    bf.g = 6;
    bf.h = 7;
    bf.i = 8;
    bf.j = 9;
}

extern "C++" int bf_add(BF3 bf)
{
    int r = 0;
    r += bf.a;
    r += bf.b;
    r += bf.c;
    r += bf.d;
    r += bf.e;
    r += bf.f;
    r += bf.g;
    r += bf.h;
    r += bf.i;
    r += bf.j;
    return r;
}


void test_BF3 ()
{
    chess_message("// test_BF3");
    BF3 bf3;
    static BF3 sbf3;
    bf_set( bf3); chess_report(bf_add( bf3));
    bf_set(sbf3); chess_report(bf_add(sbf3));
    bf_set(gbf3); chess_report(bf_add(gbf3));
}


struct SS {
    int a;
    int b : 5;
    unsigned c : 5;
    BF1 d;
    BF3 e;
    BF2 f;
};

void s_set(SS& s)
{
    s.a = 255;
    s.b = -4;
    s.c = 19;
    s.d.a = 2;
    s.d.b = 3;
    s.e.a = 1;
    s.e.b = -2;
    s.e.c = 3;
    s.e.d = -4;
    s.e.e = 5;
    s.e.f = -6;
    s.e.g = 7;
    s.e.h = -8;
    s.e.i = 9;
    s.e.j = -10;
    s.f.a = 25;
    s.f.b = 5;
}

int s_add(SS& s)
{
    int r = 0;
    r += s.a;
    r += s.b;
    r += s.c;
    r += s.d.a;
    r += s.d.b;
    r += s.e.a;
    r += s.e.b;
    r += s.e.c;
    r += s.e.d;
    r += s.e.e;
    r += s.e.f;
    r += s.e.g;
    r += s.e.h;
    r += s.e.i;
    r += s.e.j;
    r += s.f.a;
    r += s.f.b;
    return r;
}

void test_SS ()
{
    chess_message("// test_SS");
    SS s;
    s_set(s); chess_report(s_add(s));
}



int main()
{
    test_BF1();
    test_BF2();
    test_BF3();
    test_SS();
    return 0;
}
