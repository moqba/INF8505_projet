/*
-- File : math.c
--
-- Contents : Implementation of floating-point transcendental functions.
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/


// PORTED FROM
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
// Conventions :
// This code assumes an IEEE compliant layout of the float and double types.
// C comments come from the original code, C++ comments refer to the port.

#include <math.h>
#include <stdint.h>
#include "math_private.h"

static inline float float_pos_inf() {
    float x;
    SET_FLOAT_WORD(x,0x7f800000);
    return x;
}

static inline float float_neg_inf() {
    float x;
    SET_FLOAT_WORD(x,0xff800000);
    return x;
}

static inline float float_zero() {
    float x;
    SET_FLOAT_WORD(x,0x00000000);
    return x;
}

//  Basic operations too complex to be inlined

float ldexpf(float x, int n)
{
    static const float
        two25   =  3.355443200e+07,     /* 0x4c000000 */
        twom25  =  2.9802322388e-08,    /* 0x33000000 */
        huge   = 1.0e+30,
        tiny   = 1.0e-30;

    int32_t k,ix;
    GET_FLOAT_WORD(ix,x);
    k = (ix&0x7f800000)>>23;            /* extract exponent */
    if (k==0) {                         /* 0 or subnormal x */
        if ((ix&0x7fffffff)==0) return x; /* +-0 */
        x *= two25;
        GET_FLOAT_WORD(ix,x);
        k = ((ix&0x7f800000)>>23) - 25;
        if (n< -50000) return tiny*x;   /*underflow*/
    }
    if (k==0xff) return x+x;            /* NaN or Inf */
    k = k+n;
    if (k >  0xfe) return huge*copysignf(huge,x); /* overflow  */
    if (k > 0)                          /* normal result */
        {SET_FLOAT_WORD(x,(ix&0x807fffff)|(k<<23)); return x;}
    if (k <= -25) {
        if (n > 50000)  /* in case integer overflow in n+k */
            return huge*copysignf(huge,x);      /*overflow*/
        else { return tiny*copysignf(tiny,x); } /*underflow*/
    }
    k += 25;                            /* subnormal result */
    SET_FLOAT_WORD(x,(ix&0x807fffff)|(k<<23));
    return x*twom25;
}


double ldexp(double x, int n)
{
    static const double
        two54   =  1.80143985094819840000e+16, /* 0x43500000, 0x00000000 */
        twom54  =  5.55111512312578270212e-17, /* 0x3C900000, 0x00000000 */
        huge   = 1.0e+300,
        tiny   = 1.0e-300;

    int32_t k,hx,lx;
    EXTRACT_WORDS(hx,lx,x);
    k = (hx&0x7ff00000)>>20;            /* extract exponent */
    if (k==0) {                         /* 0 or subnormal x */
        if ((lx|(hx&0x7fffffff))==0) return x; /* +-0 */
        x *= two54;
        GET_HIGH_WORD(hx,x);
        k = ((hx&0x7ff00000)>>20) - 54;
        if (n< -50000) return tiny*x;   /*underflow*/
    }
    if (k==0x7ff) return x+x;           /* NaN or Inf */
    k = k+n;
    if (k >  0x7fe) return huge*copysign(huge,x); /* overflow  */
    if (k > 0)                          /* normal result */
        {SET_HIGH_WORD(x,(hx&0x800fffff)|(k<<20)); return x;}
    if (k <= -54) {
        if (n > 50000)  /* in case integer overflow in n+k */
            return huge*copysign(huge,x);       /*overflow*/
        else { return tiny*copysign(tiny,x); }  /*underflow*/
    }
    k += 54;                            /* subnormal result */
    SET_HIGH_WORD(x,(hx&0x800fffff)|(k<<20));
    return x*twom54;
}


float ceilf(float x)
{
    static const float huge = 1.0e30;

    int32_t i0,j0;
    u_int32_t i;

    GET_FLOAT_WORD(i0,x);
    j0 = ((i0>>23)&0xff)-0x7f;
    if(j0<23) {
        if(j0<0) {      /* raise inexact if x != 0 */
            if(huge+x>(float)0.0) {/* return 0*sign(x) if |x|<1 */
                if(i0<0) {i0=0x80000000;}
                else if(i0!=0) { i0=0x3f800000;}
            }
        } else {
            i = (u_int32_t)(0x007fffff)>>j0;
            if((i0&i)==0) return x; /* x is integral */
            if(huge+x>(float)0.0) {     /* raise inexact flag */
                if(i0>0) i0 += (u_int32_t)(0x00800000)>>j0;
                i0 &= (~i);
            }
        }
    } else {
        if(j0==0x80) return x+x;        /* inf or NaN */
        else return x;          /* x is integral */
    }
    SET_FLOAT_WORD(x,i0);
    return x;
}


double ceil(double x)
{
    static const double huge = 1.0e300;

    int32_t i0,i1,j0;
    u_int32_t i,j;
    EXTRACT_WORDS(i0,i1,x);
    j0 = ((i0>>20)&0x7ff)-0x3ff;
    if(j0<20) {
        if(j0<0) {      /* raise inexact if x != 0 */
            if(huge+x>0.0) {/* return 0*sign(x) if |x|<1 */
                if(i0<0) {i0=0x80000000;i1=0;}
                else if((i0|i1)!=0) { i0=0x3ff00000;i1=0;}
            }
        } else {
            i = (u_int32_t)(0x000fffff)>>j0;
            if(((i0&i)|i1)==0) return x; /* x is integral */
            if(huge+x>0.0) {    /* raise inexact flag */
                if(i0>0) i0 += (u_int32_t)(0x00100000)>>j0;
                i0 &= (~i); i1=0;
            }
        }
    } else if (j0>51) {
        if(j0==0x400) return x+x;       /* inf or NaN */
        else return x;          /* x is integral */
    } else {
        i = ((u_int32_t)(0xffffffff))>>(j0-20);
        if((i1&i)==0) return x; /* x is integral */
        if(huge+x>0.0) {                /* raise inexact flag */
            if(i0>0) {
                if(j0==20) i0+=1;
                else {
                    j = i1 + ((u_int32_t)1<<(52-j0));
                    if(j<(u_int32_t)i1) i0+=1;  /* got a carry */
                    i1 = j;
                }
            }
            i1 &= (~i);
        }
    }
    INSERT_WORDS(x,i0,i1);
    return x;
}


float floorf(float x)
{
    static const float huge = 1.0e30;

    int32_t i0,j0;
    u_int32_t i;
    GET_FLOAT_WORD(i0,x);
    j0 = ((i0>>23)&0xff)-0x7f;
    if(j0<23) {
        if(j0<0) {      /* raise inexact if x != 0 */
            if(huge+x>(float)0.0) {/* return 0*sign(x) if |x|<1 */
                if(i0>=0) {i0=0;}
                else if((i0&0x7fffffff)!=0) { i0=0xbf800000;}
            }
        } else {
            i = (u_int32_t)(0x007fffff)>>j0;
            if((i0&i)==0) return x; /* x is integral */
            if(huge+x>(float)0.0) {     /* raise inexact flag */
                if(i0<0) i0 += (u_int32_t)(0x00800000)>>j0;
                i0 &= (~i);
            }
        }
    } else {
        if(j0==0x80) return x+x;        /* inf or NaN */
        else return x;          /* x is integral */
    }
    SET_FLOAT_WORD(x,i0);
    return x;
}


double floor(double x)
{
    static const double huge = 1.0e300;

    int32_t i0,i1,j0;
    u_int32_t i,j;
    EXTRACT_WORDS(i0,i1,x);
    j0 = ((i0>>20)&0x7ff)-0x3ff;
    if(j0<20) {
        if(j0<0) {      /* raise inexact if x != 0 */
            if(huge+x>0.0) {/* return 0*sign(x) if |x|<1 */
                if(i0>=0) {i0=i1=0;}
                else if(((i0&0x7fffffff)|i1)!=0)
                    { i0=0xbff00000;i1=0;}
            }
        } else {
            i = (u_int32_t)(0x000fffff)>>j0;
            if(((i0&i)|i1)==0) return x; /* x is integral */
            if(huge+x>0.0) {    /* raise inexact flag */
                if(i0<0) i0 += (u_int32_t)(0x00100000)>>j0;
                i0 &= (~i); i1=0;
            }
        }
    } else if (j0>51) {
        if(j0==0x400) return x+x;       /* inf or NaN */
        else return x;          /* x is integral */
    } else {
        i = ((u_int32_t)(0xffffffff))>>(j0-20);
        if((i1&i)==0) return x; /* x is integral */
        if(huge+x>0.0) {                /* raise inexact flag */
            if(i0<0) {
                if(j0==20) i0+=1;
                else {
                    j = i1+((u_int32_t)1<<(52-j0));
                    if(j<(u_int32_t)i1) i0 +=1 ;        /* got a carry */
                    i1=j;
                }
            }
            i1 &= (~i);
        }
    }
    INSERT_WORDS(x,i0,i1);
    return x;
}


float roundf(float x)
{
  u_int32_t w;
  /* Most significant word, least significant word. */
  int exponent_less_127;

  GET_FLOAT_WORD(w, x);

  /* Extract exponent field. */
  exponent_less_127 = (int)((w & 0x7f800000) >> 23) - 127;

  if (exponent_less_127 < 23)
    {
      if (exponent_less_127 < 0)
        {
          w &= 0x80000000;
          if (exponent_less_127 == -1)
            /* Result is +1.0 or -1.0. */
            w |= ((u_int32_t)127 << 23);
        }
      else
        {
          u_int32_t exponent_mask = (u_int32_t)0x007fffff >> exponent_less_127;
          if ((w & exponent_mask) == 0)
            /* x has an integral value. */
            return x;

          w += (u_int32_t)0x00400000 >> exponent_less_127;
          w &= ~exponent_mask;
        }
    }
  else
    {
      if (exponent_less_127 == 128)
        /* x is NaN or infinite. */
        return x + x;
      else
        return x;
    }
  SET_FLOAT_WORD(x, w);
  return x;
}


double round(double x)
{
  /* Most significant word, least significant word. */
  int32_t msw, exponent_less_1023;
  u_int32_t lsw;

  EXTRACT_WORDS(msw, lsw, x);

  /* Extract exponent field. */
  exponent_less_1023 = ((msw & 0x7ff00000) >> 20) - 1023;

  if (exponent_less_1023 < 20)
    {
      if (exponent_less_1023 < 0)
        {
          msw &= 0x80000000;
          if (exponent_less_1023 == -1)
            /* Result is +1.0 or -1.0. */
            msw |= ((u_int32_t)1023 << 20);
          lsw = 0;
        }
      else
        {
          u_int32_t exponent_mask = (u_int32_t)0x000fffff >> exponent_less_1023;
          if ((msw & exponent_mask) == 0 && lsw == 0)
            /* x in an integral value. */
            return x;

          msw += (u_int32_t)0x00080000 >> exponent_less_1023;
          msw &= ~exponent_mask;
          lsw = 0;
        }
    }
  else if (exponent_less_1023 > 51)
    {
      if (exponent_less_1023 == 1024)
        /* x is NaN or infinite. */
        return x + x;
      else
        return x;
    }
  else
    {
      u_int32_t exponent_mask = 0xffffffff >> (exponent_less_1023 - 20);
      u_int32_t tmp;

      if ((lsw & exponent_mask) == 0)
        /* x is an integral value. */
        return x;

      tmp = lsw + ((u_int32_t)1 << (51 - exponent_less_1023));
      if (tmp < lsw)
        msw += 1;
      lsw = tmp;

      lsw &= ~exponent_mask;
    }
  INSERT_WORDS(x, msw, lsw);

  return x;
}


//  Trancendental functions


/* This array is like the one in e_rem_pio2.c, but the numbers are
   single precision and the last 8 bits are forced to 0.  */
static const int32_t npio2f_hw[] = {
0x3fc90f00, 0x40490f00, 0x4096cb00, 0x40c90f00, 0x40fb5300, 0x4116cb00,
0x412fed00, 0x41490f00, 0x41623100, 0x417b5300, 0x418a3a00, 0x4196cb00,
0x41a35c00, 0x41afed00, 0x41bc7e00, 0x41c90f00, 0x41d5a000, 0x41e23100,
0x41eec200, 0x41fb5300, 0x4203f200, 0x420a3a00, 0x42108300, 0x4216cb00,
0x421d1400, 0x42235c00, 0x4229a500, 0x422fed00, 0x42363600, 0x423c7e00,
0x4242c700, 0x42490f00
};

