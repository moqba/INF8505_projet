/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * ====================================================
 */

/*
 * from: @(#)fdlibm.h 5.1 93/09/24
 */

#ifndef _MATH_PRIVATE_H_
#define _MATH_PRIVATE_H_

//#include <sys/types.h>
typedef unsigned u_int32_t;

/* The original fdlibm code used statements like:
	n0 = ((*(int*)&one)>>29)^1;		* index of high word *
	ix0 = *(n0+(int*)&x);			* high word of x *
	ix1 = *((1-n0)+(int*)&x);		* low word of x *
   to dig two 32 bit words out of the 64 bit IEEE floating point
   value.  That is non-ANSI, and, moreover, the gcc instruction
   scheduler gets it wrong.  We instead use the following macros.
   Unlike the original code, we determine the endianness at compile
   time, not at run time; I don't see much benefit to selecting
   endianness at run time.  */

//TCT- This package uses 32 bit integer arithmetic exclusively.
//     TBD Certain operations could be done directly on 64 bit integers.

/* A union which permits us to convert between a double and two 32 bit
   ints.  */

#ifdef __clang__
__attribute__((always_inline))
#endif
inline long long compose_ll(unsigned h, unsigned l)
{
    return ((long long)h<<32) | l;
}

#ifdef __chess__
#define EXTRACT_WORDS(ix0,ix1,d) \
    ix0 = (int)(as_int64(d)>>32), ix1 = (int)(as_int64(d))
#define GET_HIGH_WORD(i,d) \
    i = (int)(as_int64(d)>>32)
#define GET_LOW_WORD(i,d) \
    i = (int)(as_int64(d))
#define INSERT_WORDS(d,ix0,ix1) \
    d = as_double(compose_ll(ix0,ix1))
#define SET_HIGH_WORD(d,v) \
    d = as_double(compose_ll(v,(unsigned)(as_int64(d))))
#define SET_LOW_WORD(d,v) \
    d = as_double(compose_ll((unsigned)(as_int64(d)>>32),v))
#else

typedef union 
{
  double value;
  struct 
  {
    u_int32_t msw;
    u_int32_t lsw;
  } parts;
} ieee_double_shape_type;


/* Get two 32 bit ints from a double.  */

#define EXTRACT_WORDS(ix0,ix1,d)				\
do {								\
  ieee_double_shape_type ew_u;					\
  ew_u.value = (d);						\
  (ix0) = ew_u.parts.msw;					\
  (ix1) = ew_u.parts.lsw;					\
} while (0)

/* Get the more significant 32 bit int from a double.  */

#define GET_HIGH_WORD(i,d)					\
do {								\
  ieee_double_shape_type gh_u;					\
  gh_u.value = (d);						\
  (i) = gh_u.parts.msw;						\
} while (0)

/* Get the less significant 32 bit int from a double.  */

#define GET_LOW_WORD(i,d)					\
do {								\
  ieee_double_shape_type gl_u;					\
  gl_u.value = (d);						\
  (i) = gl_u.parts.lsw;						\
} while (0)

/* Set a double from two 32 bit ints.  */

#define INSERT_WORDS(d,ix0,ix1)					\
do {								\
  ieee_double_shape_type iw_u;					\
  iw_u.parts.msw = (ix0);					\
  iw_u.parts.lsw = (ix1);					\
  (d) = iw_u.value;						\
} while (0)

/* Set the more significant 32 bits of a double from an int.  */

#define SET_HIGH_WORD(d,v)					\
do {								\
  ieee_double_shape_type sh_u;					\
  sh_u.value = (d);						\
  sh_u.parts.msw = (v);						\
  (d) = sh_u.value;						\
} while (0)

/* Set the less significant 32 bits of a double from an int.  */

#define SET_LOW_WORD(d,v)					\
do {								\
  ieee_double_shape_type sl_u;					\
  sl_u.value = (d);						\
  sl_u.parts.lsw = (v);						\
  (d) = sl_u.value;						\
} while (0)

#endif

/* A union which permits us to convert between a float and a 32 bit
   int.  */

#ifdef __chess__
#define GET_FLOAT_WORD(i,d) i = as_int32(d);
#define SET_FLOAT_WORD(d,i) d = as_float(i);
#else

typedef union
{
  float value;
  u_int32_t word;
} ieee_float_shape_type;

/* Get a 32 bit int from a float.  */

#define GET_FLOAT_WORD(i,d)					\
do {								\
  ieee_float_shape_type gf_u;					\
  gf_u.value = (d);						\
  (i) = gf_u.word;						\
} while (0)

/* Set a float from a 32 bit int.  */

#define SET_FLOAT_WORD(d,i)					\
do {								\
  ieee_float_shape_type sf_u;					\
  sf_u.word = (i);						\
  (d) = sf_u.value;						\
} while (0)

#endif

#endif /* _MATH_PRIVATE_H_ */
