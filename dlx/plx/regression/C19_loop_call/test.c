/*
-- Benchmark: Test (hardware) loop with nothing but a call
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/


#ifdef __chess__
#define CLOBBERS   clobbers()
#else
#define CLOBBERS
#endif

#define N 10

void foo() property(loop_free functional volatile)  CLOBBERS
{
    static int dummy = 0;
    chess_report(dummy++);
}


int main()
{
    chess_message("// start");

    for (int n = 0; n < N; n++)  foo();

    chess_message("// done");
    chess_report(99);

    return 0;
}