static int32_t rem_pio2f(float x, float *y) property(arg_mem_only) // loop_free
{
    /*
     * invpio2:  24 bits of 2/pi
     * pio2_1:   first  17 bit of pi/2
     * pio2_1t:  pi/2 - pio2_1
     * pio2_2:   second 17 bit of pi/2
     * pio2_2t:  pi/2 - (pio2_1+pio2_2)
     * pio2_3:   third  17 bit of pi/2
     * pio2_3t:  pi/2 - (pio2_1+pio2_2+pio2_3)
     */

    static const float
        zero =  0.0000000000e+00, /* 0x00000000 */
        half =  5.0000000000e-01, /* 0x3f000000 */
        two8 =  2.5600000000e+02, /* 0x43800000 */
        invpio2 =  6.3661980629e-01, /* 0x3f22f984 */
        pio2_1  =  1.5707855225e+00, /* 0x3fc90f80 */
        pio2_1t =  1.0804334124e-05, /* 0x37354443 */
        pio2_2  =  1.0804273188e-05, /* 0x37354400 */
        pio2_2t =  6.0770999344e-11, /* 0x2e85a308 */
        pio2_3  =  6.0770943833e-11, /* 0x2e85a300 */
        pio2_3t =  6.1232342629e-17; /* 0x248d3132 */

    float z,w,t,r,fn;
//  float tx[3];
    int32_t e0,i,j,nx,n,ix,hx;

    GET_FLOAT_WORD(hx,x);
    ix = hx&0x7fffffff;
    if(ix<=0x3f490fd8)   /* |x| ~<= pi/4 , no need for reduction */
        {y[0] = x; y[1] = 0; return 0;}
    if(ix<0x4016cbe4) {  /* |x| < 3pi/4, special case with n=+-1 */
        if(hx>0) {
            z = x - pio2_1;
            if((ix&0xfffffff0)!=0x3fc90fd0) { /* 24+24 bit pi OK */
                y[0] = z - pio2_1t;
                y[1] = (z-y[0])-pio2_1t;
            } else {            /* near pi/2, use 24+24+24 bit pi */
                z -= pio2_2;
                y[0] = z - pio2_2t;
                y[1] = (z-y[0])-pio2_2t;
            }
            return 1;
        } else {        /* negative x */
            z = x + pio2_1;
            if((ix&0xfffffff0)!=0x3fc90fd0) { /* 24+24 bit pi OK */
                y[0] = z + pio2_1t;
                y[1] = (z-y[0])+pio2_1t;
            } else {            /* near pi/2, use 24+24+24 bit pi */
                z += pio2_2;
                y[0] = z + pio2_2t;
                y[1] = (z-y[0])+pio2_2t;
            }
            return -1;
        }
    }
//  if(ix<=0x43490f80) { /* |x| ~<= 2^7*(pi/2), medium size */
    {// use for huge numbers as well (lots of code, little to be gained)
        t  = fabsf(x);
        n  = (int32_t) (t*invpio2+half);
        fn = (float)n;
        r  = t-fn*pio2_1;
        w  = fn*pio2_1t;        /* 1st round good to 40 bit */
        if(0<=n&&n<32&&(ix&0xffffff00)!=npio2f_hw[n-1]) {
            y[0] = r-w; /* quick check no cancellation */
        } else {
            u_int32_t high;
            j  = ix>>23;
            y[0] = r-w;
            GET_FLOAT_WORD(high,y[0]);
            i = j-((high>>23)&0xff);
            if(i>8) {  /* 2nd iteration needed, good to 57 */
                t  = r;
                w  = fn*pio2_2;
                r  = t-w;
                w  = fn*pio2_2t-((t-r)-w);
                y[0] = r-w;
                GET_FLOAT_WORD(high,y[0]);
                i = j-((high>>23)&0xff);
                if(i>25)  {     /* 3rd iteration need, 74 bits acc */
                    t  = r;     /* will cover all possible cases */
                    w  = fn*pio2_3;
                    r  = t-w;
                    w  = fn*pio2_3t-((t-r)-w);
                    y[0] = r-w;
                }
            }
        }
        y[1] = (r-y[0])-w;
    }
//  else { /* all other (large) arguments */
//      if(ix>=0x7f800000) {            /* x is inf or NaN */
//          y[0]=y[1]=x-x; return 0;
//      }
//      /* set z = scalbn(|x|,ilogb(x)-7) */
//      e0      = (ix>>23)-134;         /* e0 = ilogb(z)-7; */
//      SET_FLOAT_WORD(z, ix - ((int32_t)(e0<<23)));
//      for(i=0;i<2;i++) {
//          tx[i] = (float)((int32_t)(z));
//          z     = (z-tx[i])*two8;
//      }
//      tx[2] = z;
//      nx = 3;
//      while(tx[nx-1]==zero) nx--;     /* skip zero term */
//      n  =  __kernel_rem_pio2f(tx,y,e0,nx,2,two_over_pi);
//  }
    if(hx<0) {y[0] = -y[0]; y[1] = -y[1]; return -n;}
    return n;
}


static const int32_t npio2_hw[] = {
0x3FF921FB, 0x400921FB, 0x4012D97C, 0x401921FB, 0x401F6A7A, 0x4022D97C,
0x4025FDBB, 0x402921FB, 0x402C463A, 0x402F6A7A, 0x4031475C, 0x4032D97C,
0x40346B9C, 0x4035FDBB, 0x40378FDB, 0x403921FB, 0x403AB41B, 0x403C463A,
0x403DD85A, 0x403F6A7A, 0x40407E4C, 0x4041475C, 0x4042106C, 0x4042D97C,
0x4043A28C, 0x40446B9C, 0x404534AC, 0x4045FDBB, 0x4046C6CB, 0x40478FDB,
0x404858EB, 0x404921FB,
};


static int32_t rem_pio2(double x, double *y) property(arg_mem_only) // loop_free
{
    /*
     * invpio2:  53 bits of 2/pi
     * pio2_1:   first  33 bit of pi/2
     * pio2_1t:  pi/2 - pio2_1
     * pio2_2:   second 33 bit of pi/2
     * pio2_2t:  pi/2 - (pio2_1+pio2_2)
     * pio2_3:   third  33 bit of pi/2
     * pio2_3t:  pi/2 - (pio2_1+pio2_2+pio2_3)
     */
    static const double
        zero =  0.00000000000000000000e+00, /* 0x00000000, 0x00000000 */
        half =  5.00000000000000000000e-01, /* 0x3FE00000, 0x00000000 */
        two24 =  1.67772160000000000000e+07, /* 0x41700000, 0x00000000 */
        invpio2 =  6.36619772367581382433e-01, /* 0x3FE45F30, 0x6DC9C883 */
        pio2_1  =  1.57079632673412561417e+00, /* 0x3FF921FB, 0x54400000 */
        pio2_1t =  6.07710050650619224932e-11, /* 0x3DD0B461, 0x1A626331 */
        pio2_2  =  6.07710050630396597660e-11, /* 0x3DD0B461, 0x1A600000 */
        pio2_2t =  2.02226624879595063154e-21, /* 0x3BA3198A, 0x2E037073 */
        pio2_3  =  2.02226624871116645580e-21, /* 0x3BA3198A, 0x2E000000 */
        pio2_3t =  8.47842766036889956997e-32; /* 0x397B839A, 0x252049C1 */

    double z,w,t,r,fn;
//  double tx[3];
    int32_t e0,i,j,nx,n,ix,hx;
    u_int32_t low;

    GET_HIGH_WORD(hx,x);                /* high word of x */
    ix = hx&0x7fffffff;
    if(ix<=0x3fe921fb)   /* |x| ~<= pi/4 , no need for reduction */
        {y[0] = x; y[1] = 0; return 0;}
    if(ix<0x4002d97c) {  /* |x| < 3pi/4, special case with n=+-1 */
        if(hx>0) {
            z = x - pio2_1;
            if(ix!=0x3ff921fb) {        /* 33+53 bit pi is good enough */
                y[0] = z - pio2_1t;
                y[1] = (z-y[0])-pio2_1t;
            } else {            /* near pi/2, use 33+33+53 bit pi */
                z -= pio2_2;
                y[0] = z - pio2_2t;
                y[1] = (z-y[0])-pio2_2t;
            }
            return 1;
        } else {        /* negative x */
            z = x + pio2_1;
            if(ix!=0x3ff921fb) {        /* 33+53 bit pi is good enough */
                y[0] = z + pio2_1t;
                y[1] = (z-y[0])+pio2_1t;
            } else {            /* near pi/2, use 33+33+53 bit pi */
                z += pio2_2;
                y[0] = z + pio2_2t;
                y[1] = (z-y[0])+pio2_2t;
            }
            return -1;
        }
    }
//  if(ix<=0x413921fb) { /* |x| ~<= 2^19*(pi/2), medium size */
    {// use for huge numbers as well (lots of code, little to be gained)
        t  = fabs(x);
        n  = (int32_t) (t*invpio2+half);
        fn = (double)n;
        r  = t-fn*pio2_1;
        w  = fn*pio2_1t;        /* 1st round good to 85 bit */
        if(0<=n&&n<32&&ix!=npio2_hw[n-1]) {
            y[0] = r-w; /* quick check no cancellation */
        } else {
            u_int32_t high;
            j  = ix>>20;
            y[0] = r-w;
            GET_HIGH_WORD(high,y[0]);
            i = j-((high>>20)&0x7ff);
            if(i>16) {  /* 2nd iteration needed, good to 118 */
                t  = r;
                w  = fn*pio2_2;
                r  = t-w;
                w  = fn*pio2_2t-((t-r)-w);
                y[0] = r-w;
                GET_HIGH_WORD(high,y[0]);
                i = j-((high>>20)&0x7ff);
                if(i>49)  {     /* 3rd iteration need, 151 bits acc */
                    t  = r;     /* will cover all possible cases */
                    w  = fn*pio2_3;
                    r  = t-w;
                    w  = fn*pio2_3t-((t-r)-w);
                    y[0] = r-w;
                }
            }
        }
        y[1] = (r-y[0])-w;
    }
//  else { /* all other (large) arguments */
//      if(ix>=0x7ff00000) {            /* x is inf or NaN */
//          y[0]=y[1]=x-x; return 0;
//      }
//      /* set z = scalbn(|x|,ilogb(x)-23) */
//      GET_LOW_WORD(low,x);
//      SET_LOW_WORD(z,low);
//      e0      = (ix>>20)-1046;        /* e0 = ilogb(z)-23; */
//      SET_HIGH_WORD(z, ix - ((int32_t)(e0<<20)));
//      for(i=0;i<2;i++) {
//          tx[i] = (double)((int32_t)(z));
//          z     = (z-tx[i])*two24;
//      }
//      tx[2] = z;
//      nx = 3;
//      while(tx[nx-1]==zero) nx--;     /* skip zero term */
//      n  =  __kernel_rem_pio2(tx,y,e0,nx,2,two_over_pi);
//  }
    if(hx<0) {y[0] = -y[0]; y[1] = -y[1]; return -n;}
    return n;
}


static float kernel_cosf(float x, float y) property(functional) //l loop_free
{
    static const float
        one =  1.0000000000e+00, /* 0x3f800000 */
        C1  =  4.1666667908e-02, /* 0x3d2aaaab */
        C2  = -1.3888889225e-03, /* 0xbab60b61 */
        C3  =  2.4801587642e-05, /* 0x37d00d01 */
        C4  = -2.7557314297e-07, /* 0xb493f27c */
        C5  =  2.0875723372e-09, /* 0x310f74f6 */
        C6  = -1.1359647598e-11; /* 0xad47d74e */

    float a,hz,z,r,qx;
    int32_t ix;
    GET_FLOAT_WORD(ix,x);
    ix &= 0x7fffffff;                   /* ix = |x|'s high word*/
    if(ix<0x32000000) {                 /* if x < 2**27 */
        if(((int)x)==0) return one;             /* generate inexact */
    }
    z  = x*x;
    r  = z*(C1+z*(C2+z*(C3+z*(C4+z*(C5+z*C6)))));
    if(ix < 0x3e99999a)                         /* if |x| < 0.3 */
        return one - ((float)0.5*z - (z*r - x*y));
    else {
        if(ix > 0x3f480000) {           /* x > 0.78125 */
            qx = (float)0.28125;
        } else {
            SET_FLOAT_WORD(qx,ix-0x01000000);   /* x/4 */
        }
        hz = (float)0.5*z-qx;
        a  = one-qx;
        return a - (hz - (z*r-x*y));
    }
}


static double kernel_cos(double x, double y) property(functional) // loop_free
{
    static const double
        one =  1.00000000000000000000e+00, /* 0x3FF00000, 0x00000000 */
        C1  =  4.16666666666666019037e-02, /* 0x3FA55555, 0x5555554C */
        C2  = -1.38888888888741095749e-03, /* 0xBF56C16C, 0x16C15177 */
        C3  =  2.48015872894767294178e-05, /* 0x3EFA01A0, 0x19CB1590 */
        C4  = -2.75573143513906633035e-07, /* 0xBE927E4F, 0x809C52AD */
        C5  =  2.08757232129817482790e-09, /* 0x3E21EE9E, 0xBDB4B1C4 */
        C6  = -1.13596475577881948265e-11; /* 0xBDA8FAE9, 0xBE8838D4 */

    double a,hz,z,r,qx;
    int32_t ix;
    GET_HIGH_WORD(ix,x);
    ix &= 0x7fffffff;                   /* ix = |x|'s high word*/
    if(ix<0x3e400000) {                 /* if x < 2**27 */
        if(((int)x)==0) return one;             /* generate inexact */
    }
    z  = x*x;
    r  = z*(C1+z*(C2+z*(C3+z*(C4+z*(C5+z*C6)))));
    if(ix < 0x3FD33333)                         /* if |x| < 0.3 */
        return one - (0.5*z - (z*r - x*y));
    else {
        if(ix > 0x3fe90000) {           /* x > 0.78125 */
            qx = 0.28125;
        } else {
            INSERT_WORDS(qx,ix-0x00200000,0);   /* x/4 */
        }
        hz = 0.5*z-qx;
        a  = one-qx;
        return a - (hz - (z*r-x*y));
    }
}


