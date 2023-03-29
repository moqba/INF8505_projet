/*
-- Copyright (c) 2019-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

//#define TEST(I,T) T test##I(T a) [[chess::overlay_io]] { return a & ((1<<I)-1); }
#define TEST(I,T) T test##I(T a) property(overlay_io) { return a & ((1U<<I)-1); }

TEST( 1,unsigned)
TEST( 2,unsigned)
TEST( 3,unsigned)
TEST( 4,unsigned)
TEST( 5,unsigned)
TEST( 6,unsigned)
TEST( 7,unsigned)
TEST( 8,unsigned)
TEST( 9,unsigned)
TEST(10,unsigned)
TEST(11,unsigned)
TEST(12,unsigned)
TEST(13,unsigned)
TEST(14,unsigned)
TEST(15,unsigned)
TEST(16,unsigned)
TEST(17,unsigned)
TEST(18,unsigned)
TEST(19,unsigned)
TEST(20,unsigned)
TEST(21,unsigned)
TEST(22,unsigned)
TEST(23,unsigned)
TEST(24,unsigned)
TEST(25,unsigned)
TEST(26,unsigned)
TEST(27,unsigned)
TEST(28,unsigned)
TEST(29,unsigned)
TEST(30,unsigned)
TEST(31,unsigned)

int A[] = { 0, 1, -1 };

int main()
{
  for (int i = 0; i < (int)(sizeof(A)/sizeof(int)); ++i) {
    chess_report(test1(A[i]));
    chess_report(test2(A[i]));
    chess_report(test3(A[i]));
    chess_report(test4(A[i]));
    chess_report(test5(A[i]));
    chess_report(test6(A[i]));
    chess_report(test7(A[i]));
    chess_report(test8(A[i]));
    chess_report(test9(A[i]));
    chess_report(test10(A[i]));
    chess_report(test11(A[i]));
    chess_report(test12(A[i]));
    chess_report(test13(A[i]));
    chess_report(test14(A[i]));
    chess_report(test15(A[i]));
    chess_report(test16(A[i]));
    chess_report(test17(A[i]));
    chess_report(test18(A[i]));
    chess_report(test19(A[i]));
    chess_report(test20(A[i]));
    chess_report(test21(A[i]));
    chess_report(test22(A[i]));
    chess_report(test23(A[i]));
    chess_report(test24(A[i]));
    chess_report(test25(A[i]));
    chess_report(test26(A[i]));
    chess_report(test27(A[i]));
    chess_report(test28(A[i]));
    chess_report(test29(A[i]));
    chess_report(test30(A[i]));
    chess_report(test31(A[i]));
  }
  return 0;
}
