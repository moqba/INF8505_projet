/*
-- Test: mulh intrinsics
--
-- Copyright (c) 2020 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/


#define NOINLINE [[gnu::noinline]]

NOINLINE void test_mulh(int x, int y) {
  chess_report(mulh(x,y));
}

NOINLINE void test_mulhu(unsigned x, unsigned y) {
  chess_report(mulh(x,y));
}

NOINLINE void test_mulhsu(int x, unsigned y) {
  chess_report(mulh(x,y));
}

NOINLINE void test_mulhus(unsigned x, int y) {
  chess_report(mulh(x,y));
}

int main()
{
  static unsigned const a[] = {
      0, 1, 0x7fffffff, 0x80000000, 0xffffffff, 0x0000ffff,
      0xffff0000, 0xa0a0a0a0, 0x0a0a0a0a, 0xf0f0f0f0, 0x0f0f0f0f,
  };

  int const N = sizeof(a) / sizeof(*a);

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      test_mulh   (a[i],a[j]);
      test_mulhu  (a[i],a[j]);
      test_mulhsu (a[i],a[j]);
      test_mulhus (a[i],a[j]);
    }
  }

  return 0;
}