static float kernel_sinf(float x, float y, int iy) property(functional) // loop_free
{
    static const float
        half =  5.0000000000e-01,/* 0x3f000000 */
        S1  = -1.6666667163e-01, /* 0xbe2aaaab */
        S2  =  8.3333337680e-03, /* 0x3c088889 */
        S3  = -1.9841270114e-04, /* 0xb9500d01 */
        S4  =  2.7557314297e-06, /* 0x3638ef1b */
        S5  = -2.5050759689e-08, /* 0xb2d72f34 */
        S6  =  1.5896910177e-10; /* 0x2f2ec9d3 */

    float z,r,v;
    int32_t ix;
    GET_FLOAT_WORD(ix,x);
    ix &= 0x7fffffff;                   /* high word of x */
    if(ix<0x32000000)                   /* |x| < 2**-27 */
        {if((int)x==0) return x;}               /* generate inexact */
    z   =  x*x;
    v   =  z*x;
    r   =  S2+z*(S3+z*(S4+z*(S5+z*S6)));
    if(iy==0) return x+v*(S1+z*r);
    else      return x-((z*(half*y-v*r)-y)-v*S1);
}


static double kernel_sin(double x, double y, int iy) property(functional) // loop_free
{
    static const double
        half =  5.00000000000000000000e-01, /* 0x3FE00000, 0x00000000 */
        S1  = -1.66666666666666324348e-01, /* 0xBFC55555, 0x55555549 */
        S2  =  8.33333333332248946124e-03, /* 0x3F811111, 0x1110F8A6 */
        S3  = -1.98412698298579493134e-04, /* 0xBF2A01A0, 0x19C161D5 */
        S4  =  2.75573137070700676789e-06, /* 0x3EC71DE3, 0x57B1FE7D */
        S5  = -2.50507602534068634195e-08, /* 0xBE5AE5E6, 0x8A2B9CEB */
        S6  =  1.58969099521155010221e-10; /* 0x3DE5D93A, 0x5ACFD57C */

    double z,r,v;
    int32_t ix;
    GET_HIGH_WORD(ix,x);
    ix &= 0x7fffffff;                   /* high word of x */
    if(ix<0x3e400000)                   /* |x| < 2**-27 */
        {if((int)x==0) return x;}               /* generate inexact */
    z   =  x*x;
    v   =  z*x;
    r   =  S2+z*(S3+z*(S4+z*(S5+z*S6)));
    if(iy==0) return x+v*(S1+z*r);
    else      return x-((z*(half*y-v*r)-y)-v*S1);
}


float cosf(float x)
{
    static const float one=1.0;

    float y[2],z=0.0;
    int32_t n,ix;

    GET_FLOAT_WORD(ix,x);

    /* |x| ~< pi/4 */
    ix &= 0x7fffffff;
    if(ix <= 0x3f490fd8) return kernel_cosf(x,z);

    /* cos(Inf or NaN) is NaN */
    else if (ix>=0x7f800000) return x-x;

    /* argument reduction needed */
    else {
        n = rem_pio2f(x,y);
        switch(n&3) {
        case 0 : return  kernel_cosf(y[0],y[1]);
        case 1 : return -kernel_sinf(y[0],y[1],1);
        case 2 : return -kernel_cosf(y[0],y[1]);
        default: return  kernel_sinf(y[0],y[1],1);
        }
    }
}


double cos(double x)
{
    double y[2],z=0.0;
    int32_t n, ix;

    /* High word of x. */
    GET_HIGH_WORD(ix,x);

    /* |x| ~< pi/4 */
    ix &= 0x7fffffff;
    if(ix <= 0x3fe921fb) return kernel_cos(x,z);

    /* cos(Inf or NaN) is NaN */
    else if (ix>=0x7ff00000) return x-x;

    /* argument reduction needed */
    else {
        n = rem_pio2(x,y);
        switch(n&3) {
        case 0 : return  kernel_cos(y[0],y[1]);
        case 1 : return -kernel_sin(y[0],y[1],1);
        case 2 : return -kernel_cos(y[0],y[1]);
        default: return  kernel_sin(y[0],y[1],1);
        }
    }
}


float sinf(float x)
{
    float y[2],z=0.0;
    int32_t n, ix;

    GET_FLOAT_WORD(ix,x);

    /* |x| ~< pi/4 */
    ix &= 0x7fffffff;
    if(ix <= 0x3f490fd8) return kernel_sinf(x,z,0);

    /* sin(Inf or NaN) is NaN */
    else if (ix>=0x7f800000) return x-x;

    /* argument reduction needed */
    else {
        n = rem_pio2f(x,y);
        switch(n&3) {
        case 0 : return  kernel_sinf(y[0],y[1],1);
        case 1 : return  kernel_cosf(y[0],y[1]);
        case 2 : return -kernel_sinf(y[0],y[1],1);
        default: return -kernel_cosf(y[0],y[1]);
        }
    }
}


double sin(double x)
{
    double y[2],z=0.0;
    int32_t n, ix;

    /* High word of x. */
    GET_HIGH_WORD(ix,x);

    /* |x| ~< pi/4 */
    ix &= 0x7fffffff;
    if(ix <= 0x3fe921fb) return kernel_sin(x,z,0);

    /* sin(Inf or NaN) is NaN */
    else if (ix>=0x7ff00000) return x-x;

    /* argument reduction needed */
    else {
        n = rem_pio2(x,y);
        switch(n&3) {
        case 0 : return  kernel_sin(y[0],y[1],1);
        case 1 : return  kernel_cos(y[0],y[1]);
        case 2 : return -kernel_sin(y[0],y[1],1);
        default: return -kernel_cos(y[0],y[1]);
        }
    }
}


float expf(float x)     /* default IEEE double exp */
{
    static const float huge = 1.0e+30;

    static const float
        one     = 1.0,
        halF[2] = {0.5,-0.5,},
        twom100 = 7.8886090522e-31,      /* 2**-100=0x0d800000 */
        o_threshold=  8.8721679688e+01,  /* 0x42b17180 */
        u_threshold= -1.0397208405e+02,  /* 0xc2cff1b5 */
        ln2HI[2]   ={ 6.9313812256e-01,         /* 0x3f317180 */
                      -6.9313812256e-01,},      /* 0xbf317180 */
        ln2LO[2]   ={ 9.0580006145e-06,         /* 0x3717f7d1 */
                      -9.0580006145e-06,},      /* 0xb717f7d1 */
        invln2 =  1.4426950216e+00,             /* 0x3fb8aa3b */
        P1   =  1.6666667163e-01, /* 0x3e2aaaab */
        P2   = -2.7777778450e-03, /* 0xbb360b61 */
        P3   =  6.6137559770e-05, /* 0x388ab355 */
        P4   = -1.6533901999e-06, /* 0xb5ddea0e */
        P5   =  4.1381369442e-08; /* 0x3331bb4c */

    float y,hi,lo,c,t;
    int32_t k,xsb;
    u_int32_t hx;

    GET_FLOAT_WORD(hx,x);
    xsb = (hx>>31)&1;           /* sign bit of x */
    hx &= 0x7fffffff;           /* high word of |x| */

    /* filter out non-finite argument */
    if(hx >= 0x42b17218) {                      /* if |x|>=88.721... */
        if(hx>0x7f800000)
            return x+x;                 /* NaN */
        if(hx==0x7f800000)
            return (xsb==0)? x:0.0;             /* exp(+-inf)={inf,0} */
        if(x > o_threshold) return /*huge*huge*/ float_pos_inf(); /* overflow */
        if(x < u_threshold) return /*twom100*twom100*/ float_zero(); /* underflow */
    }

    /* argument reduction */
    if(hx > 0x3eb17218) {               /* if  |x| > 0.5 ln2 */
        if(hx < 0x3F851592) {   /* and |x| < 1.5 ln2 */
            hi = x-ln2HI[xsb]; lo=ln2LO[xsb]; k = 1-xsb-xsb;
        } else {
            k  = invln2*x+halF[xsb];
            t  = k;
            hi = x - t*ln2HI[0];        /* t*ln2HI is exact here */
            lo = t*ln2LO[0];
        }
        x  = hi - lo;
    }
    else if(hx < 0x31800000)  { /* when |x|<2**-28 */
        if(huge+x>one) return one+x;/* trigger inexact */
    }
    else k = 0;

    /* x is now in primary range */
    t  = x*x;
    c  = x - t*(P1+t*(P2+t*(P3+t*(P4+t*P5))));
    if(k==0)    return one-((x*c)/(c-(float)2.0)-x);
    else        y = one-((lo-(x*c)/((float)2.0-c))-hi);
    if(k >= -125) {
        u_int32_t hy;
        GET_FLOAT_WORD(hy,y);
        SET_FLOAT_WORD(y,hy+(k<<23));   /* add k to y's exponent */
        return y;
    } else {
        u_int32_t hy;
        GET_FLOAT_WORD(hy,y);
        SET_FLOAT_WORD(y,hy+((k+100)<<23));     /* add k to y's exponent */
        return y*twom100;
    }
}



double exp(double x)    /* default IEEE double exp */
{
    static const double
        one     = 1.0,
        halF[2] = {0.5,-0.5,},
        huge    = 1.0e+300,
        twom1000= 9.33263618503218878990e-302,     /* 2**-1000=0x01700000,0*/
        o_threshold=  7.09782712893383973096e+02,  /* 0x40862E42, 0xFEFA39EF */
        u_threshold= -7.45133219101941108420e+02,  /* 0xc0874910, 0xD52D3051 */
        ln2HI[2]   ={ 6.93147180369123816490e-01,  /* 0x3fe62e42, 0xfee00000 */
                      -6.93147180369123816490e-01,},/* 0xbfe62e42, 0xfee00000 */
        ln2LO[2]   ={ 1.90821492927058770002e-10,  /* 0x3dea39ef, 0x35793c76 */
                      -1.90821492927058770002e-10,},/* 0xbdea39ef, 0x35793c76 */
        invln2 =  1.44269504088896338700e+00, /* 0x3ff71547, 0x652b82fe */
        P1   =  1.66666666666666019037e-01, /* 0x3FC55555, 0x5555553E */
        P2   = -2.77777777770155933842e-03, /* 0xBF66C16C, 0x16BEBD93 */
        P3   =  6.61375632143793436117e-05, /* 0x3F11566A, 0xAF25DE2C */
        P4   = -1.65339022054652515390e-06, /* 0xBEBBBD41, 0xC5D26BF1 */
        P5   =  4.13813679705723846039e-08; /* 0x3E663769, 0x72BEA4D0 */

    double y,hi,lo,c,t;
    int32_t k,xsb;
    u_int32_t hx;

    GET_HIGH_WORD(hx,x);
    xsb = (hx>>31)&1;           /* sign bit of x */
    hx &= 0x7fffffff;           /* high word of |x| */

    /* filter out non-finite argument */
    if(hx >= 0x40862E42) {                      /* if |x|>=709.78... */
        if(hx>=0x7ff00000) {
            u_int32_t lx;
            GET_LOW_WORD(lx,x);
            if(((hx&0xfffff)|lx)!=0)
                return x+x;             /* NaN */
            else return (xsb==0)? x:0.0;        /* exp(+-inf)={inf,0} */
        }
        if(x > o_threshold) return huge*huge; /* overflow */
        if(x < u_threshold) return twom1000*twom1000; /* underflow */
    }

    /* argument reduction */
    if(hx > 0x3fd62e42) {               /* if  |x| > 0.5 ln2 */
        if(hx < 0x3FF0A2B2) {   /* and |x| < 1.5 ln2 */
            hi = x-ln2HI[xsb]; lo=ln2LO[xsb]; k = 1-xsb-xsb;
        } else {
            k  = invln2*x+halF[xsb];
            t  = k;
            hi = x - t*ln2HI[0];        /* t*ln2HI is exact here */
            lo = t*ln2LO[0];
        }
        x  = hi - lo;
    }
    else if(hx < 0x3e300000)  { /* when |x|<2**-28 */
        if(huge+x>one) return one+x;/* trigger inexact */
    }
    else k = 0;

    /* x is now in primary range */
    t  = x*x;
    c  = x - t*(P1+t*(P2+t*(P3+t*(P4+t*P5))));
    if(k==0)    return one-((x*c)/(c-2.0)-x);
    else        y = one-((lo-(x*c)/(2.0-c))-hi);
    if(k >= -1021) {
        u_int32_t hy;
        GET_HIGH_WORD(hy,y);
        SET_HIGH_WORD(y,hy+(k<<20));    /* add k to y's exponent */
        return y;
    } else {
        u_int32_t hy;
        GET_HIGH_WORD(hy,y);
        SET_HIGH_WORD(y,hy+((k+1000)<<20));     /* add k to y's exponent */
        return y*twom1000;
    }
}



