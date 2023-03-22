/*
-- File : common.h
--
-- Contents : common defines for the PLX processor.
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/



#ifndef _common_h
#define _common_h

/*
There are 2 views on the core:

    model view        | ST | MT |
    =============================
    pipeline depth    |  1 |  4 |
    number of threads |  1 |  4 |

There is one common description with some local specialization for the 2 views,
using the C preprocessor and a define:

    #define _THREADED

These views have different usage:

    usage                 | view | project file     |
    =================================================
    compiler & assembler  |  MT  | lib/plx.prx      |
    ISS (single-threaded) |  ST  | iss/plx_st.prx   |
    ISS (multi-threaded)  |  MT  | iss/plx_ca.prx   |
    hardware              |  MT  | hdl/plx_vhdl.prx |
*/

#include "iss_defines.h"

#if !defined(_ISS_ST)
#define _THREADED
#endif

#define CSIZE_NBIT        4
#define CSIZE             (1<<CSIZE_NBIT) // number of threads
// scheduler supports 16 threads but only 8 are instantiated
#define actual_CSIZE_NBIT 3
#define actual_CSIZE      (1<<actual_CSIZE_NBIT)

#endif  // _common_h
