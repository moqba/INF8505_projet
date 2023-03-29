/*
-- Test convolve-like loops
--
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

// NOTE: This is not a real convolution.

const int M = 32;
const int N = 16;

int X[M] = { 0, 0, 1, 2, 3, 4, 5, 6, 5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5, -6, -5, -4, -3, -2, -1, 0, 0, 0, 0, 0, 0 };
int H[N] = { 1, 5, 2, 6, 3, 8, 4, 9, 1, 5, 2, 6, 3, 8, 4, 9 };
int Y[M];

void convolve (int x[], int h[], int y[])
{
  for (int i = 0; i < M; i++)
  {
    int z = 0;
    for (int j = 0; j < N; j++)
      z += x[j] * h[j];
    y[i] = z;
  }
}

void convolve2(int x[], int h[], int y[])
{
  for (int i = 0; i < M; i++)
  {
    int z = 0;
    for (int j = 0; j < N; j++) chess_unroll_loop(4)
                z += x[j] * h[j];
    y[i] = z;
  }
}

void convolve3(int x[], int h[], int y[])
{
  for (int i = 0; i < M; i++)
  {
    int z = 0;
    for (int j = 0; j < N; j++) chess_unroll_loop(8)
                z += x[j] * h[j];
    y[i] = z;
  }
}

void convolve4(int x[], int h[], int y[])
{
  for (int i = 0; i < M; i++)
  {
    int z = 0;
    for (int j = 0; j < N; j++) chess_flatten_loop
        z += x[j] * h[j];
    y[i] = z;
  }
}


int sum(int y[])
{
  int s = 0;
  for (int i = 0; i < M; i++)
    s += y[i];
  return s;
}


int main()
{
  int x = 0;
  convolve(X,H,Y);
  x += sum(Y);
  chess_report(x);
  convolve2(X,H,Y);
  x += sum(Y);
  chess_report(x);
  convolve3(X,H,Y);
  x += sum(Y);
  chess_report(x);
  convolve4(X,H,Y);
  x += sum(Y);
  chess_report(x);
  return 0;
}
