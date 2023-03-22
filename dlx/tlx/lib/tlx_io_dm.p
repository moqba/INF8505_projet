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

#include "tlx_define.h"

#include "module_merge_strb4.p"
#include "module_iwnop_strb.p"

// endianness
#define IS_BIG_ENDIAN 0

// data sizes in memory
#define BYTE_SZ     8
#define HALFWORD_SZ 16
#define WORD_SZ     32

// address size
#define ADDR_SZ 32

// memory size
#define DM_SIZE (2**DM_SIZE_NBIT)
#define DRAM_SIZE_BY_4 (2**(DM_SIZE_NBIT-2))

io_interface merge_dm : merge_module_strb4<BE=IS_BIG_ENDIAN,
                                           AWIDTH=ADDR_SZ,
                                           BWIDTH=BYTE_SZ, HWIDTH=HALFWORD_SZ, WWIDTH=WORD_SZ,
                                           M_SIZE_NBIT = DM_SIZE_NBIT> (DMb, DMh, DMw)
{
    mem swDM[DM_SIZE,4]<w32,addr> access {
        swdm_ld: swdm_rd`1` = swDM[swdm_addr]`1`;
        swdm_st: swDM[swdm_addr`0`]`1` = swdm_wr`1`;
    };
    outport swdm_strb<uint4_t>; // Read/write strobe
}

io_interface insert_wait_nop_dm : iwnop_module_strb<AWIDTH=ADDR_SZ, ASTRIDE=4,
                                                    DWIDTH=WORD_SZ,
                                                    M_SIZE_NBIT = DM_SIZE_NBIT> (swDM, swdm_strb)
{
    mem fcDM[DM_SIZE,4]<w32,addr> access {
        fcdm_ld: fcdm_rd`1` = fcDM[fcdm_addr]`1`;
        fcdm_st: fcDM[fcdm_addr] = fcdm_wr;
    };
    outport fcdm_strb<uint4_t>; // Read/write strobe
    inport  fcdm_ack<bool>;     // Slave acknowledges read or write request
}

io_interface insert_ack_dm : insert_ack_module_strb<AWIDTH=ADDR_SZ, ASTRIDE=4,
                                                    DWIDTH=WORD_SZ,
                                                    M_SIZE_NBIT = DM_SIZE_NBIT> (fcDM, fcdm_strb, fcdm_ack)
{
    mem tbDM[DM_SIZE,4]<w32,addr> access {
        tbdm_ld: tbdm_rd`1` = tbDM[tbdm_addr]`1`;
        tbdm_st: tbDM[tbdm_addr] = tbdm_wr;
    };
    outport tbdm_strb<uint4_t>; // Read/write strobe
}

io_interface split_dm : split_module_strb4<BE=IS_BIG_ENDIAN,
                                           AWIDTH=32,
                                           BWIDTH=8, WWIDTH=32,
                                           M_SIZE_NBIT = DM_SIZE_NBIT> (tbDM, tbdm_strb)
{
    // 4 byte addressed testbench memory banks
    mem tbDRAM0 [DRAM_SIZE_BY_4,1]<w08,addr> access {
    tbdram0_ld: tbdram0_read `1` = tbDRAM0[tbdram0_addr] `1`;
    tbdram0_st: tbDRAM0[tbdram0_addr] = tbdram0_write;
    };
    mem tbDRAM1 [DRAM_SIZE_BY_4,1]<w08,addr> access {
    tbdram1_ld: tbdram1_read `1` = tbDRAM1[tbdram1_addr] `1`;
    tbdram1_st: tbDRAM1[tbdram1_addr] = tbdram1_write;
    };
    mem tbDRAM2 [DRAM_SIZE_BY_4,1]<w08,addr> access {
    tbdram2_ld: tbdram2_read `1` = tbDRAM2[tbdram2_addr] `1`;
    tbdram2_st: tbDRAM2[tbdram2_addr] = tbdram2_write;
    };
    mem tbDRAM3 [DRAM_SIZE_BY_4,1]<w08,addr> access {
    tbdram3_ld: tbdram3_read `1` = tbDRAM3[tbdram3_addr] `1`;
    tbdram3_st: tbDRAM3[tbdram3_addr] = tbdram3_write;
    };
}
