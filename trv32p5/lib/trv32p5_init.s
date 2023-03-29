; Copyright (c) 2019-2021 Synopsys, Inc. This Synopsys processor model
; captures an ASIP Designer Design Technique. The model and all associated
; documentation are proprietary to Synopsys, Inc. and may only be used
; pursuant to the terms and conditions of a written license agreement with
; Synopsys, Inc.  All other use, reproduction, modification, or distribution
; of the Synopsys processor model or the associated  documentation is
; strictly prohibited.

.direct_eval >>,&,(,),+

#include "trv32p5_define.h"

; initialisation before entering the main function.
.text global 0 _main_init

  ; Init stack pointer
  lui  x2, ((_sp_start_DMb+2048)>>12)
  addi x2, x2, (_sp_start_DMb&0xfff)

  ; The following 'nops' are extra guards in case that model changes introduce
  ; hazards. Remove them if not needed.
  ; Note: RISC-V ISA 'nop' = 'addi x0, x0, 0'. Check if you see conflicts
.lrepeat 4
  nop

; area to load main(argc,char* argv[]) arguments
; Only for ISS simulation, ISS loads argc/argv into memory and initializes
; argument registers (argc, argv)
.bss global 0 _main_argv_area DMb 256
