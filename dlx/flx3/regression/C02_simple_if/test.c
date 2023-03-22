/*
-- Test conditional expressions (basic jump instructions).
--
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/




int greater(int a, int b)
{
    return a > b ? a + b : 3 * a;
}


int smaller(int a, int b)
{
    return a <= b ? a & b : a | b;
}


int main()
{
    chess_report( greater(11,44) );
    chess_report( greater(55,22) );
    chess_report( smaller(123,456) );
    chess_report( smaller(1024,255) );

    return 0;
}

