/*
-- Test pointer arithmetic.
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/



struct SS { short a, b, c, d, e, f; };

SS ss[4];

void ptr_comparison(SS* p, SS* q)
{
    chess_message( "// ptr_comparison" );

    chess_report( p == q ? 100 : 101 );
    chess_report( p <  q ? 110 : 111 );
    chess_report( p >  q ? 120 : 121 );
    chess_report( p <= q ? 130 : 131 );
    chess_report( p >= q ? 140 : 141 );
    chess_report( p != q ? 150 : 151 );
}


int main()
{
    SS* p1 = &ss[1];
    SS* p3 = &ss[3];

 // chess_report( (int)(sizeof(SS)) );
 // chess_report( (int)((unsigned)p3 - (unsigned)p1) );
 // chess_report( (int)((void*)p3 - (void*)p1) ); // illegal
    chess_report( (int)(p3 - p1) );               // sizeof(SS) == 3-1 == 2

    ptr_comparison(p1,p3);
    ptr_comparison(p1,p1);

    return 0;
}
