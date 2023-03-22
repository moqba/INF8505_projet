/*
-- Test reference casts.
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/


#if defined(__ndl__)
// Target procesor is big endian
#define X1 0x00110021
#define X2 0x00120022
#define X3 0x00130023
#else
// Host (x86) is little endian, so swap bits
#define X1 0x00210011
#define X2 0x00220012
#define X3 0x00230013
#endif


short test_union()
{
    union { long l; short i; } x;
    x.l = X1;
    return x.i;
}

short test_refcast()
{
    long l = X2;
    return (short&)l;
}

short test_refinit()
{
    long l = X3;
    short& i = (short&)l;
    return i;
}


int main()
{
    chess_report( test_union() );
    chess_report( test_refcast() );
    chess_report( test_refinit() );

    return 0;
}
