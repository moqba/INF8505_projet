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
inline assembly void test_1() clobbers(x3,x4,x5,x10) {
  asm_begin
  asm_text
    ori x4, x0, 10
    ori x3, x0, 20
    nop
    nop
    add x5,x4,x3
    nop
    nop
    add x5,x5,x4
    nop
    nop
    add x5,x5,x4
    nop
    nop
    add x5,x5,x4
    nop
    nop
    add x10,x5,x4
.chess_report __sint
    nop
    nop
    nop
    sub x10,x3,x10
.chess_report __sint
    nop
    nop
  asm_end
}
#else
inline void test_1() {
  chess_message(" // test_1");
  chess_report (70);
  chess_report (-50);
}
#endif

#ifdef __ndl__
inline assembly void test_2() clobbers(x3,x4,x5,x10) {
  asm_begin
  asm_text
    ori x4, x0, 10
    ori x3, x0, 20
    nop
    add x5,x4,x3
    nop
    add x5,x5,x4
    nop
    add x5,x5,x4
    nop
    add x5,x5,x4
    nop
    add x10,x5,x4
.chess_report __sint
    nop
    nop
    nop
    sub x10,x3,x10
.chess_report __sint
    nop
    nop
  asm_end
}
#else
inline void test_2() {
  chess_message(" // test_2");
  chess_report (70);
  chess_report (-50);
}
#endif

#ifdef __ndl__
inline assembly void test_3() clobbers(x3,x4,x5,x10) {
  asm_begin
  asm_text
    ori x4, x0, 10
    ori x3, x0, 20
    add x5, x4, x3
    add x5, x5, x4
    add x5, x5, x4
    add x5, x5, x4
    add x10, x5, x4
.chess_report __sint
    sub x10, x3, x10
.chess_report __sint
    nop
    nop
    nop
  asm_end
}
#else
inline void test_3() {
  chess_message(" // test_3");
  chess_report (70);
  chess_report (-50);
}
#endif

int main() {
  test_1();
  test_2();
  test_3();
  return 0;
}
