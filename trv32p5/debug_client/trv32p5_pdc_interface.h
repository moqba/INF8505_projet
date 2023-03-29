/*
-- File : trv32p5_pdc_interface.h
--
-- Contents : Specialisation of Checkers_pdc_interface for TRV32P5 procesor
--
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

#ifndef INCLUDED_TRV32P5_PDC_INTERFACE_H__
#define INCLUDED_TRV32P5_PDC_INTERFACE_H__

#include <vbit.h>

#include "checkers_pdc_interface.h"

// #define TRACE_PDC_API
#ifdef TRACE_PDC_API
#include "checkers_debugger_logger.h"
class trv32p5_pdc_interface_;
typedef Checkers_debugger_logger<trv32p5_pdc_interface_> trv32p5_pdc_interface;
#define trv32p5_pdc_interface trv32p5_pdc_interface_
#endif

class trv32p5_pdc_interface : public Checkers_pdc_interface {
public:
  trv32p5_pdc_interface(int coreid, std::string server, int port=41001);
  virtual ~trv32p5_pdc_interface() = default;

  VBitWrapper get_instruction_at(AddressType) override;
  void put_instruction_at(AddressType, VBitWrapper) override;
  AddressType next_instruction(AddressType) override;
  AddressType prev_instruction(AddressType) override;

  void populate_common_scl_regs() override;
};

#ifdef TRACE_PDC_API
#undef trv32p5_pdc_interface
#endif

#endif // def INCLUDED_TRV32P5_PDC_INTERFACE_H__
