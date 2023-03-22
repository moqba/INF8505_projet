/*
-- Test function call mechanism.
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/


int foo(int a, int b) { return a + b; }

int pass(int i) { return i; }


int main()
{
    chess_report( foo(11,44) );
    chess_report( pass(77) );

    return 0;
}

