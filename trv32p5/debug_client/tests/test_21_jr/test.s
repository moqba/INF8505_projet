; Copyright (c) 2021 Synopsys, Inc. This Synopsys processor model
; captures an ASIP Designer Design Technique. The model and all associated
; documentation are proprietary to Synopsys, Inc. and may only be used
; pursuant to the terms and conditions of a written license agreement with
; Synopsys, Inc.  All other use, reproduction, modification, or distribution
; of the Synopsys processor model or the associated  documentation is
; strictly prohibited.

; test_21_jr.s -- assembly program for jump instruction

.text_segment PM 0
.entry_point
        addi x2,x0,1  ;  0
        addi x2,x2,2  ;
  nop
  ori x13, x0, La
        addi x3,x2,3  ; (no delay slot)
        addi x3,x3,4  ; (no delay slot)
  jalr x13, x13, 0          ; 16
        addi x3,x3,5  ;
La:     addi x6,x3,6  ; 32
        nop    ;
        nop    ;
        nop    ;
        nop    ; 48
