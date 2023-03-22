/*
-- File: float.h
--
-- Contents: ISO C99 Standard, 7.7 Characteristics of floating types <float.h>
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model 
-- captures an ASIP Designer Design Technique. The model and all associated 
-- documentation are proprietary to Synopsys, Inc. and may only be used 
-- pursuant to the terms and conditions of a written license agreement with 
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution 
-- of the Synopsys processor model or the associated  documentation is 
-- strictly prohibited. 
*/



#ifndef _FLOAT_H
#define _FLOAT_H

#define FLT_ROUNDS      1
#define FLT_EVAL_METHOD	0
#define DECIMAL_DIG	21

#define FLT_RADIX 2
#define FLT_MANT_DIG 24
#define FLT_DIG 6
#define FLT_EPSILON 1.19209290e-07F
#define FLT_MIN_EXP (-125)
#define FLT_MIN 1.17549435e-38F
#define FLT_MIN_10_EXP (-37)
#define FLT_MAX_EXP 128
#define FLT_MAX 3.40282347e+38F
#define FLT_MAX_10_EXP 38

#define DBL_MANT_DIG 53
#define DBL_DIG 15
#define DBL_EPSILON 2.2204460492503131e-16
#define DBL_MIN_EXP (-1021)
#define DBL_MIN 2.2250738585072014e-308
#define DBL_MIN_10_EXP (-307)
#define DBL_MAX_EXP 1024
#define DBL_MAX 1.7976931348623157e+308
#define DBL_MAX_10_EXP 308

#define LDBL_MANT_DIG     DBL_MANT_DIG 
#define LDBL_DIG          DBL_DIG 
#define LDBL_EPSILON      DBL_EPSILON 
#define LDBL_MIN_EXP      DBL_MIN_EXP 
#define LDBL_MIN          DBL_MIN 
#define LDBL_MIN_10_EXP   DBL_MIN_10_EXP 
#define LDBL_MAX_EXP      DBL_MAX_EXP 
#define LDBL_MAX          DBL_MAX 
#define LDBL_MAX_10_EXP   DBL_MAX_10_EXP 

#endif /* float.h */
