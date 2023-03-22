/*
-- File: stdalign.h
--
-- Copyright (c) 2017 Synopsys, Inc. This processor model and the associated
-- documentation are proprietary to Synopsys, Inc.  This model may only be
-- used in accordance with the terms and conditions of a written license 
-- agreement with Synopsys, Inc.  All other use, reproduction, or distribution 
-- of this model are strictly prohibited.
*/

#ifndef __clang__

#ifndef _STDALIGN_H
#define _STDALIGN_H

#define __alignas_is_defined 1
#define __alignof_is_defined 1

#endif /* stdalign.h */

#else
# include_next "stdalign.h"
#endif // __clang__
