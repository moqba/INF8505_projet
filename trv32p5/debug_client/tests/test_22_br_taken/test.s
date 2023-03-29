; Copyright (c) 2021 Synopsys, Inc. This Synopsys processor model
; captures an ASIP Designer Design Technique. The model and all associated
; documentation are proprietary to Synopsys, Inc. and may only be used
; pursuant to the terms and conditions of a written license agreement with
; Synopsys, Inc.  All other use, reproduction, modification, or distribution
; of the Synopsys processor model or the associated  documentation is
; strictly prohibited.

; test_22_br_taken.s -- assembly program for branch instruction
.text_segment PM 0
.entry_point
        addi x3,x0,1
        addi x3,x3,2
        addi x3,x3,4
        addi x3,x3,8
        beq  x0, x0, La
        addi x3,x3,64
        addi x3,x3,128
La:     addi x3,x3,16
        addi x3,x3,32
        nop
        nop
        nop
        nop