float logf(float x)
{
    static const float
        zero   =  0.0,
        ln2_hi =   6.9313812256e-01,    /* 0x3f317180 */
        ln2_lo =   9.0580006145e-06,    /* 0x3717f7d1 */
        two25 =    3.355443200e+07,     /* 0x4c000000 */
        Lg1 = 6.6666668653e-01, /* 3F2AAAAB */
        Lg2 = 4.0000000596e-01, /* 3ECCCCCD */
        Lg3 = 2.8571429849e-01, /* 3E924925 */
        Lg4 = 2.2222198546e-01, /* 3E638E29 */
        Lg5 = 1.8183572590e-01, /* 3E3A3325 */
        Lg6 = 1.5313838422e-01, /* 3E1CD04F */
        Lg7 = 1.4798198640e-01; /* 3E178897 */

    float hfsq,f,s,z,R,w,t1,t2,dk;
    int32_t k,ix,i,j;

    GET_FLOAT_WORD(ix,x);

    k=0;
    if (ix < 0x00800000) {                      /* x < 2**-126  */
        if ((ix&0x7fffffff)==0)
            return /*-two25/zero*/ float_neg_inf();             /* log(+-0)=-inf */
        if (ix<0) return (x-x)/zero;    /* log(-#) = NaN */
        k -= 25; x *= two25; /* subnormal number, scale up x */
        GET_FLOAT_WORD(ix,x);
    }
    if (ix >= 0x7f800000) return x+x;
    k += (ix>>23)-127;
    ix &= 0x007fffff;
    i = (ix+((u_int32_t)0x95f64<<3))&0x800000;
    SET_FLOAT_WORD(x,ix|(i^0x3f800000));        /* normalize x or x/2 */
    k += (i>>23);
    f = x-(float)1.0;
    if((0x007fffff&(15+ix))<16) {       /* |f| < 2**-20 */
        if(f==zero) {if(k==0) return zero;
                     else {dk=(float)k; return dk*ln2_hi+dk*ln2_lo;}}
        R = f*f*((float)0.5-(float)0.33333333333333333*f);
        if(k==0) return f-R;
        else {dk=(float)k; return dk*ln2_hi-((R-dk*ln2_lo)-f);}
    }
    s = f/((float)2.0+f);
    dk = (float)k;
    z = s*s;
    i = ix-((u_int32_t)0x6147a<<3);
    w = z*z;
    j = ((u_int32_t)0x6b851<<3)-ix;
    t1= w*(Lg2+w*(Lg4+w*Lg6));
    t2= z*(Lg1+w*(Lg3+w*(Lg5+w*Lg7)));
    i |= j;
    R = t2+t1;
    if(i>0) {
        hfsq=(float)0.5*f*f;
        if(k==0) return f-(hfsq-s*(hfsq+R));
        else     return dk*ln2_hi-((hfsq-(s*(hfsq+R)+dk*ln2_lo))-f);
    } else {
        if(k==0) return f-s*(f-R);
        else     return dk*ln2_hi-((s*(f-R)-dk*ln2_lo)-f);
    }
}


double log(double x)
{
    static const double
        zero   =  0.0,
        ln2_hi  =  6.93147180369123816490e-01,  /* 3fe62e42 fee00000 */
        ln2_lo  =  1.90821492927058770002e-10,  /* 3dea39ef 35793c76 */
        two54   =  1.80143985094819840000e+16,  /* 43500000 00000000 */
        Lg1 = 6.666666666666735130e-01,  /* 3FE55555 55555593 */
        Lg2 = 3.999999999940941908e-01,  /* 3FD99999 9997FA04 */
        Lg3 = 2.857142874366239149e-01,  /* 3FD24924 94229359 */
        Lg4 = 2.222219843214978396e-01,  /* 3FCC71C5 1D8E78AF */
        Lg5 = 1.818357216161805012e-01,  /* 3FC74664 96CB03DE */
        Lg6 = 1.531383769920937332e-01,  /* 3FC39A09 D078C69F */
        Lg7 = 1.479819860511658591e-01;  /* 3FC2F112 DF3E5244 */

    double hfsq,f,s,z,R,w,t1,t2,dk;
    int32_t k,hx,i,j;
    u_int32_t lx;

    EXTRACT_WORDS(hx,lx,x);

    k=0;
    if (hx < 0x00100000) {                      /* x < 2**-1022  */
        if (((hx&0x7fffffff)|lx)==0)
            return /*-two54/zero*/ float_neg_inf();             /* log(+-0)=-inf */
        if (hx<0) return (x-x)/zero;    /* log(-#) = NaN */
        k -= 54; x *= two54; /* subnormal number, scale up x */
        GET_HIGH_WORD(hx,x);
    }
    if (hx >= 0x7ff00000) return x+x;
    k += (hx>>20)-1023;
    hx &= 0x000fffff;
    i = (hx+0x95f64)&0x100000;
    SET_HIGH_WORD(x,hx|(i^0x3ff00000)); /* normalize x or x/2 */
    k += (i>>20);
    f = x-1.0;
    if((0x000fffff&(2+hx))<3) { /* |f| < 2**-20 */
        if(f==zero) {if(k==0) return zero;
                     else {dk=(double)k; return dk*ln2_hi+dk*ln2_lo;}}
        R = f*f*(0.5-0.33333333333333333*f);
        if(k==0) return f-R;
        else {dk=(double)k; return dk*ln2_hi-((R-dk*ln2_lo)-f);}
    }
    s = f/(2.0+f);
    dk = (double)k;
    z = s*s;
    i = hx-0x6147a;
    w = z*z;
    j = 0x6b851-hx;
    t1= w*(Lg2+w*(Lg4+w*Lg6));
    t2= z*(Lg1+w*(Lg3+w*(Lg5+w*Lg7)));
    i |= j;
    R = t2+t1;
    if(i>0) {
        hfsq=0.5*f*f;
        if(k==0) return f-(hfsq-s*(hfsq+R));
        else     return dk*ln2_hi-((hfsq-(s*(hfsq+R)+dk*ln2_lo))-f);
    } else {
        if(k==0) return f-s*(f-R);
        else     return dk*ln2_hi-((s*(f-R)-dk*ln2_lo)-f);
    }
}


float log10f(float x)
{
    static const float
        zero   =  0.0,
        two25      =  3.3554432000e+07, /* 0x4c000000 */
        ivln10     =  4.3429449201e-01, /* 0x3ede5bd9 */
        log10_2hi  =  3.0102920532e-01, /* 0x3e9a2080 */
        log10_2lo  =  7.9034151668e-07; /* 0x355427db */

    float y,z;
    int32_t i,k,hx;

    GET_FLOAT_WORD(hx,x);

    k=0;
    if (hx < 0x00800000) {                  /* x < 2**-126  */
        if ((hx&0x7fffffff)==0)
            return /*-two25/zero*/ float_neg_inf();             /* log(+-0)=-inf */
        if (hx<0) return (x-x)/zero;        /* log(-#) = NaN */
        k -= 25; x *= two25; /* subnormal number, scale up x */
        GET_FLOAT_WORD(hx,x);
    }
    if (hx >= 0x7f800000) return x+x;
    k += (hx>>23)-127;
    i  = ((u_int32_t)k&0x80000000)>>31;
    hx = (hx&0x007fffff)|((0x7f-i)<<23);
    y  = (float)(k+i);
    SET_FLOAT_WORD(x,hx);
    z  = y*log10_2lo + ivln10*logf(x);
    return  z+y*log10_2hi;
}


double log10(double x)
{
    static const double
        zero   =  0.0,
        two54      =  1.80143985094819840000e+16, /* 0x43500000, 0x00000000 */
        ivln10     =  4.34294481903251816668e-01, /* 0x3FDBCB7B, 0x1526E50E */
        log10_2hi  =  3.01029995663611771306e-01, /* 0x3FD34413, 0x509F6000 */
        log10_2lo  =  3.69423907715893078616e-13; /* 0x3D59FEF3, 0x11F12B36 */

    double y,z;
    int32_t i,k,hx;
    u_int32_t lx;

    EXTRACT_WORDS(hx,lx,x);

    k=0;
    if (hx < 0x00100000) {                  /* x < 2**-1022  */
        if (((hx&0x7fffffff)|lx)==0)
            return /*-two54/zero*/ float_neg_inf();             /* log(+-0)=-inf */
        if (hx<0) return (x-x)/zero;        /* log(-#) = NaN */
        k -= 54; x *= two54; /* subnormal number, scale up x */
        GET_HIGH_WORD(hx,x);
    }
    if (hx >= 0x7ff00000) return x+x;
    k += (hx>>20)-1023;
    i  = ((u_int32_t)k&0x80000000)>>31;
    hx = (hx&0x000fffff)|((0x3ff-i)<<20);
    y  = (double)(k+i);
    SET_HIGH_WORD(x,hx);
    z  = y*log10_2lo + ivln10*log(x);
    return  z+y*log10_2hi;
}


float powf(float x, float y)
{
    static const float huge = 1.0e+30, tiny = 1.0e-30;

    static const float
        bp[] = {1.0, 1.5,},
        dp_h[] = { 0.0, 5.84960938e-01,}, /* 0x3f15c000 */
        dp_l[] = { 0.0, 1.56322085e-06,}, /* 0x35d1cfdc */
        zero    =  0.0,
        one     =  1.0,
        two     =  2.0,
        two24   =  16777216.0,  /* 0x4b800000 */
        /* poly coefs for (3/2)*(log(x)-2s-2/3*s**3 */
        L1  =  6.0000002384e-01, /* 0x3f19999a */
        L2  =  4.2857143283e-01, /* 0x3edb6db7 */
        L3  =  3.3333334327e-01, /* 0x3eaaaaab */
        L4  =  2.7272811532e-01, /* 0x3e8ba305 */
        L5  =  2.3066075146e-01, /* 0x3e6c3255 */
        L6  =  2.0697501302e-01, /* 0x3e53f142 */
        P1   =  1.6666667163e-01, /* 0x3e2aaaab */
        P2   = -2.7777778450e-03, /* 0xbb360b61 */
        P3   =  6.6137559770e-05, /* 0x388ab355 */
        P4   = -1.6533901999e-06, /* 0xb5ddea0e */
        P5   =  4.1381369442e-08, /* 0x3331bb4c */
        lg2  =  6.9314718246e-01, /* 0x3f317218 */
        lg2_h  =  6.93145752e-01, /* 0x3f317200 */
        lg2_l  =  1.42860654e-06, /* 0x35bfbe8c */
        ovt =  4.2995665694e-08, /* -(128-log2(ovfl+.5ulp)) */
        cp    =  9.6179670095e-01, /* 0x3f76384f =2/(3ln2) */
        cp_h  =  9.6179199219e-01, /* 0x3f763800 =head of cp */
        cp_l  =  4.7017383622e-06, /* 0x369dc3a0 =tail of cp_h */
        ivln2    =  1.4426950216e+00, /* 0x3fb8aa3b =1/ln2 */
        ivln2_h  =  1.4426879883e+00, /* 0x3fb8aa00 =16b 1/ln2*/
        ivln2_l  =  7.0526075433e-06; /* 0x36eca570 =1/ln2 tail*/

    float z,ax,z_h,z_l,p_h,p_l;
    float y1,t1,t2,r,s,t,u,v,w;
    int32_t i,j,k,yisint,n;
    int32_t hx,hy,ix,iy,is;

    GET_FLOAT_WORD(hx,x);
    GET_FLOAT_WORD(hy,y);
    ix = hx&0x7fffffff;  iy = hy&0x7fffffff;

    /* y==zero: x**0 = 1 */
    if(iy==0) return one;

    /* +-NaN return x+y */
    if(ix > 0x7f800000 || iy > 0x7f800000)
        return x+y;

    /* determine if y is an odd int when x < 0
     * yisint = 0       ... y is not an integer
     * yisint = 1       ... y is an odd int
     * yisint = 2       ... y is an even int
     */
    yisint  = 0;
    if(hx<0) {
        if(iy>=0x4b800000) yisint = 2; /* even integer y */
        else if(iy>=0x3f800000) {
            k = (iy>>23)-0x7f;     /* exponent */
            j = iy>>(23-k);
            if((j<<(23-k))==iy) yisint = 2-(j&1);
        }
    }

    /* special value of y */
    if (iy==0x7f800000) {       /* y is +-inf */
        if (ix==0x3f800000)
            return  y - y;      /* inf**+-1 is NaN */
        else if (ix > 0x3f800000)/* (|x|>1)**+-inf = inf,0 */
            return (hy>=0)? y: zero;
        else                    /* (|x|<1)**-,+inf = inf,0 */
            return (hy<0)?-y: zero;
    }
    if(iy==0x3f800000) {        /* y is  +-1 */
        if(hy<0) return one/x; else return x;
    }
    if(hy==0x40000000) return x*x; /* y is  2 */
    if(hy==0x3f000000) {        /* y is  0.5 */
        if(hx>=0)       /* x >= +0 */
            return sqrtf(x);
    }

    ax   = fabsf(x);
    /* special value of x */
    if(ix==0x7f800000||ix==0||ix==0x3f800000){
        z = ax;                 /*x is +-0,+-inf,+-1*/
        if(hy<0) z = one/z;     /* z = (1/|x|) */
        if(hx<0) {
            if(((ix-0x3f800000)|yisint)==0) {
                z = (z-z)/(z-z); /* (-1)**non-int is NaN */
            } else if(yisint==1)
                z = -z;         /* (x<0)**odd = -(|x|**odd) */
        }
        return z;
    }

    /* (x<0)**(non-int) is NaN */
    if(((((u_int32_t)hx>>31)-1)|yisint)==0) return (x-x)/(x-x);

    /* |y| is huge */
    if(iy>0x4d000000) { /* if |y| > 2**27 */
        /* over/underflow if x is not close to one */
        if(ix<0x3f7ffff8) return (hy<0)? /*huge*huge*/ float_pos_inf() : /*tiny*tiny*/ float_zero();
        if(ix>0x3f800007) return (hy>0)? /*huge*huge*/ float_pos_inf() : /*tiny*tiny*/ float_zero();
        /* now |1-x| is tiny <= 2**-20, suffice to compute
           log(x) by x-x^2/2+x^3/3-x^4/4 */
        t = x-1;                /* t has 20 trailing zeros */
        w = (t*t)*((float)0.5-t*((float)0.333333333333-t*(float)0.25));
        u = ivln2_h*t;  /* ivln2_h has 16 sig. bits */
        v = t*ivln2_l-w*ivln2;
        t1 = u+v;
        GET_FLOAT_WORD(is,t1);
        SET_FLOAT_WORD(t1,is&0xfffff000);
        t2 = v-(t1-u);
    } else {
        float s2,s_h,s_l,t_h,t_l;
        n = 0;
        /* take care subnormal number */
        if(ix<0x00800000)
            {ax *= two24; n -= 24; GET_FLOAT_WORD(ix,ax); }
        n  += ((ix)>>23)-0x7f;
        j  = ix&0x007fffff;
        /* determine interval */
        ix = j|0x3f800000;              /* normalize ix */
        if(j<=0x1cc471) k=0;    /* |x|<sqrt(3/2) */
        else if(j<0x5db3d7) k=1;        /* |x|<sqrt(3)   */
        else {k=0;n+=1;ix -= 0x00800000;}
        SET_FLOAT_WORD(ax,ix);

        /* compute s = s_h+s_l = (x-1)/(x+1) or (x-1.5)/(x+1.5) */
        u = ax-bp[k];           /* bp[0]=1.0, bp[1]=1.5 */
        v = one/(ax+bp[k]);
        s = u*v;
        s_h = s;
        GET_FLOAT_WORD(is,s_h);
        SET_FLOAT_WORD(s_h,is&0xfffff000);
        /* t_h=ax+bp[k] High */
        SET_FLOAT_WORD(t_h,((ix>>1)|0x20000000)+0x0040000+(k<<21));
        t_l = ax - (t_h-bp[k]);
        s_l = v*((u-s_h*t_h)-s_h*t_l);
        /* compute log(ax) */
        s2 = s*s;
        r = s2*s2*(L1+s2*(L2+s2*(L3+s2*(L4+s2*(L5+s2*L6)))));
        r += s_l*(s_h+s);
        s2  = s_h*s_h;
        t_h = (float)3.0+s2+r;
        GET_FLOAT_WORD(is,t_h);
        SET_FLOAT_WORD(t_h,is&0xfffff000);
        t_l = r-((t_h-(float)3.0)-s2);
        /* u+v = s*(1+...) */
        u = s_h*t_h;
        v = s_l*t_h+t_l*s;
        /* 2/(3log2)*(s+...) */
        p_h = u+v;
        GET_FLOAT_WORD(is,p_h);
        SET_FLOAT_WORD(p_h,is&0xfffff000);
        p_l = v-(p_h-u);
        z_h = cp_h*p_h;         /* cp_h+cp_l = 2/(3*log2) */
        z_l = cp_l*p_h+p_l*cp+dp_l[k];
        /* log2(ax) = (s+..)*2/(3*log2) = n + dp_h + z_h + z_l */
        t = (float)n;
        t1 = (((z_h+z_l)+dp_h[k])+t);
        GET_FLOAT_WORD(is,t1);
        SET_FLOAT_WORD(t1,is&0xfffff000);
        t2 = z_l-(((t1-t)-dp_h[k])-z_h);
    }

    s = one; /* s (sign of result -ve**odd) = -1 else = 1 */
    if(((((u_int32_t)hx>>31)-1)|(yisint-1))==0)
        s = -one;       /* (-ve)**(odd int) */

    /* split up y into y1+y2 and compute (y1+y2)*(t1+t2) */
    GET_FLOAT_WORD(is,y);
    SET_FLOAT_WORD(y1,is&0xfffff000);
    p_l = (y-y1)*t1+y*t2;
    p_h = y1*t1;
    z = p_l+p_h;
    GET_FLOAT_WORD(j,z);
    // NOTE: chess_copy(s) to prevent CSE moving s * ... * ...
    if (j>0x43000000)                           /* if z > 128 */
        return chess_copy(s)*huge*huge;                         /* overflow */
    else if (j==0x43000000) {                   /* if z == 128 */
        if(p_l+ovt>z-p_h) return chess_copy(s)*huge*huge;       /* overflow */
    }
    else if ((j&0x7fffffff)>0x43160000)         /* z <= -150 */
        return chess_copy(s)*tiny*tiny;                         /* underflow */
    else if (j==0xc3160000){                    /* z == -150 */
        if(p_l<=z-p_h) return chess_copy(s)*tiny*tiny;          /* underflow */
    }
    /* compute 2**(p_h+p_l) */
    i = j&0x7fffffff;
    k = (i>>23)-0x7f;
    n = 0;
    if(i>0x3f000000) {          /* if |z| > 0.5, set n = [z+0.5] */
        n = j+((u_int32_t)0x00800000>>(k+1));
        k = ((n&0x7fffffff)>>23)-0x7f;  /* new k for n */
        SET_FLOAT_WORD(t,n&~((u_int32_t)0x007fffff>>k));
        n = ((n&0x007fffff)|0x00800000)>>(23-k);
        if(j<0) n = -n;
        p_h -= t;
    }
    t = p_l+p_h;
    GET_FLOAT_WORD(is,t);
    SET_FLOAT_WORD(t,is&0xfffff000);
    u = t*lg2_h;
    v = (p_l-(t-p_h))*lg2+t*lg2_l;
    z = u+v;
    w = v-(z-u);
    t  = z*z;
    t1 = z - t*(P1+t*(P2+t*(P3+t*(P4+t*P5))));
    r  = (z*t1)/(t1-two)-(w+z*w);
    z  = one-(r-z);
    GET_FLOAT_WORD(j,z);
    j += (n<<23);
    if((j>>23)<=0) z = ldexpf(z,n);     /* subnormal output */
    else SET_FLOAT_WORD(z,j);
    return s*z;
}


