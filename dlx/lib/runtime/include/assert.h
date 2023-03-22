/*
-- File: assert.h
--
-- Contents: ISO C99 Standard, 7.2 Diagnostics <assert.h>
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model 
-- captures an ASIP Designer Design Technique. The model and all associated 
-- documentation are proprietary to Synopsys, Inc. and may only be used 
-- pursuant to the terms and conditions of a written license agreement with 
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution 
-- of the Synopsys processor model or the associated  documentation is 
-- strictly prohibited. 
*/


#ifdef _ASSERT_H
#undef _ASSERT_H
#undef assert
#endif

#define _ASSERT_H

#ifdef  NDEBUG
# define assert(expr)   ((void)0)
#else
# define assert(expr)   ((expr) ? (void)0 : chess_assert(0))
#endif
