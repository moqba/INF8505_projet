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
inline assembly void test_br_taken() clobbers(x4, x5, x6, x7, x8, x9, x10) {
  asm_begin
  asm_text
    ori x4, x0, 100
    ori x5, x0, 1
    ori x6, x0, 2
    ori x7, x0, 3
    ori x8, x0, 4
    ori x9, x0, 5
    ori x10, x0, 6
    nop
    add x4,x4,x5
    beq x4,x4, La
    add x4,x4,x6
    add x4,x4,x7
    add x4,x4,x8
La:     add x4,x4,x9
    add x10,x4,x10
.chess_report __sint
    nop
    nop
  asm_end
}
#else
inline void test_br_taken() {
  chess_message(" // test_br_taken");
  chess_report (112);
}
#endif

#ifdef __ndl__
inline assembly void test_br_untaken() clobbers(x4, x5, x6, x7, x8, x9, x10) {
  asm_begin
  asm_text
    ori x4, x0, 200
    ori x5, x0, 1
    ori x6, x0, 2
    ori x7, x0, 3
    ori x8, x0, 4
    ori x9, x0, 5
    ori x10, x0, 6
    nop
    add x4,x4,x5
    bne x4,x4, Lb
    add x4,x4,x6
    add x4,x4,x7
    add x4,x4,x8
Lb:     add x4,x4,x9
    add x10,x4,x10
.chess_report __sint
    nop
    nop
  asm_end
}
#else
inline void test_br_untaken() {
  chess_message(" // test_br_untaken");
  chess_report (221);
}
#endif

int main() {
  test_br_taken();
  test_br_untaken();
  return 0;
}
