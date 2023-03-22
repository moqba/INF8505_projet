/*
-- File : tlx_define.h
--
-- Contents : Common macro's.
--
-- Copyright (c) 2016-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

// memory sizes
#define PM_SIZE_NBIT   20       // program-memory size=2**PM_SIZE_NBIT in bytes
#define DM_SIZE_NBIT   24       //    data-memory size=2**DM_SIZE_NBIT in bytes

// configuration
#define TLX_HAS_DOLOOP
#define TLX_HAS_ZLOOP
#define TLX_IS_LITTLE_ENDIAN
#define TLX_HAS_IRQ             // 16 irq-pins
#define TLX_R_SZ 16             // 16 regs
