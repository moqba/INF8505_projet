/*
-- Test Test long (> 128 and > 256) jumps.
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/



int jump_less_128(int n, int m, int x)
{
    chess_message( "// jump_less_128(" << n << ',' << m << ',' << x << ')' );

    if (n > 0) {

        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;

    }
    else  {

        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;

    }
    return m ? x : -x;
}

int jump_more_128(int n, int m, int x)
{
    chess_message( "// jump_more_128(" << n << ',' << m << ',' << x << ')' );

    if (n > 0) {

        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;

        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;

        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;

        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;

        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;

        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;

        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;

        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;
        x += 1; x &= 0xfff;

    }
    else  {

        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;

        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;

        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;

        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;

        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;

        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;

        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;

        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;
        x -= 1; x &= 0xfff;

    }
    return m ? x : -x;
}

int main()
{
#ifdef CHESS_REGRESSION_INTERRUPTED
    dummy_isr_init();
#endif

    chess_report( jump_less_128(10,1,1000) );
    chess_report( jump_less_128(-5,1,1000) );
    chess_report( jump_more_128(10,1,1000) );
    chess_report( jump_more_128(-5,1,1000) );

    return 0;
}