double pow(double x, double y)
{
    static const double
        bp[] = {1.0, 1.5,},
        dp_h[] = { 0.0, 5.84962487220764160156e-01,}, /* 0x3FE2B803, 0x40000000 */
        dp_l[] = { 0.0, 1.35003920212974897128e-08,}, /* 0x3E4CFDEB, 0x43CFD006 */
        zero    =  0.0,
        one     =  1.0,
        two     =  2.0,
        two53   =  9007199254740992.0,  /* 0x43400000, 0x00000000 */
        huge    =  1.0e300,
        tiny    =  1.0e-300,
        /* poly coefs for (3/2)*(log(x)-2s-2/3*s**3 */
        L1  =  5.99999999999994648725e-01, /* 0x3FE33333, 0x33333303 */
        L2  =  4.28571428578550184252e-01, /* 0x3FDB6DB6, 0xDB6FABFF */
        L3  =  3.33333329818377432918e-01, /* 0x3FD55555, 0x518F264D */
        L4  =  2.72728123808534006489e-01, /* 0x3FD17460, 0xA91D4101 */
        L5  =  2.30660745775561754067e-01, /* 0x3FCD864A, 0x93C9DB65 */
        L6  =  2.06975017800338417784e-01, /* 0x3FCA7E28, 0x4A454EEF */
        P1   =  1.66666666666666019037e-01, /* 0x3FC55555, 0x5555553E */
        P2   = -2.77777777770155933842e-03, /* 0xBF66C16C, 0x16BEBD93 */
        P3   =  6.61375632143793436117e-05, /* 0x3F11566A, 0xAF25DE2C */
        P4   = -1.65339022054652515390e-06, /* 0xBEBBBD41, 0xC5D26BF1 */
        P5   =  4.13813679705723846039e-08, /* 0x3E663769, 0x72BEA4D0 */
        lg2  =  6.93147180559945286227e-01, /* 0x3FE62E42, 0xFEFA39EF */
        lg2_h  =  6.93147182464599609375e-01, /* 0x3FE62E43, 0x00000000 */
        lg2_l  = -1.90465429995776804525e-09, /* 0xBE205C61, 0x0CA86C39 */
        ovt =  8.0085662595372944372e-0017, /* -(1024-log2(ovfl+.5ulp)) */
        cp    =  9.61796693925975554329e-01, /* 0x3FEEC709, 0xDC3A03FD =2/(3ln2) */
        cp_h  =  9.61796700954437255859e-01, /* 0x3FEEC709, 0xE0000000 =(float)cp */
        cp_l  = -7.02846165095275826516e-09, /* 0xBE3E2FE0, 0x145B01F5 =tail of cp_h*/
        ivln2    =  1.44269504088896338700e+00, /* 0x3FF71547, 0x652B82FE =1/ln2 */
        ivln2_h  =  1.44269502162933349609e+00, /* 0x3FF71547, 0x60000000 =24b 1/ln2*/
        ivln2_l  =  1.92596299112661746887e-08; /* 0x3E54AE0B, 0xF85DDF44 =1/ln2 tail*/

    double z,ax,z_h,z_l,p_h,p_l;
    double y1,t1,t2,r,s,t,u,v,w;
    int32_t i,j,k,yisint,n;
    int32_t hx,hy,ix,iy;
    u_int32_t lx,ly;

    EXTRACT_WORDS(hx,lx,x);
    EXTRACT_WORDS(hy,ly,y);
    ix = hx&0x7fffffff;  iy = hy&0x7fffffff;

    /* y==zero: x**0 = 1 */
    if((iy|ly)==0) return one;

    /* +-NaN return x+y */
    if(ix > 0x7ff00000 || ((ix==0x7ff00000)&&(lx!=0)) ||
       iy > 0x7ff00000 || ((iy==0x7ff00000)&&(ly!=0)))
        return x+y;

    /* determine if y is an odd int when x < 0
     * yisint = 0       ... y is not an integer
     * yisint = 1       ... y is an odd int
     * yisint = 2       ... y is an even int
     */
    yisint  = 0;
    if(hx<0) {
        if(iy>=0x43400000) yisint = 2; /* even integer y */
        else if(iy>=0x3ff00000) {
            k = (iy>>20)-0x3ff;    /* exponent */
            if(k>20) {
                j = ly>>(52-k);
                if((j<<(52-k))==ly) yisint = 2-(j&1);
            } else if(ly==0) {
                j = iy>>(20-k);
                if((j<<(20-k))==iy) yisint = 2-(j&1);
            }
        }
    }

    /* special value of y */
    if(ly==0) {
        if (iy==0x7ff00000) {   /* y is +-inf */
            if(((ix-0x3ff00000)|lx)==0)
                return  y - y;  /* inf**+-1 is NaN */
            else if (ix >= 0x3ff00000)/* (|x|>1)**+-inf = inf,0 */
                return (hy>=0)? y: zero;
            else                        /* (|x|<1)**-,+inf = inf,0 */
                return (hy<0)?-y: zero;
        }
        if(iy==0x3ff00000) {    /* y is  +-1 */
            if(hy<0) return one/x; else return x;
        }
        if(hy==0x40000000) return x*x; /* y is  2 */
        if(hy==0x3fe00000) {    /* y is  0.5 */
            if(hx>=0)   /* x >= +0 */
                return sqrt(x);
        }
    }

    ax   = fabs(x);
    /* special value of x */
    if(lx==0) {
        if(ix==0x7ff00000||ix==0||ix==0x3ff00000){
            z = ax;                     /*x is +-0,+-inf,+-1*/
            if(hy<0) z = one/z; /* z = (1/|x|) */
            if(hx<0) {
                if(((ix-0x3ff00000)|yisint)==0) {
                    z = (z-z)/(z-z); /* (-1)**non-int is NaN */
                } else if(yisint==1)
                    z = -z;             /* (x<0)**odd = -(|x|**odd) */
            }
            return z;
        }
    }

    /* (x<0)**(non-int) is NaN */
    if(((((u_int32_t)hx>>31)-1)|yisint)==0) return (x-x)/(x-x);

    /* |y| is huge */
    if(iy>0x41e00000) { /* if |y| > 2**31 */
        if(iy>0x43f00000){      /* if |y| > 2**64, must o/uflow */
            if(ix<=0x3fefffff) return (hy<0)? huge*huge:tiny*tiny;
            if(ix>=0x3ff00000) return (hy>0)? huge*huge:tiny*tiny;
        }
        /* over/underflow if x is not close to one */
        if(ix<0x3fefffff) return (hy<0)? huge*huge:tiny*tiny;
        if(ix>0x3ff00000) return (hy>0)? huge*huge:tiny*tiny;
        /* now |1-x| is tiny <= 2**-20, suffice to compute
           log(x) by x-x^2/2+x^3/3-x^4/4 */
        t = x-1;                /* t has 20 trailing zeros */
        w = (t*t)*(0.5-t*(0.3333333333333333333333-t*0.25));
        u = ivln2_h*t;  /* ivln2_h has 21 sig. bits */
        v = t*ivln2_l-w*ivln2;
        t1 = u+v;
        SET_LOW_WORD(t1,0);
        t2 = v-(t1-u);
    } else {
        double s2,s_h,s_l,t_h,t_l;
        n = 0;
        /* take care subnormal number */
        if(ix<0x00100000)
            {ax *= two53; n -= 53; GET_HIGH_WORD(ix,ax); }
        n  += ((ix)>>20)-0x3ff;
        j  = ix&0x000fffff;
        /* determine interval */
        ix = j|0x3ff00000;              /* normalize ix */
        if(j<=0x3988E) k=0;             /* |x|<sqrt(3/2) */
        else if(j<0xBB67A) k=1; /* |x|<sqrt(3)   */
        else {k=0;n+=1;ix -= 0x00100000;}
        SET_HIGH_WORD(ax,ix);

        /* compute s = s_h+s_l = (x-1)/(x+1) or (x-1.5)/(x+1.5) */
        u = ax-bp[k];           /* bp[0]=1.0, bp[1]=1.5 */
        v = one/(ax+bp[k]);
        s = u*v;
        s_h = s;
        SET_LOW_WORD(s_h,0);
        /* t_h=ax+bp[k] High */
        t_h = zero;
        SET_HIGH_WORD(t_h,((ix>>1)|0x20000000)+0x00080000+(k<<18));
        t_l = ax - (t_h-bp[k]);
        s_l = v*((u-s_h*t_h)-s_h*t_l);
        /* compute log(ax) */
        s2 = s*s;
        r = s2*s2*(L1+s2*(L2+s2*(L3+s2*(L4+s2*(L5+s2*L6)))));
        r += s_l*(s_h+s);
        s2  = s_h*s_h;
        t_h = 3.0+s2+r;
        SET_LOW_WORD(t_h,0);
        t_l = r-((t_h-3.0)-s2);
        /* u+v = s*(1+...) */
        u = s_h*t_h;
        v = s_l*t_h+t_l*s;
        /* 2/(3log2)*(s+...) */
        p_h = u+v;
        SET_LOW_WORD(p_h,0);
        p_l = v-(p_h-u);
        z_h = cp_h*p_h;         /* cp_h+cp_l = 2/(3*log2) */
        z_l = cp_l*p_h+p_l*cp+dp_l[k];
        /* log2(ax) = (s+..)*2/(3*log2) = n + dp_h + z_h + z_l */
        t = (double)n;
        t1 = (((z_h+z_l)+dp_h[k])+t);
        SET_LOW_WORD(t1,0);
        t2 = z_l-(((t1-t)-dp_h[k])-z_h);
    }

    s = one; /* s (sign of result -ve**odd) = -1 else = 1 */
    if(((((u_int32_t)hx>>31)-1)|(yisint-1))==0)
        s = -one;/* (-ve)**(odd int) */

    /* split up y into y1+y2 and compute (y1+y2)*(t1+t2) */
    y1  = y;
    SET_LOW_WORD(y1,0);
    p_l = (y-y1)*t1+y*t2;
    p_h = y1*t1;
    z = p_l+p_h;
    EXTRACT_WORDS(j,i,z);
    if (j>=0x40900000) {                                /* z >= 1024 */
        if(((j-0x40900000)|i)!=0)                       /* if z > 1024 */
            return s*huge*huge;                 /* overflow */
        else {
            if(p_l+ovt>z-p_h) return s*huge*huge;       /* overflow */
        }
    } else if((j&0x7fffffff)>=0x4090cc00 ) {    /* z <= -1075 */
        if(((j-0xc090cc00)|i)!=0)               /* z < -1075 */
            return s*tiny*tiny;         /* underflow */
        else {
            if(p_l<=z-p_h) return s*tiny*tiny;  /* underflow */
        }
    }
    /* compute 2**(p_h+p_l) */
    i = j&0x7fffffff;
    k = (i>>20)-0x3ff;
    n = 0;
    if(i>0x3fe00000) {          /* if |z| > 0.5, set n = [z+0.5] */
        n = j+((u_int32_t)0x00100000>>(k+1));
        k = ((n&0x7fffffff)>>20)-0x3ff; /* new k for n */
        t = zero;
        SET_HIGH_WORD(t,n&~((u_int32_t)0x000fffff>>k));
        n = ((n&0x000fffff)|0x00100000)>>(20-k);
        if(j<0) n = -n;
        p_h -= t;
    }
    t = p_l+p_h;
    SET_LOW_WORD(t,0);
    u = t*lg2_h;
    v = (p_l-(t-p_h))*lg2+t*lg2_l;
    z = u+v;
    w = v-(z-u);
    t  = z*z;
    t1  = z - t*(P1+t*(P2+t*(P3+t*(P4+t*P5))));
    r  = (z*t1)/(t1-two)-(w+z*w);
    z  = one-(r-z);
    GET_HIGH_WORD(j,z);
    j += (n<<20);
    if((j>>20)<=0) z = ldexp(z,n);      /* subnormal output */
    else SET_HIGH_WORD(z,j);
    return s*z;

}


