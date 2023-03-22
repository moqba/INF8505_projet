/*
  https://electronics.stackexchange.com/questions/196914/verilog-synthesize-high-speed-leading-zero-count
  Leading zero encoders can be made with a nice balanced tree structure.

  First, encode bits 2 by 2 :

  00 => 10 : 2 leading zeros
  01 => 01 : 1 leading zero
  10 => 00 : 0 leading zero
  11 => 00 : 0 leading zero
  Then, assemble as pairs.

  If both sides start with 1xxx, the result is 10...0
  If the left side start with 0 the result is 0[left]
  If the left side starts with 1, the result is 01[right(msb-1:0)]

  For negative results:
  First, encode bits 2 by 2 :

  00 => 00 :  0 leading zeros
  01 => 11 : -1 leading zero
  10 => 10 : -2 leading zeros
  11 => 10 : -2 leading zeros
  Then, assemble as pairs.

  If both sides start with 0xxx, the result is 00...0
  If the left side start with 1 the result is 1[left]
  If the left side starts with 0, the result is 11[right(msb-1:0)]

*/
/*
- 2 0x0
- 1 0x1
- 0 0x2
- 0 0x3
*/
uint2_t clb2_hier(uint2_t a) {
  uint2_t r;
  switch (a) {
  case 0: r = 2; break;
  case 1: r = 1; break;
  case 2: r = 0; break;
  default/*3*/: r = 0; break;
  }
  return r;
}

uint3_t clb4_hier(uint4_t a) {
  uint2_t h = clb2_hier(a[3:2]);
  uint2_t l = clb2_hier(a[1:0]);
  uint3_t r = 0;
  if ((h[1] == 1) && (l[1] == 1)) r = "100";
  else if (h[1] == 0) r = h;
  else r = "01"::l[0];
  return r;
}

uint4_t clb8_hier(uint8_t a) {
  uint3_t h = clb4_hier(a[7:4]);
  uint3_t l = clb4_hier(a[3:0]);
  uint4_t r = 0;
  if ((h[2] == 1) && (l[2] == 1)) r = "1000";
  else if (h[2] == 0) r = h;
  else r = "01"::l[1:0];
  return r;
}

uint5_t clb16_hier(uint16_t a) {
  uint4_t h = clb8_hier(a[15:8]);
  uint4_t l = clb8_hier(a[7 :0]);
  uint5_t r = 0;
  if ((h[3] == 1) && (l[3] == 1)) r = "10000";
  else if (h[3] == 0) r = h;
  else r = "01"::l[2:0];
  return r;
}

uint6_t clb32_hier(uint32_t a) {
  uint5_t h = clb16_hier(a[31:16]);
  uint5_t l = clb16_hier(a[15:0]);
  uint6_t r = 0;
  if ((h[4] == 1) && (l[4] == 1)) r = "100000";
  else if (h[4] == 0) r = h;
  else r = "01"::l[3:0];
  return r;
}

uint7_t clb64_hier(uint64_t a) {
  uint6_t h = clb32_hier(a[63:32]);
  uint6_t l = clb32_hier(a[31:0]);
  uint7_t r = 0;
  if ((h[5] == 1) && (l[5] == 1)) r = "1000000";
  else if (h[5] == 0) r = h;
  else r = "01"::l[4:0];
  return r;
}

void clb_dummy() { uint64_t a=0; clb64_hier(a); } // to avoid warnings


