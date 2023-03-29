; Copyright (c) 2021 Synopsys, Inc. This Synopsys processor model
; captures an ASIP Designer Design Technique. The model and all associated
; documentation are proprietary to Synopsys, Inc. and may only be used
; pursuant to the terms and conditions of a written license agreement with
; Synopsys, Inc.  All other use, reproduction, modification, or distribution
; of the Synopsys processor model or the associated  documentation is
; strictly prohibited.

; File: test_20_j.s -- assembly program for jump instruction

.text_segment PM 0
.entry_point
        addi x1,x0,1  ;  0
        addi x2,x1,2  ;  4
        addi x3,x2,3  ; 12  (no delay slot)
  jal  x7,La           ;  8
        addi x3,x3,4  ; 16
        addi x3,x3,5  ; 20
La:     addi x6,x3,6  ; 24
        nop    ; 28
        nop    ; 32
        nop    ; 36
        nop    ; 40
