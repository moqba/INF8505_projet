; Copyright (c) 2021 Synopsys, Inc. This Synopsys processor model
; captures an ASIP Designer Design Technique. The model and all associated
; documentation are proprietary to Synopsys, Inc. and may only be used
; pursuant to the terms and conditions of a written license agreement with
; Synopsys, Inc.  All other use, reproduction, modification, or distribution
; of the Synopsys processor model or the associated  documentation is
; strictly prohibited.

.text_segment PM 0
.entry_point

  // test.tcl initializes all X[] to 0

  addi x1,  x1,  1
  addi x2,  x2,  1
  addi x3,  x3,  1
  addi x4,  x4,  1
  addi x5,  x5,  1
  addi x6,  x6,  1
  addi x7,  x7,  1
  addi x8,  x8,  1
  addi x9,  x9,  1
  addi x10, x10, 1
  addi x11, x11, 1
  addi x12, x12, 1
  addi x13, x13, 1
  addi x14, x14, 1
  addi x15, x15, 1
  addi x16, x16, 1
  addi x17, x17, 1
  addi x18, x18, 1
  addi x19, x19, 1
  addi x20, x20, 1
  addi x21, x21, 1
  addi x22, x22, 1
  addi x23, x23, 1
  addi x24, x24, 1
  addi x25, x25, 1
  addi x26, x26, 1
  addi x27, x27, 1
  addi x28, x28, 1
  addi x29, x29, 1
  addi x30, x30, 1
  addi x31, x31, 1

.stop
l_exit:
  j 0

