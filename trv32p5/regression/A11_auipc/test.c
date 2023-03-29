/*
-- Copyright (c) 2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

#include "regression.h"

#ifdef __ndl__
assembly void test1()
  chess_storage(PMb:0x1000)
  chess_clobbers(x8, x10)
{
  asm_begin
    .direct_eval >>,&,(,),+,-,*
  asm_text

    nop
    nop
    nop

    auipc x8, 0x20
    addi  x10, x8, 0x345 - 4*3

.chess_report __sint
    nop
    nop

    ret

  asm_end
}
#else
void test1() {
  chess_message("// test1");
  chess_report (0x00021345);
}
#endif

int main() {
  test1();
  return 0;
}


