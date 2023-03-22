/*
-- File: stdbool.h
--
-- Contents: ISO C99 Standard, 7.26.7 Boolean type and values <stdbool.h>
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

#ifndef _STDBOOL_H
#define _STDBOOL_H

#define true 1
#define false 0
#define __bool_true_false_are_defined 1

#endif /* stdbool.h */

#else
# include_next "stdbool.h"
#endif // __clang__
