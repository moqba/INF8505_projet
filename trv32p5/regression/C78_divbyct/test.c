/*
-- Test division-by-constant reduction.
--
-- Copyright (c) 2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

#include "regression.h"

NEVER_INLINE int sdiv_1(int i) { return i / 1; }
NEVER_INLINE int sdiv_3(int i) { return i / 3; }
NEVER_INLINE int sdiv_7(int i) { return i / 7; }
NEVER_INLINE int sdiv_15(int i) { return i / 15; }
NEVER_INLINE int sdiv_31(int i) { return i / 31; }
NEVER_INLINE int sdiv_63(int i) { return i / 63; }
NEVER_INLINE int sdiv_127(int i) { return i / 127; }
NEVER_INLINE int sdiv_255(int i) { return i / 255; }
NEVER_INLINE int sdiv_511(int i) { return i / 511; }
NEVER_INLINE int sdiv_1023(int i) { return i / 1023; }
NEVER_INLINE int sdiv_2047(int i) { return i / 2047; }
NEVER_INLINE int sdiv_4095(int i) { return i / 4095; }
NEVER_INLINE int sdiv_8191(int i) { return i / 8191; }
NEVER_INLINE int sdiv_16383(int i) { return i / 16383; }
NEVER_INLINE int sdiv_32767(int i) { return i / 32767; }
NEVER_INLINE int sdiv_65535(int i) { return i / 65535; }
NEVER_INLINE int sdiv_131071(int i) { return i / 131071; }
NEVER_INLINE int sdiv_262143(int i) { return i / 262143; }
NEVER_INLINE int sdiv_524287(int i) { return i / 524287; }
NEVER_INLINE int sdiv_1048575(int i) { return i / 1048575; }
NEVER_INLINE int sdiv_2097151(int i) { return i / 2097151; }
NEVER_INLINE int sdiv_4194303(int i) { return i / 4194303; }
NEVER_INLINE int sdiv_8388607(int i) { return i / 8388607; }
NEVER_INLINE int sdiv_16777215(int i) { return i / 16777215; }
NEVER_INLINE int sdiv_33554431(int i) { return i / 33554431; }
NEVER_INLINE int sdiv_67108863(int i) { return i / 67108863; }
NEVER_INLINE int sdiv_134217727(int i) { return i / 134217727; }
NEVER_INLINE int sdiv_268435455(int i) { return i / 268435455; }
NEVER_INLINE int sdiv_536870911(int i) { return i / 536870911; }
NEVER_INLINE int sdiv_1073741823(int i) { return i / 1073741823; }
NEVER_INLINE int sdiv_2147483647(int i) { return i / 2147483647; }

NEVER_INLINE int sdiv_n1(int i) { return i / -1; }
NEVER_INLINE int sdiv_n3(int i) { return i / -3; }
NEVER_INLINE int sdiv_n7(int i) { return i / -7; }
NEVER_INLINE int sdiv_n15(int i) { return i / -15; }
NEVER_INLINE int sdiv_n31(int i) { return i / -31; }
NEVER_INLINE int sdiv_n63(int i) { return i / -63; }
NEVER_INLINE int sdiv_n127(int i) { return i / -127; }
NEVER_INLINE int sdiv_n255(int i) { return i / -255; }
NEVER_INLINE int sdiv_n511(int i) { return i / -511; }
NEVER_INLINE int sdiv_n1023(int i) { return i / -1023; }
NEVER_INLINE int sdiv_n2047(int i) { return i / -2047; }
NEVER_INLINE int sdiv_n4095(int i) { return i / -4095; }
NEVER_INLINE int sdiv_n8191(int i) { return i / -8191; }
NEVER_INLINE int sdiv_n16383(int i) { return i / -16383; }
NEVER_INLINE int sdiv_n32767(int i) { return i / -32767; }
NEVER_INLINE int sdiv_n65535(int i) { return i / -65535; }
NEVER_INLINE int sdiv_n131071(int i) { return i / -131071; }
NEVER_INLINE int sdiv_n262143(int i) { return i / -262143; }
NEVER_INLINE int sdiv_n524287(int i) { return i / -524287; }
NEVER_INLINE int sdiv_n1048575(int i) { return i / -1048575; }
NEVER_INLINE int sdiv_n2097151(int i) { return i / -2097151; }
NEVER_INLINE int sdiv_n4194303(int i) { return i / -4194303; }
NEVER_INLINE int sdiv_n8388607(int i) { return i / -8388607; }
NEVER_INLINE int sdiv_n16777215(int i) { return i / -16777215; }
NEVER_INLINE int sdiv_n33554431(int i) { return i / -33554431; }
NEVER_INLINE int sdiv_n67108863(int i) { return i / -67108863; }
NEVER_INLINE int sdiv_n134217727(int i) { return i / -134217727; }
NEVER_INLINE int sdiv_n268435455(int i) { return i / -268435455; }
NEVER_INLINE int sdiv_n536870911(int i) { return i / -536870911; }
NEVER_INLINE int sdiv_n1073741823(int i) { return i / -1073741823; }
NEVER_INLINE int sdiv_n2147483647(int i) { return i / -2147483647; }

NEVER_INLINE unsigned udiv_1(unsigned i) { return i / 1U; }
NEVER_INLINE unsigned udiv_3(unsigned i) { return i / 3U; }
NEVER_INLINE unsigned udiv_7(unsigned i) { return i / 7U; }
NEVER_INLINE unsigned udiv_15(unsigned i) { return i / 15U; }
NEVER_INLINE unsigned udiv_31(unsigned i) { return i / 31U; }
NEVER_INLINE unsigned udiv_63(unsigned i) { return i / 63U; }
NEVER_INLINE unsigned udiv_127(unsigned i) { return i / 127U; }
NEVER_INLINE unsigned udiv_255(unsigned i) { return i / 255U; }
NEVER_INLINE unsigned udiv_511(unsigned i) { return i / 511U; }
NEVER_INLINE unsigned udiv_1023(unsigned i) { return i / 1023U; }
NEVER_INLINE unsigned udiv_2047(unsigned i) { return i / 2047U; }
NEVER_INLINE unsigned udiv_4095(unsigned i) { return i / 4095U; }
NEVER_INLINE unsigned udiv_8191(unsigned i) { return i / 8191U; }
NEVER_INLINE unsigned udiv_16383(unsigned i) { return i / 16383U; }
NEVER_INLINE unsigned udiv_32767(unsigned i) { return i / 32767U; }
NEVER_INLINE unsigned udiv_65535(unsigned i) { return i / 65535U; }
NEVER_INLINE unsigned udiv_131071(unsigned i) { return i / 131071U; }
NEVER_INLINE unsigned udiv_262143(unsigned i) { return i / 262143U; }
NEVER_INLINE unsigned udiv_524287(unsigned i) { return i / 524287U; }
NEVER_INLINE unsigned udiv_1048575(unsigned i) { return i / 1048575U; }
NEVER_INLINE unsigned udiv_2097151(unsigned i) { return i / 2097151U; }
NEVER_INLINE unsigned udiv_4194303(unsigned i) { return i / 4194303U; }
NEVER_INLINE unsigned udiv_8388607(unsigned i) { return i / 8388607U; }
NEVER_INLINE unsigned udiv_16777215(unsigned i) { return i / 16777215U; }
NEVER_INLINE unsigned udiv_33554431(unsigned i) { return i / 33554431U; }
NEVER_INLINE unsigned udiv_67108863(unsigned i) { return i / 67108863U; }
NEVER_INLINE unsigned udiv_134217727(unsigned i) { return i / 134217727U; }
NEVER_INLINE unsigned udiv_268435455(unsigned i) { return i / 268435455U; }
NEVER_INLINE unsigned udiv_536870911(unsigned i) { return i / 536870911U; }
NEVER_INLINE unsigned udiv_1073741823(unsigned i) { return i / 1073741823U; }
NEVER_INLINE unsigned udiv_2147483647(unsigned i) { return i / 2147483647U; }
NEVER_INLINE unsigned udiv_4294967295(unsigned i) { return i / 4294967295U; }

NEVER_INLINE int sdiv_2(int i) { return i / 2; };
NEVER_INLINE int sdiv_5(int i) { return i / 5; };
NEVER_INLINE int sdiv_11(int i) { return i / 11; };
NEVER_INLINE int sdiv_13(int i) { return i / 13; };
NEVER_INLINE int sdiv_17(int i) { return i / 17; };
NEVER_INLINE int sdiv_19(int i) { return i / 19; };
NEVER_INLINE int sdiv_23(int i) { return i / 23; };
NEVER_INLINE int sdiv_29(int i) { return i / 29; };
NEVER_INLINE int sdiv_37(int i) { return i / 37; };
NEVER_INLINE int sdiv_41(int i) { return i / 41; };
NEVER_INLINE int sdiv_43(int i) { return i / 43; };
NEVER_INLINE int sdiv_47(int i) { return i / 47; };
NEVER_INLINE int sdiv_53(int i) { return i / 53; };
NEVER_INLINE int sdiv_59(int i) { return i / 59; };
NEVER_INLINE int sdiv_61(int i) { return i / 61; };
NEVER_INLINE int sdiv_67(int i) { return i / 67; };
NEVER_INLINE int sdiv_71(int i) { return i / 71; };
NEVER_INLINE int sdiv_73(int i) { return i / 73; };
NEVER_INLINE int sdiv_79(int i) { return i / 79; };
NEVER_INLINE int sdiv_83(int i) { return i / 83; };
NEVER_INLINE int sdiv_89(int i) { return i / 89; };
NEVER_INLINE int sdiv_97(int i) { return i / 97; };

NEVER_INLINE unsigned udiv_2(unsigned i) { return i / 2; };
NEVER_INLINE unsigned udiv_5(unsigned i) { return i / 5; };
NEVER_INLINE unsigned udiv_11(unsigned i) { return i / 11; };
NEVER_INLINE unsigned udiv_13(unsigned i) { return i / 13; };
NEVER_INLINE unsigned udiv_17(unsigned i) { return i / 17; };
NEVER_INLINE unsigned udiv_19(unsigned i) { return i / 19; };
NEVER_INLINE unsigned udiv_23(unsigned i) { return i / 23; };
NEVER_INLINE unsigned udiv_29(unsigned i) { return i / 29; };
NEVER_INLINE unsigned udiv_37(unsigned i) { return i / 37; };
NEVER_INLINE unsigned udiv_41(unsigned i) { return i / 41; };
NEVER_INLINE unsigned udiv_43(unsigned i) { return i / 43; };
NEVER_INLINE unsigned udiv_47(unsigned i) { return i / 47; };
NEVER_INLINE unsigned udiv_53(unsigned i) { return i / 53; };
NEVER_INLINE unsigned udiv_59(unsigned i) { return i / 59; };
NEVER_INLINE unsigned udiv_61(unsigned i) { return i / 61; };
NEVER_INLINE unsigned udiv_67(unsigned i) { return i / 67; };
NEVER_INLINE unsigned udiv_71(unsigned i) { return i / 71; };
NEVER_INLINE unsigned udiv_73(unsigned i) { return i / 73; };
NEVER_INLINE unsigned udiv_79(unsigned i) { return i / 79; };
NEVER_INLINE unsigned udiv_83(unsigned i) { return i / 83; };
NEVER_INLINE unsigned udiv_89(unsigned i) { return i / 89; };
NEVER_INLINE unsigned udiv_97(unsigned i) { return i / 97; };



void sdiv(int i) {
  chess_message("// sdiv " << i);
  chess_report(sdiv_1(i));
  chess_report(sdiv_3(i));
  chess_report(sdiv_7(i));
  chess_report(sdiv_15(i));
  chess_report(sdiv_31(i));
  chess_report(sdiv_63(i));
  chess_report(sdiv_127(i));
  chess_report(sdiv_255(i));
  chess_report(sdiv_511(i));
  chess_report(sdiv_1023(i));
  chess_report(sdiv_2047(i));
  chess_report(sdiv_4095(i));
  chess_report(sdiv_8191(i));
  chess_report(sdiv_16383(i));
  chess_report(sdiv_32767(i));
  chess_report(sdiv_65535(i));
  chess_report(sdiv_131071(i));
  chess_report(sdiv_262143(i));
  chess_report(sdiv_524287(i));
  chess_report(sdiv_1048575(i));
  chess_report(sdiv_2097151(i));
  chess_report(sdiv_4194303(i));
  chess_report(sdiv_8388607(i));
  chess_report(sdiv_16777215(i));
  chess_report(sdiv_33554431(i));
  chess_report(sdiv_67108863(i));
  chess_report(sdiv_134217727(i));
  chess_report(sdiv_268435455(i));
  chess_report(sdiv_536870911(i));
  chess_report(sdiv_1073741823(i));
  chess_report(sdiv_2147483647(i));

  chess_report(sdiv_n1(i));
  chess_report(sdiv_n3(i));
  chess_report(sdiv_n7(i));
  chess_report(sdiv_n15(i));
  chess_report(sdiv_n31(i));
  chess_report(sdiv_n63(i));
  chess_report(sdiv_n127(i));
  chess_report(sdiv_n255(i));
  chess_report(sdiv_n511(i));
  chess_report(sdiv_n1023(i));
  chess_report(sdiv_n2047(i));
  chess_report(sdiv_n4095(i));
  chess_report(sdiv_n8191(i));
  chess_report(sdiv_n16383(i));
  chess_report(sdiv_n32767(i));
  chess_report(sdiv_n65535(i));
  chess_report(sdiv_n131071(i));
  chess_report(sdiv_n262143(i));
  chess_report(sdiv_n524287(i));
  chess_report(sdiv_n1048575(i));
  chess_report(sdiv_n2097151(i));
  chess_report(sdiv_n4194303(i));
  chess_report(sdiv_n8388607(i));
  chess_report(sdiv_n16777215(i));
  chess_report(sdiv_n33554431(i));
  chess_report(sdiv_n67108863(i));
  chess_report(sdiv_n134217727(i));
  chess_report(sdiv_n268435455(i));
  chess_report(sdiv_n536870911(i));
  chess_report(sdiv_n1073741823(i));
  chess_report(sdiv_n2147483647(i));

  chess_report(sdiv_2(i));
  chess_report(sdiv_5(i));
  chess_report(sdiv_11(i));
  chess_report(sdiv_13(i));
  chess_report(sdiv_17(i));
  chess_report(sdiv_19(i));
  chess_report(sdiv_23(i));
  chess_report(sdiv_29(i));
  chess_report(sdiv_37(i));
  chess_report(sdiv_41(i));
  chess_report(sdiv_43(i));
  chess_report(sdiv_47(i));
  chess_report(sdiv_53(i));
  chess_report(sdiv_59(i));
  chess_report(sdiv_61(i));
  chess_report(sdiv_67(i));
  chess_report(sdiv_71(i));
  chess_report(sdiv_73(i));
  chess_report(sdiv_79(i));
  chess_report(sdiv_83(i));
  chess_report(sdiv_89(i));
  chess_report(sdiv_97(i));
}

void udiv(unsigned i) {
  chess_message("// udiv " << i);
  chess_report(udiv_1(i));
  chess_report(udiv_3(i));
  chess_report(udiv_7(i));
  chess_report(udiv_15(i));
  chess_report(udiv_31(i));
  chess_report(udiv_63(i));
  chess_report(udiv_127(i));
  chess_report(udiv_255(i));
  chess_report(udiv_511(i));
  chess_report(udiv_1023(i));
  chess_report(udiv_2047(i));
  chess_report(udiv_4095(i));
  chess_report(udiv_8191(i));
  chess_report(udiv_16383(i));
  chess_report(udiv_32767(i));
  chess_report(udiv_65535(i));
  chess_report(udiv_131071(i));
  chess_report(udiv_262143(i));
  chess_report(udiv_524287(i));
  chess_report(udiv_1048575(i));
  chess_report(udiv_2097151(i));
  chess_report(udiv_4194303(i));
  chess_report(udiv_8388607(i));
  chess_report(udiv_16777215(i));
  chess_report(udiv_33554431(i));
  chess_report(udiv_67108863(i));
  chess_report(udiv_134217727(i));
  chess_report(udiv_268435455(i));
  chess_report(udiv_536870911(i));
  chess_report(udiv_1073741823(i));
  chess_report(udiv_2147483647(i));
  chess_report(udiv_4294967295(i));

  chess_report(udiv_2(i));
  chess_report(udiv_5(i));
  chess_report(udiv_11(i));
  chess_report(udiv_13(i));
  chess_report(udiv_17(i));
  chess_report(udiv_19(i));
  chess_report(udiv_23(i));
  chess_report(udiv_29(i));
  chess_report(udiv_37(i));
  chess_report(udiv_41(i));
  chess_report(udiv_43(i));
  chess_report(udiv_47(i));
  chess_report(udiv_53(i));
  chess_report(udiv_59(i));
  chess_report(udiv_61(i));
  chess_report(udiv_67(i));
  chess_report(udiv_71(i));
  chess_report(udiv_73(i));
  chess_report(udiv_79(i));
  chess_report(udiv_83(i));
  chess_report(udiv_89(i));
  chess_report(udiv_97(i));

}

int A[] = {
    0, 1, -1, 3, -7, 15, 47, 0x7fff00ff, -0x7fff00ff, 0x42424242
};

unsigned B[] = {
    1, 0, 2, 10, 8, 16, 13, 42, 255, 0x7fff00ff, 0xffffffff, 0xff00ff00,
    0xdeadbeef
};

int main() {
  for (unsigned i = 0; i < sizeof(A)/sizeof(int); ++i) {
    sdiv(A[i]);
  }
  for (unsigned i = 0; i < sizeof(B)/sizeof(int); ++i) {
    udiv(B[i]);
  }
  return 0;
}
