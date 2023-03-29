/*
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

#ifdef __ndl__
inline assembly void test_j() clobbers(x4, x5, x6, x7, x8, x9, x10) {
  asm_begin
  asm_text
    ori x4, x0, 100
    ori x5, x0, 1
    ori x6, x0, 2
    ori x7, x0, 3
    ori x8, x0, 4
    ori x9, x0, 5
    ori x10, x0, 6
    add x4,x4,x5
    jal x0, La
    add x4,x4,x6
    add x4,x4,x7
    add x4,x4,x8
La:
    add x4,x4,x9
    add x10,x4,x10
.chess_report __sint
    nop
    nop
  asm_end
}
#else
inline void test_j()
{
    chess_message(" // test_j");
    chess_report (112);
}
#endif

#ifdef __ndl__
inline assembly void test_jr() clobbers(x4, x5, x6, x7, x8, x9, x10, x13) {
  asm_begin
    .direct_eval >>,&,(,),+
  asm_text
    ori x4, x0, 200
    lui x13, ((Lb+2048)>>12)
    addi x13, x13, (Lb&0xfff)
    nop
    ori x5, x0, 1
    ori x6, x0, 2
    ori x7, x0, 3
    ori x8, x0, 4
    ori x9, x0, 5
    ori x10, x0, 6
    add x4,x4,x5
    jalr x0, x13, 0
    add x4,x4,x6
    add x4,x4,x7
    add x4,x4,x8
Lb:
    add x4,x4,x9
    add x10,x4,x10
.chess_report __sint
    nop
    nop
  asm_end
}
#else
inline void test_jr() {
  chess_message(" // test_jr");
  chess_report (212);
}
#endif

int main() {
  test_j();
  test_jr();
  return 0;
}
