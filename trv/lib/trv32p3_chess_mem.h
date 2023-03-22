/*
-- File : trv32p3_chess_mem.h
--
-- Contents : Chess memory functions
--
-- Copyright (c) 2019-2020 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

#ifndef INCLUDED_TRV32P3_CHESS_MEM_H_
#define INCLUDED_TRV32P3_CHESS_MEM_H_

#ifndef TRV32P3_CHESSMEM_THRESHOLD
#define TRV32P3_CHESSMEM_THRESHOLD 5
#endif

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ Struct Copies
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

inline void char_memory_copy(
    volatile char* l, const volatile char* r,
    const unsigned int sz) [[chess::dont_generate]]
{
  char* ll = (char*)l;
  char* rr = (char*)r;
  if (chess_manifest(sz < (TRV32P3_CHESSMEM_THRESHOLD))) {
    [[chess::unroll_loop]]
    for (unsigned int ii = 0; ii < sz; ii++)
      ll[ii] = rr[ii];
  }
  else
    for (unsigned int ii = 0; ii < sz; ii++)
      ll[ii] = rr[ii];
}

inline void short_memory_copy(
    volatile short* l, const volatile short* r,
    const unsigned int sz) [[chess::dont_generate]]
{
  short* ll = (short*)l;
  short* rr = (short*)r;
  if (chess_manifest(sz < (TRV32P3_CHESSMEM_THRESHOLD))) {
    [[chess::unroll_loop]]
    for (unsigned int ii = 0; ii < sz; ii++)
      ll[ii] = rr[ii];
  }
  else
    for (unsigned int ii = 0; ii < sz; ii++)
      ll[ii] = rr[ii];
}

inline void int_memory_copy(
    volatile int* l, const volatile int* r,
    const unsigned int sz) [[chess::dont_generate]]
{
  int* ll = (int*)l;
  int* rr = (int*)r;
  if (chess_manifest(sz < (TRV32P3_CHESSMEM_THRESHOLD))) {
    [[chess::unroll_loop]]
    for (unsigned int ii = 0; ii < sz; ii++)
      ll[ii] = rr[ii];
  }
  else
    for (unsigned int ii = 0; ii < sz; ii++)
      ll[ii] = rr[ii];
}

inline void chess_memory_copy(
          volatile void* l_,
    const volatile void* r_,
    const unsigned int sz,
    const unsigned int algn) [[chess::dont_generate]]
{
  if      ((algn % chess_alignof(int)) == 0) {
    int_memory_copy   ((int*)   l_, (int*)   r_, sz / sizeof(int));
  }
  else if ((algn % chess_alignof(short)) == 0) {
    short_memory_copy ((short*) l_, (short*) r_, sz / sizeof(short));
  }
  else {
    char_memory_copy  ((char*)  l_, (char*)  r_, sz / sizeof(char));
  }
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ Struct Inits
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

inline void chess_memory_set(
    volatile void* l, const int v,
    const unsigned int sz_, const unsigned int algn) [[chess::dont_generate]]
{
  int* ll = (int*)l;
  unsigned int sz = sz_ / sizeof(int);
  if (chess_manifest(sz < (TRV32P3_CHESSMEM_THRESHOLD))) {
    [[chess::unroll_loop]]
    for (unsigned int ii = 0; ii < sz; ii++)
      ll[ii] = v;
  }
  else
    for (unsigned int ii = 0; ii < sz; ii++)
      ll[ii] = v;
}

inline void chess_memory_set(
    volatile void* l, const short v,
    const unsigned int sz_, const unsigned int algn) [[chess::dont_generate]]
{
  if ((algn % chess_alignof(int)) == 0) {
    int sv = (unsigned short)v;
    int vv = (sv << chess_bitsof(short)) | sv;
    chess_memory_set(l, vv, sz_, algn);
  } else {
    short* ll = (short*)l;
    unsigned int sz = sz_ / sizeof(short);
    if (chess_manifest(sz < (TRV32P3_CHESSMEM_THRESHOLD))) {
      [[chess::unroll_loop]]
      for (unsigned int ii = 0; ii < sz; ii++)
        ll[ii] = v;
    }
    else
      for (unsigned int ii = 0; ii < sz; ii++)
        ll[ii] = v;
  }
}

inline void chess_memory_set(
    volatile void* l, const char v,
    const unsigned int sz_, const unsigned int algn) [[chess::dont_generate]]
{
  if ((algn % chess_alignof(short)) == 0) {
    short sv = (unsigned char)v;
    short vv = (sv << chess_bitsof(char)) | sv;
    chess_memory_set(l, vv, sz_, algn);
  } else {
    char* ll = (char*)l;
    unsigned int sz = sz_ / sizeof(char);
    if (chess_manifest(sz < (TRV32P3_CHESSMEM_THRESHOLD))) {
      [[chess::unroll_loop]]
      for (unsigned int ii = 0; ii < sz; ii++)
        ll[ii] = v;
    }
    else
      for (unsigned int ii = 0; ii < sz; ii++)
        ll[ii] = v;
  }
}

#endif /* INCLUDED_TRV32P3_CHESS_MEM_H_ */
