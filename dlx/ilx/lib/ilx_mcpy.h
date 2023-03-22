/*
-- File : ilx_mcpy.h
--
-- Contents : Chess implementation of memcpy() function
--
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/



#ifndef _ilx_mcpy_h
#define _ilx_mcpy_h

typedef short chess_may_alias _aliasing_short;
typedef int   chess_may_alias _aliasing_int;

#define DOCOPY                                                       \
  if (chess_manifest(sz < 5)) {                                      \
    if (sz >= 1) *ll++ = *rr++;                                      \
    if (sz >= 2) *ll++ = *rr++;                                      \
    if (sz >= 3) *ll++ = *rr++;                                      \
    if (sz >= 4) *ll   = *rr;                                        \
  }                                                                  \
  else                                                               \
    for (int ii = 0; ii < sz; ii++)                                  \
      ll[ii] = rr[ii];                                               \
// end define DOCOPY

inline void char_memory_copy(volatile char* l, const volatile char* r,
                             const int sz)
{
  char* ll = (char*)l;
  char* rr = (char*)r;
  DOCOPY
}

inline void short_memory_copy(volatile short* l, const volatile short* r,
                              const int sz)
{
  _aliasing_short* ll = (_aliasing_short*)l;
  _aliasing_short* rr = (_aliasing_short*)r;
  DOCOPY
}

inline void int_memory_copy(volatile int* l, const volatile int* r,
                            const int sz)
{
  _aliasing_int* ll = (_aliasing_int*)l;
  _aliasing_int* rr = (_aliasing_int*)r;
  DOCOPY
}

inline void chess_memory_copy(volatile void* l, const volatile void* r,
                              const int sz, const int algn)
{
  if (algn == sizeof(int))
    int_memory_copy((int*)l, (int*)r, sz / sizeof(int));
  else if (algn == sizeof(short))
    short_memory_copy((short*)l, (short*)r, sz / sizeof(short));
  else  // algn == sizeof(char)
    char_memory_copy((char*)l, (char*)r, sz / sizeof(char));
}


#define DOSET                                                        \
  if (chess_manifest(ssz < 5)) {                                     \
    if (ssz >= 1) *ll++ = v;                                         \
    if (ssz >= 2) *ll++ = v;                                         \
    if (ssz >= 3) *ll++ = v;                                         \
    if (ssz >= 4) *ll   = v;                                         \
  }                                                                  \
  else                                                               \
    for (int ii = 0; ii < ssz; ii++)                                 \
      ll[ii] = v;                                                    \
// end define DOSET

inline void chess_memory_set(volatile void* l, const int v,
                             const int sz, const int algn)
{
    _aliasing_int* ll = (_aliasing_int*)l;
    int ssz = sz / sizeof(int);
    DOSET
}

inline void chess_memory_set(volatile void* l, const short v,
                             const int sz, const int algn)
{
    if (algn % chess_alignof(int) == 0) {
        int sv = (unsigned short)v;
        int vv = sv << chess_bitsof(short) | sv;
        chess_memory_set(l, vv, sz, algn);
    } else {
        _aliasing_short* ll = (_aliasing_short*)l;
        int ssz = sz / sizeof(short);
        DOSET
    }
}

inline void chess_memory_set(volatile void* l, const char v,
                             const int sz, const int algn)
{
    if (algn % chess_alignof(short) == 0) {
        int cv = (unsigned char)v;
        short vv = cv << chess_bitsof(char) | cv;
        chess_memory_set(l, vv, sz, algn);
    } else {
        char* ll = (char*)l;
        int ssz = sz / sizeof(char);
        DOSET
    }
}

#endif /* _ilx_mcpy_h */
