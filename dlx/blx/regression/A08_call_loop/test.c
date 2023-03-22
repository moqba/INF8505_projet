/*
-- Test call instructions at the end of a hardware loop.
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/


// NO HWDO
void test_cl_doi(){
        chess_message( "// test_cl_doi()" );
        chess_report(42);
        chess_report(43);
        chess_report(46);
        chess_report(47);
        chess_report(50);
        chess_report(51);
        chess_report(52);
}
inline void test_clid_doi()
{
        chess_message( "// test_clid_doi()" );
        chess_report(42);
        chess_report(47);
        chess_report(50);
        chess_report(55);
        chess_report(56);
 }


int main()
{
    test_cl_doi();
    test_clid_doi();
    return 0;
}
