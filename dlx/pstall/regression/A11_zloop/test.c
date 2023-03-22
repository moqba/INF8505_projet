/*
-- Test hardware zloop instructions.
-- Copyright (c) 2019-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/


#include "dlx_define.h"

inline void test_zlp1()
{
        chess_message( "// test_zlp1()" );
        chess_report(13);
        chess_report(15);
        chess_report(17);
        chess_report(27);
        chess_report(31);
        chess_report(35);
}


int main()
{
    test_zlp1();
    return 0;
}