float sqrtf(float x)
{
    static const float  one     = 1.0, tiny=1.0e-30;

    float z;
    int32_t sign = (int32_t)0x80000000;
    int32_t ix,s,q,m,t,i;
    u_int32_t r;

    GET_FLOAT_WORD(ix,x);

    /* take care of Inf and NaN */
    if((ix&0x7f800000)==0x7f800000) {
        return x*x+x;           /* sqrt(NaN)=NaN, sqrt(+inf)=+inf
                                   sqrt(-inf)=sNaN */
    }
    /* take care of zero */
    if(ix<=0) {
        if((ix&(~sign))==0) return x;/* sqrt(+-0) = +-0 */
        else if(ix<0)
            return (x-x)/(x-x);         /* sqrt(-ve) = sNaN */
    }
    /* normalize x */
    m = (ix>>23);
    if(m==0) {                          /* subnormal x */
        for(i=0;(ix&0x00800000)==0;i++) ix<<=1;
        m -= i-1;
    }
    m -= 127;   /* unbias exponent */
    ix = (ix&0x007fffff)|0x00800000;
    if(m&1)     /* odd m, double x to make it even */
        ix += ix;
    m >>= 1;    /* m = [m/2] */

    /* generate sqrt(x) bit by bit */
    ix += ix;
    q = s = 0;          /* q = sqrt(x) */
    r = 0x01000000;             /* r = moving bit from right to left */

    while(r!=0) {
        t = s+r;
        if(t<=ix) {
            s    = t+r;
            ix  -= t;
            q   += r;
        }
        ix += ix;
        r>>=1;
    }

    /* use floating add to find out rounding direction */
    if(ix!=0) {
        z = one-tiny; /* trigger inexact flag */
        if (z>=one) {
            z = one+tiny;
            if (z>one)
                q += 2;
            else
                q += (q&1);
        }
    }
    ix = (q>>1)+0x3f000000;
    ix += (m <<23);
    SET_FLOAT_WORD(z,ix);
    return z;
}


double sqrt(double x)
{
    static const double one     = 1.0, tiny=1.0e-300;

    double z;
    int32_t sign = (int32_t)0x80000000;
    int32_t ix0,s0,q,m,t,i;
    u_int32_t r,t1,s1,ix1,q1;

    EXTRACT_WORDS(ix0,ix1,x);

    /* take care of Inf and NaN */
    if((ix0&0x7ff00000)==0x7ff00000) {
        return x*x+x;           /* sqrt(NaN)=NaN, sqrt(+inf)=+inf
                                   sqrt(-inf)=sNaN */
    }
    /* take care of zero */
    if(ix0<=0) {
        if(((ix0&(~sign))|ix1)==0) return x;/* sqrt(+-0) = +-0 */
        else if(ix0<0)
            return (x-x)/(x-x);         /* sqrt(-ve) = sNaN */
    }
    /* normalize x */
    m = (ix0>>20);
    if(m==0) {                          /* subnormal x */
        while(ix0==0) {
            m -= 21;
            ix0 |= (ix1>>11); ix1 <<= 21;
        }
        for(i=0;(ix0&0x00100000)==0;i++) ix0<<=1;
        m -= i-1;
        ix0 |= (ix1>>(32-i));
        ix1 <<= i;
    }
    m -= 1023;  /* unbias exponent */
    ix0 = (ix0&0x000fffff)|0x00100000;
    if(m&1){    /* odd m, double x to make it even */
        ix0 += ix0 + ((ix1&sign)>>31);
        ix1 += ix1;
    }
    m >>= 1;    /* m = [m/2] */

    /* generate sqrt(x) bit by bit */
    ix0 += ix0 + ((ix1&sign)>>31);
    ix1 += ix1;
    q = q1 = s0 = s1 = 0;       /* [q,q1] = sqrt(x) */
    r = 0x00200000;             /* r = moving bit from right to left */

    while(r!=0) {
        t = s0+r;
        if(t<=ix0) {
            s0   = t+r;
            ix0 -= t;
            q   += r;
        }
        ix0 += ix0 + ((ix1&sign)>>31);
        ix1 += ix1;
        r>>=1;
    }

    r = sign;
    while(r!=0) {
        t1 = s1+r;
        t  = s0;
        if((t<ix0)||((t==ix0)&&(t1<=ix1))) {
            s1  = t1+r;
            if(((t1&sign)==sign)&&(s1&sign)==0) s0 += 1;
            ix0 -= t;
            if (ix1 < t1) ix0 -= 1;
            ix1 -= t1;
            q1  += r;
        }
        ix0 += ix0 + ((ix1&sign)>>31);
        ix1 += ix1;
        r>>=1;
    }

    /* use floating add to find out rounding direction */
    if((ix0|ix1)!=0) {
        z = one-tiny; /* trigger inexact flag */
        if (z>=one) {
            z = one+tiny;
            if (q1==(u_int32_t)0xffffffff) { q1=0; q += 1;}
            else if (z>one) {
                if (q1==(u_int32_t)0xfffffffe) q+=1;
                q1+=2;
            } else
                q1 += (q1&1);
        }
    }
    ix0 = (q>>1)+0x3fe00000;
    ix1 =  q1>>1;
    if ((q&1)==1) ix1 |= sign;
    ix0 += (m <<20);
    INSERT_WORDS(z,ix0,ix1);
    return z;
}



double fmod(double x, double y)
{
        static const double one = 1.0, Zero[] = {0.0, -0.0,};

        int32_t n,hx,hy,hz,ix,iy,sx,i;
        u_int32_t lx,ly,lz;

        EXTRACT_WORDS(hx,lx,x);
        EXTRACT_WORDS(hy,ly,y);
        sx = hx&0x80000000;             /* sign of x */
        hx ^=sx;                /* |x| */
        hy &= 0x7fffffff;       /* |y| */

    /* purge off exception values */
        if((hy|ly)==0||(hx>=0x7ff00000)||       /* y=0,or x not finite */
          ((hy|((ly|-ly)>>31))>0x7ff00000))     /* or y is NaN */
            return (x*y)/(x*y);
        if(hx<=hy) {
            if((hx<hy)||(lx<ly)) return x;      /* |x|<|y| return x */
            if(lx==ly)
                return Zero[(u_int32_t)sx>>31]; /* |x|=|y| return x*0*/
        }

    /* determine ix = ilogb(x) */
        if(hx<0x00100000) {     /* subnormal x */
            if(hx==0) {
                for (ix = -1043, i=lx; i>0; i<<=1) ix -=1;
            } else {
                for (ix = -1022,i=(hx<<11); i>0; i<<=1) ix -=1;
            }
        } else ix = (hx>>20)-1023;

    /* determine iy = ilogb(y) */
        if(hy<0x00100000) {     /* subnormal y */
            if(hy==0) {
                for (iy = -1043, i=ly; i>0; i<<=1) iy -=1;
            } else {
                for (iy = -1022,i=(hy<<11); i>0; i<<=1) iy -=1;
            }
        } else iy = (hy>>20)-1023;

    /* set up {hx,lx}, {hy,ly} and align y to x */
        if(ix >= -1022)
            hx = 0x00100000|(0x000fffff&hx);
        else {          /* subnormal x, shift x to normal */
            n = -1022-ix;
            if(n<=31) {
                hx = (hx<<n)|(lx>>(32-n));
                lx <<= n;
            } else {
                hx = lx<<(n-32);
                lx = 0;
            }
        }
        if(iy >= -1022)
            hy = 0x00100000|(0x000fffff&hy);
        else {          /* subnormal y, shift y to normal */
            n = -1022-iy;
            if(n<=31) {
                hy = (hy<<n)|(ly>>(32-n));
                ly <<= n;
            } else {
                hy = ly<<(n-32);
                ly = 0;
            }
        }

    /* fix point fmod */
        n = ix - iy;
        while(n--) {
            hz=hx-hy;lz=lx-ly; if(lx<ly) hz -= 1;
            if(hz<0){hx = hx+hx+(lx>>31); lx = lx+lx;}
            else {
                if((hz|lz)==0)          /* return sign(x)*0 */
                    return Zero[(u_int32_t)sx>>31];
                hx = hz+hz+(lz>>31); lx = lz+lz;
            }
        }
        hz=hx-hy;lz=lx-ly; if(lx<ly) hz -= 1;
        if(hz>=0) {hx=hz;lx=lz;}

    /* convert back to floating value and restore the sign */
        if((hx|lx)==0)                  /* return sign(x)*0 */
            return Zero[(u_int32_t)sx>>31];
        while(hx<0x00100000) {          /* normalize x */
            hx = hx+hx+(lx>>31); lx = lx+lx;
            iy -= 1;
        }
        if(iy>= -1022) {        /* normalize output */
            hx = ((hx-0x00100000)|((iy+1023)<<20));
            INSERT_WORDS(x,hx|sx,lx);
        } else {                /* subnormal output */
            n = -1022 - iy;
            if(n<=20) {
                lx = (lx>>n)|((u_int32_t)hx<<(32-n));
                hx >>= n;
            } else if (n<=31) {
                lx = (hx<<(32-n))|(lx>>n); hx = sx;
            } else {
                lx = hx>>(n-32); hx = sx;
            }
            INSERT_WORDS(x,hx|sx,lx);
            x *= one;           /* create necessary signal */
        }
        return x;               /* exact output */
}

