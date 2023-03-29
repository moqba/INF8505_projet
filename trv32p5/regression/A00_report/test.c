/*
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

#include <stdlib.h>

#ifdef __ndl__
inline assembly void asm_report() clobbers(x3,x4,x10) {
  asm_begin
  asm_text
    ori x3, x0, 10
    ori x4, x0, 20
    nop
    nop
    nop
    add  x10,x3,x4
.chess_report __sint
    nop
    nop
    nop
  asm_end
}
#else
inline void asm_report() {
  chess_report (30);
}
#endif

int * a;
int main() {
  a = (int *)malloc(4);
  chess_message( "// First test message" );
  chess_report(101);
  asm_report();
  return 0;
}
