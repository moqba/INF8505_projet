/*
-- Test jump instructions at the end of a hardware loop.
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/



// ASIP has no HWDO
inline void test_cl_doi()
{
        chess_message( "// test_cl_doi()" );
        chess_report(43);
        chess_report(47);
        chess_report(51);
        chess_report(52);
}

int main()
{
    test_cl_doi();
    return 0;
}