float acosf(float x)
{
        static const float
        one =  1.0000000000e+00, /* 0x3F800000 */
        pi =  3.1415925026e+00, /* 0x40490fda */
        pio2_hi =  1.5707962513e+00, /* 0x3fc90fda */
        pio2_lo =  7.5497894159e-08, /* 0x33a22168 */
        pS0 =  1.6666667163e-01, /* 0x3e2aaaab */
        pS1 = -3.2556581497e-01, /* 0xbea6b090 */
        pS2 =  2.0121252537e-01, /* 0x3e4e0aa8 */
        pS3 = -4.0055535734e-02, /* 0xbd241146 */
        pS4 =  7.9153501429e-04, /* 0x3a4f7f04 */
        pS5 =  3.4793309169e-05, /* 0x3811ef08 */
        qS1 = -2.4033949375e+00, /* 0xc019d139 */
        qS2 =  2.0209457874e+00, /* 0x4001572d */
        qS3 = -6.8828397989e-01, /* 0xbf303361 */
        qS4 =  7.7038154006e-02; /* 0x3d9dc62e */

        float z,p,q,r,w,s,c,df;
        int32_t hx,ix;
        GET_FLOAT_WORD(hx,x);
        ix = hx&0x7fffffff;
        if(ix==0x3f800000) {            /* |x|==1 */
            if(hx>0) return 0.0;        /* acos(1) = 0  */
            else return pi+(float)2.0*pio2_lo;  /* acos(-1)= pi */
        } else if(ix>0x3f800000) {      /* |x| >= 1 */
            return (x-x)/(x-x);         /* acos(|x|>1) is NaN */
        }
        if(ix<0x3f000000) {     /* |x| < 0.5 */
            if(ix<=0x23000000) return pio2_hi+pio2_lo;/*if|x|<2**-57*/
            z = x*x;
            p = z*(pS0+z*(pS1+z*(pS2+z*(pS3+z*(pS4+z*pS5)))));
            q = one+z*(qS1+z*(qS2+z*(qS3+z*qS4)));
            r = p/q;
            return pio2_hi - (x - (pio2_lo-x*r));
        } else  if (hx<0) {             /* x < -0.5 */
            z = (one+x)*(float)0.5;
            p = z*(pS0+z*(pS1+z*(pS2+z*(pS3+z*(pS4+z*pS5)))));
            q = one+z*(qS1+z*(qS2+z*(qS3+z*qS4)));
            s = sqrtf(z);
            r = p/q;
            w = r*s-pio2_lo;
            return pi - (float)2.0*(s+w);
        } else {                        /* x > 0.5 */
            int32_t idf;
            z = (one-x)*(float)0.5;
            s = sqrtf(z);
            df = s;
            GET_FLOAT_WORD(idf,df);
            SET_FLOAT_WORD(df,idf&0xfffff000);
            c  = (z-df*df)/(s+df);
            p = z*(pS0+z*(pS1+z*(pS2+z*(pS3+z*(pS4+z*pS5)))));
            q = one+z*(qS1+z*(qS2+z*(qS3+z*qS4)));
            r = p/q;
            w = r*s+c;
            return (float)2.0*(df+w);
        }
}


double acos(double x)
{
     static const double
     one=  1.00000000000000000000e+00, /* 0x3FF00000, 0x00000000 */
     pi =  3.14159265358979311600e+00, /* 0x400921FB, 0x54442D18 */
     pio2_hi =  1.57079632679489655800e+00, /* 0x3FF921FB, 0x54442D18 */
     pio2_lo =  6.12323399573676603587e-17, /* 0x3C91A626, 0x33145C07 */
     pS0 =  1.66666666666666657415e-01, /* 0x3FC55555, 0x55555555 */
     pS1 = -3.25565818622400915405e-01, /* 0xBFD4D612, 0x03EB6F7D */
     pS2 =  2.01212532134862925881e-01, /* 0x3FC9C155, 0x0E884455 */
     pS3 = -4.00555345006794114027e-02, /* 0xBFA48228, 0xB5688F3B */
     pS4 =  7.91534994289814532176e-04, /* 0x3F49EFE0, 0x7501B288 */
     pS5 =  3.47933107596021167570e-05, /* 0x3F023DE1, 0x0DFDF709 */
     qS1 = -2.40339491173441421878e+00, /* 0xC0033A27, 0x1C8A2D4B */
     qS2 =  2.02094576023350569471e+00, /* 0x40002AE5, 0x9C598AC8 */
     qS3 = -6.88283971605453293030e-01, /* 0xBFE6066C, 0x1B8D0159 */
     qS4 =  7.70381505559019352791e-02; /* 0x3FB3B8C5, 0xB12E9282 */

        double z,p,q,r,w,s,c,df;
        int32_t hx,ix;
        GET_HIGH_WORD(hx,x);
        ix = hx&0x7fffffff;
        if(ix>=0x3ff00000) {    /* |x| >= 1 */
            u_int32_t lx;
            GET_LOW_WORD(lx,x);
            if(((ix-0x3ff00000)|lx)==0) {       /* |x|==1 */
                if(hx>0) return 0.0;            /* acos(1) = 0  */
                else return pi+2.0*pio2_lo;     /* acos(-1)= pi */
            }
            return (x-x)/(x-x);         /* acos(|x|>1) is NaN */
        }
        if(ix<0x3fe00000) {     /* |x| < 0.5 */
            if(ix<=0x3c600000) return pio2_hi+pio2_lo;/*if|x|<2**-57*/
            z = x*x;
            p = z*(pS0+z*(pS1+z*(pS2+z*(pS3+z*(pS4+z*pS5)))));
            q = one+z*(qS1+z*(qS2+z*(qS3+z*qS4)));
            r = p/q;
            return pio2_hi - (x - (pio2_lo-x*r));
        } else  if (hx<0) {             /* x < -0.5 */
            z = (one+x)*0.5;
            p = z*(pS0+z*(pS1+z*(pS2+z*(pS3+z*(pS4+z*pS5)))));
            q = one+z*(qS1+z*(qS2+z*(qS3+z*qS4)));
            s = sqrt(z);
            r = p/q;
            w = r*s-pio2_lo;
            return pi - 2.0*(s+w);
        } else {                        /* x > 0.5 */
            z = (one-x)*0.5;
            s = sqrt(z);
            df = s;
            SET_LOW_WORD(df,0);
            c  = (z-df*df)/(s+df);
            p = z*(pS0+z*(pS1+z*(pS2+z*(pS3+z*(pS4+z*pS5)))));
            q = one+z*(qS1+z*(qS2+z*(qS3+z*qS4)));
            r = p/q;
            w = r*s+c;
            return 2.0*(df+w);
        }
}


float asinf(float x)
{
      static const float
      one =  1.0000000000e+00, /* 0x3F800000 */
      huge =  1.000e+30,
      pio2_hi = 1.57079637050628662109375f,
      pio2_lo = -4.37113900018624283e-8f,
      pio4_hi = 0.785398185253143310546875f,
              /* coefficient for R(x^2) */
      pS0 =  1.6666667163e-01, /* 0x3e2aaaab */
      pS1 = -3.2556581497e-01, /* 0xbea6b090 */
      pS2 =  2.0121252537e-01, /* 0x3e4e0aa8 */
      pS3 = -4.0055535734e-02, /* 0xbd241146 */
      pS4 =  7.9153501429e-04, /* 0x3a4f7f04 */
      pS5 =  3.4793309169e-05, /* 0x3811ef08 */
      qS1 = -2.4033949375e+00, /* 0xc019d139 */
      qS2 =  2.0209457874e+00, /* 0x4001572d */
      qS3 = -6.8828397989e-01, /* 0xbf303361 */
      qS4 =  7.7038154006e-02; /* 0x3d9dc62e */

        float t,w,p,q,c,r,s;
        int32_t hx,ix;
        GET_FLOAT_WORD(hx,x);
        ix = hx&0x7fffffff;
        if(ix==0x3f800000) {
                /* asin(1)=+-pi/2 with inexact */
            return x*pio2_hi+x*pio2_lo;
        } else if(ix> 0x3f800000) {     /* |x|>= 1 */
            return (x-x)/(x-x);         /* asin(|x|>1) is NaN */
        } else if (ix<0x3f000000) {     /* |x|<0.5 */
            if(ix<0x32000000) {         /* if |x| < 2**-27 */
                if(huge+x>one) return x;/* return x with inexact if x!=0*/
            } else
                t = x*x;
                p = t*(pS0+t*(pS1+t*(pS2+t*(pS3+t*(pS4+t*pS5)))));
                q = one+t*(qS1+t*(qS2+t*(qS3+t*qS4)));
                w = p/q;
                return x+x*w;
        }
        /* 1> |x|>= 0.5 */
        w = one-fabsf(x);
        t = w*(float)0.5;
        p = t*(pS0+t*(pS1+t*(pS2+t*(pS3+t*(pS4+t*pS5)))));
        q = one+t*(qS1+t*(qS2+t*(qS3+t*qS4)));
        s = sqrtf(t);
        if(ix>=0x3F79999A) {    /* if |x| > 0.975 */
            w = p/q;
            t = pio2_hi-((float)2.0*(s+s*w)-pio2_lo);
        } else {
            int32_t iw;
            w  = s;
            GET_FLOAT_WORD(iw,w);
            SET_FLOAT_WORD(w,iw&0xfffff000);
            c  = (t-w*w)/(s+w);
            r  = p/q;
            p  = (float)2.0*s*r-(pio2_lo-(float)2.0*c);
            q  = pio4_hi-(float)2.0*w;
            t  = pio4_hi-(p-q);
        }
        if(hx>0) return t; else return -t;
}


double asin(double x)
{
    static const double
    one =  1.00000000000000000000e+00, /* 0x3FF00000, 0x00000000 */
    huge =  1.000e+300,
    pio2_hi =  1.57079632679489655800e+00, /* 0x3FF921FB, 0x54442D18 */
    pio2_lo =  6.12323399573676603587e-17, /* 0x3C91A626, 0x33145C07 */
    pio4_hi =  7.85398163397448278999e-01, /* 0x3FE921FB, 0x54442D18 */
            /* coefficient for R(x^2) */
    pS0 =  1.66666666666666657415e-01, /* 0x3FC55555, 0x55555555 */
    pS1 = -3.25565818622400915405e-01, /* 0xBFD4D612, 0x03EB6F7D */
    pS2 =  2.01212532134862925881e-01, /* 0x3FC9C155, 0x0E884455 */
    pS3 = -4.00555345006794114027e-02, /* 0xBFA48228, 0xB5688F3B */
    pS4 =  7.91534994289814532176e-04, /* 0x3F49EFE0, 0x7501B288 */
    pS5 =  3.47933107596021167570e-05, /* 0x3F023DE1, 0x0DFDF709 */
    qS1 = -2.40339491173441421878e+00, /* 0xC0033A27, 0x1C8A2D4B */
    qS2 =  2.02094576023350569471e+00, /* 0x40002AE5, 0x9C598AC8 */
    qS3 = -6.88283971605453293030e-01, /* 0xBFE6066C, 0x1B8D0159 */
    qS4 =  7.70381505559019352791e-02; /* 0x3FB3B8C5, 0xB12E9282 */

        double t,w,p,q,c,r,s;
        int32_t hx,ix;
        GET_HIGH_WORD(hx,x);
        ix = hx&0x7fffffff;
        if(ix>= 0x3ff00000) {           /* |x|>= 1 */
            u_int32_t lx;
            GET_LOW_WORD(lx,x);
            if(((ix-0x3ff00000)|lx)==0)
                    /* asin(1)=+-pi/2 with inexact */
                return x*pio2_hi+x*pio2_lo;
            return (x-x)/(x-x);         /* asin(|x|>1) is NaN */
        } else if (ix<0x3fe00000) {     /* |x|<0.5 */
            if(ix<0x3e400000) {         /* if |x| < 2**-27 */
                if(huge+x>one) return x;/* return x with inexact if x!=0*/
          } else {
                t = x*x;
                p = t*(pS0+t*(pS1+t*(pS2+t*(pS3+t*(pS4+t*pS5)))));
                q = one+t*(qS1+t*(qS2+t*(qS3+t*qS4)));
                w = p/q;
                return x+x*w;
          }
        }
        /* 1> |x|>= 0.5 */
        w = one-fabs(x);
        t = w*0.5;
        p = t*(pS0+t*(pS1+t*(pS2+t*(pS3+t*(pS4+t*pS5)))));
        q = one+t*(qS1+t*(qS2+t*(qS3+t*qS4)));
        s = sqrt(t);
        if(ix>=0x3FEF3333) {    /* if |x| > 0.975 */
            w = p/q;
            t = pio2_hi-(2.0*(s+s*w)-pio2_lo);
        } else {
            w  = s;
            SET_LOW_WORD(w,0);
            c  = (t-w*w)/(s+w);
            r  = p/q;
            p  = 2.0*s*r-(pio2_lo-2.0*c);
            q  = pio4_hi-2.0*w;
            t  = pio4_hi-(p-q);
        }
        if(hx>0) return t; else return -t;
}

