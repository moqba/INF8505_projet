/*
-- File : plx_mcpy.h
--
-- Contents : Chess implementation of memcpy() function
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/



#ifndef _plx_mcpy_h
#define _plx_mcpy_h

#define DOCOPY                                                       \
  if (sz < 5) {                                                      \
    if (sz >= 1) *ll++ = *rr++;                                      \
    if (sz >= 2) *ll++ = *rr++;                                      \
    if (sz >= 3) *ll++ = *rr++;                                      \
    if (sz >= 4) *ll = *rr;                                          \
  }                                                                  \
  else                                                               \
    for (int ii = 0; ii < sz; ii++) chess_loop_range(5,)    \
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
  short* ll = (short*)l;
  short* rr = (short*)r;
  DOCOPY
}

inline void int_memory_copy(volatile int* l, const volatile int* r,
                            const int sz)
{
  int* ll = (int*)l;
  int* rr = (int*)r;
  DOCOPY
}

inline void chess_memory_copy(volatile void* l, const volatile void* r,
                              const int sz, const int algn)
{
  if (algn == sizeof(int))
    int_memory_copy( (int*)l, (int*)r, sz / sizeof(int) );
  else if (algn == sizeof(short))
    short_memory_copy((short*)l, (short*)r, sz / sizeof(short));
  else  // algn == sizeof(char)
    char_memory_copy((char*)l, (char*)r, sz / sizeof(char));

}

#endif /* _plx_mcpy_h */
