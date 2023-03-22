/*
-- File: stdalign.h
--
-- Copyright (c) 2017 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
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
