/*
-- File: stddef.h
--
-- Contents: ISO C99 Standard, 7.17 Common definitions <stddef.h>
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model 
-- captures an ASIP Designer Design Technique. The model and all associated 
-- documentation are proprietary to Synopsys, Inc. and may only be used 
-- pursuant to the terms and conditions of a written license agreement with 
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution 
-- of the Synopsys processor model or the associated  documentation is 
-- strictly prohibited. 
*/


#ifndef __clang__
#ifndef _STDDEF_H
#define _STDDEF_H

typedef signed int    ptrdiff_t;
typedef unsigned int  size_t;
typedef int           wchar_t;

#define NULL 0
#define offsetof(s,m) (size_t)(&(((s *)0)->m))

#endif /* stddef.h */
#else
# include_next "stddef.h"
#endif
