/*
-- Test bitfields with software bitfield extraction.
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/


//-----------------------------------------------------------------------------


struct BF1 {
    int   : 1;
    int a : 5;
    int   : 1;
    int b : 3;
};


int bf_add(int x, int y)
{
    BF1 bf0, bf1, bf2;
    bf1.a = x;
    bf1.b = y;
    return bf1.a + bf1.b;
}


void  bf_set(BF1& bf, int x, int y)
{
    bf.a = x;
    bf.b = y;
}


int bf_add(BF1 bf)
{
    return bf.a + bf.b;
}


void test_BF1 ()
{
    chess_message( "// test_BF1" );

    chess_report( bf_add(6,2) );

    BF1 bf1;

    bf_set(bf1,5,-3);
    chess_report( bf_add(bf1) );

    bf_set(bf1,15,0);
    chess_report( bf_add(bf1) );

    bf_set(bf1,-16,0);
    chess_report( bf_add(bf1) );

    bf_set(bf1,0,3);
    chess_report( bf_add(bf1) );

    bf_set(bf1,0,-4);
    chess_report( bf_add(bf1) );

    bf_set(bf1,16,0);     // overflow
    chess_report( bf_add(bf1) );

    bf_set(bf1,0,8);      // overflow
    chess_report( bf_add(bf1) );

    bf_set(bf1,16,8);     // overflow
    chess_report( bf_add(bf1) );
}


//-----------------------------------------------------------------------------


struct BF2 {
    unsigned   : 1;
    unsigned a : 5;
    unsigned   : 1;
    unsigned b : 3;
};


void  bf_set(BF2& bf, int x, int y)
{
    bf.a = x;
    bf.b = y;
}


int bf_add(BF2 bf)
{
    return bf.a + bf.b;
}


void test_BF2 ()
{
    chess_message( "// test_BF2" );

    BF2 bf2;

    bf_set(bf2,5,0);
    chess_report( bf_add(bf2) );

    bf_set(bf2,0,3);
    chess_report( bf_add(bf2) );

    bf_set(bf2,6,4);
    chess_report( bf_add(bf2) );

    bf_set(bf2,31,7);
    chess_report( bf_add(bf2) );

    bf_set(bf2,-1,-1);
    chess_report( bf_add(bf2) );
}


//-----------------------------------------------------------------------------


struct BF3 {
    int a : 4;     // first word
    int b : 4;
    int c : 4;
    int d : 4;

    int e : 3;     // second word
    int f : 8;
    int g : 4;

    int h : 4;     // third word

    int   : 0;     // fourth word
    int i : 6;
    int j : 6;
};


void bf_set(BF3& bf)
{
                   chess_separator();
    bf.a = 0;      chess_separator();
    bf.b = 1;      chess_separator();
    bf.c = 2;      chess_separator();
    bf.d = 3;      chess_separator();
    bf.e = 4;      chess_separator();
    bf.f = 5;      chess_separator();
    bf.g = 6;      chess_separator();
    bf.h = 7;      chess_separator();
    bf.i = 8;      chess_separator();
    bf.j = 9;      chess_separator();
}


int bf_add(BF3 bf)
{
    int r = 0;     chess_separator();
    r += bf.a;     chess_separator();
    r += bf.b;     chess_separator();
    r += bf.c;     chess_separator();
    r += bf.d;     chess_separator();
    r += bf.e;     chess_separator();
    r += bf.f;     chess_separator();
    r += bf.g;     chess_separator();
    r += bf.h;     chess_separator();
    r += bf.i;     chess_separator();
    r += bf.j;     chess_separator();
    return r;
}


BF3 gbf3;


void test_BF3 ()
{
    chess_message( "// test_BF3" );

    BF3 bf3;
    bf_set(bf3);
    chess_report( bf_add(bf3) );

    static BF3 sbf3;
    bf_set(sbf3);
    chess_report( bf_add(sbf3) );

    bf_set(gbf3);
    chess_report( bf_add(gbf3) );
}


//-----------------------------------------------------------------------------


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
                   chess_separator();
    s.a = 255;     chess_separator();
    s.b = -4;      chess_separator();
    s.c = 19;      chess_separator();
    s.d.a = 2;     chess_separator();
    s.d.b = 3;     chess_separator();
    s.e.a = 1;     chess_separator();
    s.e.b = -2;    chess_separator();
    s.e.c = 3;     chess_separator();
    s.e.d = -4;    chess_separator();
    s.e.e = 5;     chess_separator();
    s.e.f = -6;    chess_separator();
    s.e.g = 7;     chess_separator();
    s.e.h = -8;    chess_separator();
    s.e.i = 9;     chess_separator();
    s.e.j = -10;   chess_separator();
    s.f.a = 25;    chess_separator();
    s.f.b = 5;     chess_separator();
}


int s_add(SS& s)
{
    int r = 0;     chess_separator();
    r += s.a;      chess_separator();
    r += s.b;      chess_separator();
    r += s.c;      chess_separator();
    r += s.d.a;    chess_separator();
    r += s.d.b;    chess_separator();
    r += s.e.a;    chess_separator();
    r += s.e.b;    chess_separator();
    r += s.e.c;    chess_separator();
    r += s.e.d;    chess_separator();
    r += s.e.e;    chess_separator();
    r += s.e.f;    chess_separator();
    r += s.e.g;    chess_separator();
    r += s.e.h;    chess_separator();
    r += s.e.i;    chess_separator();
    r += s.e.j;    chess_separator();
    r += s.f.a;    chess_separator();
    r += s.f.b;    chess_separator();
    return r;
}


void test_SS ()
{
    chess_message( "// test_SS" );

    SS s;
    s_set(s);
    chess_report( s_add(s) );
}


//-----------------------------------------------------------------------------


int main()
{
    test_BF1();
    test_BF2();
    test_BF3();
    test_SS();

    return 0;
}
