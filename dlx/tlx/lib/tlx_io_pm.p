/*
-- File : tlx_io.p
--
-- Contents : Definition of the TLX IO interface.
--
-- Copyright (c) 2014-2021 Synopsys, Inc. This processor model and the associated
-- documentation are proprietary to Synopsys, Inc.  This model may only be
-- used in accordance with the terms and conditions of a written license
-- agreement with Synopsys, Inc.  All other use, reproduction, or distribution
-- of this model are strictly prohibited.
*/

//#include "tlx_define.h"

#include "module_iwnop.p"

#define PM_SIZE_NBIT   18 /* program-memory size=2**PM_SIZE_NBIT in instruction- words */

#define PM_ADDR_SZ        32
#define PM_LOG_ADDR_STRIDE 0
#define PM_ADDR_STRIDE     1
#define PM_ROOT_WORD_SIZE 16
#define PM_WORD_SZ        32

// memory size
#define PM_SIZE (2**PM_SIZE_NBIT)

io_interface insert_wait_nop_pm : iwnop_module<AWIDTH=PM_ADDR_SZ, ASTRIDE=PM_ADDR_STRIDE,
                                               DWIDTH=PM_WORD_SZ,
                                               M_SIZE_NBIT = PM_SIZE_NBIT> (PM)
{
    mem fcPM[PM_SIZE,PM_ADDR_STRIDE]<iword,addr> access {
        fcpm_ld: fcpm_rd`1` = fcPM[fcpm_addr]`1`;
        fcpm_st: fcPM[fcpm_addr] = fcpm_wr;
    };
    inport  fcpm_ack<bool>;     // Slave acknowledges read or write request
}

io_interface insert_ack_pm : insert_ack_module<AWIDTH=PM_ADDR_SZ, ASTRIDE=PM_ADDR_STRIDE,
                                               DWIDTH=PM_WORD_SZ,
                                               M_SIZE_NBIT = PM_SIZE_NBIT> (fcPM, fcpm_ack)
{
    mem tbPM[PM_SIZE,PM_ADDR_STRIDE]<iword,addr> access {
        tbpm_ld: tbpm_rd`1` = tbPM[tbpm_addr]`1`;
        tbpm_st: tbPM[tbpm_addr] = tbpm_wr;
    };
}
