/*
-- Test cordic like code
--
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

// Based on http://www.dcs.gla.ac.uk/~jhw/cordic/

// Cordic in 32 bit signed fixed point math
// Function is valid for arguments in range -pi/2 -- pi/2
// for values pi/2--pi: value = half_pi-(theta-half_pi) and similarly
// for values -pi---pi/2
//
// 1.0 = 1073741824
// 1/k = 0.6072529350088812561694
// pi = 3.1415926536897932384626

// Constants
#define cordic_1K 0x26DD3B6A
#define half_pi 0x6487ED51
#define MUL 1073741824.000000
#define N 32

int cordic_ctab [] = {
    0x3243F6A8, 0x1DAC6705, 0x0FADBAFC, 0x07F56EA6,
    0x03FEAB76, 0x01FFD55B, 0x00FFFAAA, 0x007FFF55,
    0x003FFFEA, 0x001FFFFD, 0x000FFFFF, 0x0007FFFF,
    0x0003FFFF, 0x0001FFFF, 0x0000FFFF, 0x00007FFF,
    0x00003FFF, 0x00001FFF, 0x00000FFF, 0x000007FF,
    0x000003FF, 0x000001FF, 0x000000FF, 0x0000007F,
    0x0000003F, 0x0000001F, 0x0000000F, 0x00000008,
    0x00000004, 0x00000002, 0x00000001, 0x00000000, };

typedef void (*cordic_fn)(int,int*,int*);

void cordic0(int theta, int *s, int *c)
{
  int k, d, tx, ty, tz;
  int x = cordic_1K;
  int y = 0;
  int z = theta;
  for (k=0; k < N; ++k)
  {
    if (z >= 0) {
      tx = x - (y>>k);
      ty = y + (x>>k);
      tz = z - cordic_ctab[k];
    } else {
      tx = x + (y>>k);
      ty = y - (x>>k);
      tz = z + cordic_ctab[k];
    }
    x = tx;
    y = ty;
    z = tz;
  }
  *c = x;
  *s = y;
}

void cordic1(int theta, int *s, int *c)
{
  int k, d, tx, ty, tz;
  int x = cordic_1K;
  int y = 0;
  int z = theta;
  for (k=0; k < N; ++k)
  {
    d = z>>31;
    tx = x - (((y>>k) ^ d) - d);
    ty = y + (((x>>k) ^ d) - d);
    tz = z - ((cordic_ctab[k] ^ d) - d);
    x = tx;
    y = ty;
    z = tz;
  }
  *c = x;
  *s = y;
}

void test_cordic(cordic_fn f)
{
  int angle, sinval, cosval;


  angle = half_pi >> 1;
  chess_message( "// angle (" << angle << ')' );
  f(angle, &sinval, &cosval);
  chess_report(sinval);
  chess_report(cosval);

  angle = half_pi >> 2;
  chess_message( "// angle (" << angle << ')' );
  f(angle, &sinval, &cosval);
  chess_report(sinval);
  chess_report(cosval);

  angle = (half_pi >> 1) + (half_pi >> 2);
  chess_message( "// angle (" << angle << ')' );
  f(angle, &sinval, &cosval);
  chess_report(sinval);
  chess_report(cosval);
}

int main()
{
  chess_message( "// cordic 0 --------- ");
  test_cordic(cordic0);
  chess_message( "// cordic 1 --------- ");
  test_cordic(cordic1);
  return 0;
}
