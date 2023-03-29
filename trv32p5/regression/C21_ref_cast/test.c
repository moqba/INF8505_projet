/*
-- Test reference casts.
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

// These #defines must be set externally (via always include or -D command line arguments)
// For instance when int is a 16-bit type on the ASIP:
//
// #define SHRT_NBIT    16
// #define LNG_NBIT     32
// #define __ENDIANNESS __LITTLE_ENDIAN

// The helper macro's help to define X1, X2 and X3 depending on endianness, size of short, number of shorts into a long


#define X1 LONG_ENDIAN_CONCAT_SHRT_1DIG(1)  /* eg: 0x00210011 */
#define X2 LONG_ENDIAN_CONCAT_SHRT_1DIG(2)  /* eg: 0x00210011 */
#define X3 LONG_ENDIAN_CONCAT_SHRT_1DIG(3)  /* eg: 0x00210011  */


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