double atan(double x)
{

    static const double atanhi[] = {
      4.63647609000806093515e-01, /* atan(0.5)hi 0x3FDDAC67, 0x0561BB4F */
      7.85398163397448278999e-01, /* atan(1.0)hi 0x3FE921FB, 0x54442D18 */
      9.82793723247329054082e-01, /* atan(1.5)hi 0x3FEF730B, 0xD281F69B */
      1.57079632679489655800e+00, /* atan(inf)hi 0x3FF921FB, 0x54442D18 */
    };

    static const double atanlo[] = {
      2.26987774529616870924e-17, /* atan(0.5)lo 0x3C7A2B7F, 0x222F65E2 */
      3.06161699786838301793e-17, /* atan(1.0)lo 0x3C81A626, 0x33145C07 */
      1.39033110312309984516e-17, /* atan(1.5)lo 0x3C700788, 0x7AF0CBBD */
      6.12323399573676603587e-17, /* atan(inf)lo 0x3C91A626, 0x33145C07 */
    };

    static const double aT[] = {
      3.33333333333329318027e-01, /* 0x3FD55555, 0x5555550D */
     -1.99999999998764832476e-01, /* 0xBFC99999, 0x9998EBC4 */
      1.42857142725034663711e-01, /* 0x3FC24924, 0x920083FF */
     -1.11111104054623557880e-01, /* 0xBFBC71C6, 0xFE231671 */
      9.09088713343650656196e-02, /* 0x3FB745CD, 0xC54C206E */
     -7.69187620504482999495e-02, /* 0xBFB3B0F2, 0xAF749A6D */
      6.66107313738753120669e-02, /* 0x3FB10D66, 0xA0D03D51 */
     -5.83357013379057348645e-02, /* 0xBFADDE2D, 0x52DEFD9A */
      4.97687799461593236017e-02, /* 0x3FA97B4B, 0x24760DEB */
     -3.65315727442169155270e-02, /* 0xBFA2B444, 0x2C6A6C2F */
      1.62858201153657823623e-02, /* 0x3F90AD3A, 0xE322DA11 */
    };

    static const double
    one   = 1.0,
    huge   = 1.0e300;

        double w,s1,s2,z;
        int32_t ix,hx,id;

        GET_HIGH_WORD(hx,x);
        ix = hx&0x7fffffff;
        if(ix>=0x44100000) {    /* if |x| >= 2^66 */
            u_int32_t low;
            GET_LOW_WORD(low,x);
            if(ix>0x7ff00000||
                (ix==0x7ff00000&&(low!=0)))
                return x+x;             /* NaN */
            if(hx>0) return  atanhi[3]+atanlo[3];
            else     return -atanhi[3]-atanlo[3];
        } if (ix < 0x3fdc0000) {        /* |x| < 0.4375 */
            if (ix < 0x3e200000) {      /* |x| < 2^-29 */
                if(huge+x>one) return x;        /* raise inexact */
            }
            id = -1;
        } else {
        x = fabs(x);
        if (ix < 0x3ff30000) {          /* |x| < 1.1875 */
            if (ix < 0x3fe60000) {      /* 7/16 <=|x|<11/16 */
                id = 0; x = (2.0*x-one)/(2.0+x);
            } else {                    /* 11/16<=|x|< 19/16 */
                id = 1; x  = (x-one)/(x+one);
            }
        } else {
            if (ix < 0x40038000) {      /* |x| < 2.4375 */
                id = 2; x  = (x-1.5)/(one+1.5*x);
            } else {                    /* 2.4375 <= |x| < 2^66 */
                id = 3; x  = -1.0/x;
            }
        }}
    /* end of argument reduction */
        z = x*x;
        w = z*z;
    /* break sum from i=0 to 10 aT[i]z**(i+1) into odd and even poly */
        s1 = z*(aT[0]+w*(aT[2]+w*(aT[4]+w*(aT[6]+w*(aT[8]+w*aT[10])))));
        s2 = w*(aT[1]+w*(aT[3]+w*(aT[5]+w*(aT[7]+w*aT[9]))));
        if (id<0) return x - x*(s1+s2);
        else {
            z = atanhi[id] - ((x*(s1+s2) - atanlo[id]) - x);
            return (hx<0)? -z:z;
        }
}

float
atanf(float x)
{
static const float atanhi[] = {
  4.6364760399e-01, /* atan(0.5)hi 0x3eed6338 */
  7.8539812565e-01, /* atan(1.0)hi 0x3f490fda */
  9.8279368877e-01, /* atan(1.5)hi 0x3f7b985e */
  1.5707962513e+00, /* atan(inf)hi 0x3fc90fda */
};

static const float atanlo[] = {
  5.0121582440e-09, /* atan(0.5)lo 0x31ac3769 */
  3.7748947079e-08, /* atan(1.0)lo 0x33222168 */
  3.4473217170e-08, /* atan(1.5)lo 0x33140fb4 */
  7.5497894159e-08, /* atan(inf)lo 0x33a22168 */
};

static const float aT[] = {
  3.3333334327e-01, /* 0x3eaaaaaa */
 -2.0000000298e-01, /* 0xbe4ccccd */
  1.4285714924e-01, /* 0x3e124925 */
 -1.1111110449e-01, /* 0xbde38e38 */
  9.0908870101e-02, /* 0x3dba2e6e */
 -7.6918758452e-02, /* 0xbd9d8795 */
  6.6610731184e-02, /* 0x3d886b35 */
 -5.8335702866e-02, /* 0xbd6ef16b */
  4.9768779427e-02, /* 0x3d4bda59 */
 -3.6531571299e-02, /* 0xbd15a221 */
  1.6285819933e-02, /* 0x3c8569d7 */
};

static const float
one   = 1.0,
huge   = 1.0e30;

        float w,s1,s2,z;
        int32_t ix,hx,id;

        GET_FLOAT_WORD(hx,x);
        ix = hx&0x7fffffff;
        if(ix>=0x50800000) {    /* if |x| >= 2^34 */
            if(ix>0x7f800000)
                return x+x;             /* NaN */
            if(hx>0) return  atanhi[3]+atanlo[3];
            else     return -atanhi[3]-atanlo[3];
        } if (ix < 0x3ee00000) {        /* |x| < 0.4375 */
            if (ix < 0x31000000) {      /* |x| < 2^-29 */
                if(huge+x>one) return x;        /* raise inexact */
            }
            id = -1;
        } else {
        x = fabsf(x);
        if (ix < 0x3f980000) {          /* |x| < 1.1875 */
            if (ix < 0x3f300000) {      /* 7/16 <=|x|<11/16 */
                id = 0; x = ((float)2.0*x-one)/((float)2.0+x);
            } else {                    /* 11/16<=|x|< 19/16 */
                id = 1; x  = (x-one)/(x+one);
            }
        } else {
            if (ix < 0x401c0000) {      /* |x| < 2.4375 */
                id = 2; x  = (x-(float)1.5)/(one+(float)1.5*x);
            } else {                    /* 2.4375 <= |x| < 2^66 */
                id = 3; x  = -(float)1.0/x;
            }
        }}
    /* end of argument reduction */
        z = x*x;
        w = z*z;
    /* break sum from i=0 to 10 aT[i]z**(i+1) into odd and even poly */
        s1 = z*(aT[0]+w*(aT[2]+w*(aT[4]+w*(aT[6]+w*(aT[8]+w*aT[10])))));
        s2 = w*(aT[1]+w*(aT[3]+w*(aT[5]+w*(aT[7]+w*aT[9]))));
        if (id<0) return x - x*(s1+s2);
        else {
            z = atanhi[id] - ((x*(s1+s2) - atanlo[id]) - x);
            return (hx<0)? -z:z;
        }
}



float atan2f(float y, float x)
{
static const float
tiny  = 1.0e-30,
zero  = 0.0,
pi_o_4  = 7.8539818525e-01, /* 0x3f490fdb */
pi_o_2  = 1.5707963705e+00, /* 0x3fc90fdb */
pi      = 3.1415925026e+00, /* 0x40490fda */
pi_lo   = 1.5099578832e-07; /* 0x34222168 */

        float z;
        int32_t k,m,hx,hy,ix,iy;

        GET_FLOAT_WORD(hx,x);
        ix = hx&0x7fffffff;
        GET_FLOAT_WORD(hy,y);
        iy = hy&0x7fffffff;
        if((ix>0x7f800000)||
           (iy>0x7f800000))     /* x or y is NaN */
           return x+y;
        if(hx==0x3f800000) return atanf(y);   /* x=1.0 */
        m = ((hy>>31)&1)|((hx>>30)&2);  /* 2*sign(x)+sign(y) */

    /* when y = 0 */
        if(iy==0) {
            switch(m) {
                case 0:
                case 1: return y;       /* atan(+-0,+anything)=+-0 */
                case 2: return  pi+tiny;/* atan(+0,-anything) = pi */
                case 3: return -pi-tiny;/* atan(-0,-anything) =-pi */
            }
        }
    /* when x = 0 */
        if(ix==0) return (hy<0)?  -pi_o_2-tiny: pi_o_2+tiny;

    /* when x is INF */
        if(ix==0x7f800000) {
            if(iy==0x7f800000) {
                switch(m) {
                    case 0: return  pi_o_4+tiny;/* atan(+INF,+INF) */
                    case 1: return -pi_o_4-tiny;/* atan(-INF,+INF) */
                    case 2: return  (float)3.0*pi_o_4+tiny;/*atan(+INF,-INF)*/
                    case 3: return (float)-3.0*pi_o_4-tiny;/*atan(-INF,-INF)*/
                }
            } else {
                switch(m) {
                    case 0: return  zero  ;     /* atan(+...,+INF) */
                    case 1: return -zero  ;     /* atan(-...,+INF) */
                    case 2: return  pi+tiny  ;  /* atan(+...,-INF) */
                    case 3: return -pi-tiny  ;  /* atan(-...,-INF) */
                }
            }
        }
    /* when y is INF */
        if(iy==0x7f800000) return (hy<0)? -pi_o_2-tiny: pi_o_2+tiny;

    /* compute y/x */
        k = (iy-ix)>>23;
        if(k > 60) z=pi_o_2+(float)0.5*pi_lo;   /* |y/x| >  2**60 */
        else if(hx<0&&k<-60) z=0.0;     /* |y|/x < -2**60 */
        else z=atanf(fabsf(y/x));       /* safe to do y/x */
        switch (m) {
            case 0: return       z  ;   /* atan(+,+) */
            case 1: {
                      u_int32_t zh;
                      GET_FLOAT_WORD(zh,z);
                      SET_FLOAT_WORD(z,zh ^ 0x80000000);
                    }
                    return       z  ;   /* atan(-,+) */
            case 2: return  pi-(z-pi_lo);/* atan(+,-) */
            default: /* case 3 */
                    return  (z-pi_lo)-pi;/* atan(-,-) */
        }
}

double atan2(double y, double x)
{
    static const double
    tiny  = 1.0e-300,
    zero  = 0.0,
    pi_o_4  = 7.8539816339744827900E-01, /* 0x3FE921FB, 0x54442D18 */
    pi_o_2  = 1.5707963267948965580E+00, /* 0x3FF921FB, 0x54442D18 */
    pi      = 3.1415926535897931160E+00, /* 0x400921FB, 0x54442D18 */
    pi_lo   = 1.2246467991473531772E-16; /* 0x3CA1A626, 0x33145C07 */

        double z;
        int32_t k,m,hx,hy,ix,iy;
        u_int32_t lx,ly;

        EXTRACT_WORDS(hx,lx,x);
        ix = hx&0x7fffffff;
        EXTRACT_WORDS(hy,ly,y);
        iy = hy&0x7fffffff;
        if(((ix|((lx|-lx)>>31))>0x7ff00000)||
           ((iy|((ly|-ly)>>31))>0x7ff00000))    /* x or y is NaN */
           return x+y;
        if((hx-0x3ff00000|lx)==0) return atan(y);   /* x=1.0 */
        m = ((hy>>31)&1)|((hx>>30)&2);  /* 2*sign(x)+sign(y) */

    /* when y = 0 */
        if((iy|ly)==0) {
            switch(m) {
                case 0:
                case 1: return y;       /* atan(+-0,+anything)=+-0 */
                case 2: return  pi+tiny;/* atan(+0,-anything) = pi */
                case 3: return -pi-tiny;/* atan(-0,-anything) =-pi */
            }
        }
    /* when x = 0 */
        if((ix|lx)==0) return (hy<0)?  -pi_o_2-tiny: pi_o_2+tiny;

    /* when x is INF */
        if(ix==0x7ff00000) {
            if(iy==0x7ff00000) {
                switch(m) {
                    case 0: return  pi_o_4+tiny;/* atan(+INF,+INF) */
                    case 1: return -pi_o_4-tiny;/* atan(-INF,+INF) */
                    case 2: return  3.0*pi_o_4+tiny;/*atan(+INF,-INF)*/
                    case 3: return -3.0*pi_o_4-tiny;/*atan(-INF,-INF)*/
                }
            } else {
                switch(m) {
                    case 0: return  zero  ;     /* atan(+...,+INF) */
                    case 1: return -zero  ;     /* atan(-...,+INF) */
                    case 2: return  pi+tiny  ;  /* atan(+...,-INF) */
                    case 3: return -pi-tiny  ;  /* atan(-...,-INF) */
                }
            }
        }
    /* when y is INF */
        if(iy==0x7ff00000) return (hy<0)? -pi_o_2-tiny: pi_o_2+tiny;

    /* compute y/x */
        k = (iy-ix)>>20;
        if(k > 60) z=pi_o_2+0.5*pi_lo;  /* |y/x| >  2**60 */
        else if(hx<0&&k<-60) z=0.0;     /* |y|/x < -2**60 */
        else z=atan(fabs(y/x));         /* safe to do y/x */
        switch (m) {
            case 0: return       z  ;   /* atan(+,+) */
            case 1: {
                      u_int32_t zh;
                      GET_HIGH_WORD(zh,z);
                      SET_HIGH_WORD(z,zh ^ 0x80000000);
                    }
                    return       z  ;   /* atan(-,+) */
            case 2: return  pi-(z-pi_lo);/* atan(+,-) */
            default: /* case 3 */
                    return  (z-pi_lo)-pi;/* atan(-,-) */
        }
}

