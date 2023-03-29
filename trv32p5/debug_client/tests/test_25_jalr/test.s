; Copyright (c) 2021 Synopsys, Inc. This Synopsys processor model
; captures an ASIP Designer Design Technique. The model and all associated
; documentation are proprietary to Synopsys, Inc. and may only be used
; pursuant to the terms and conditions of a written license agreement with
; Synopsys, Inc.  All other use, reproduction, modification, or distribution
; of the Synopsys processor model or the associated  documentation is
; strictly prohibited.

; test_25_jalr.s -- assembly test program for call instruction

.text_segment PM 0
.entry_point
        addi x2,x0,1  ;  0
        addi x2,x2,2  ;
  ori x13, x0, Fa
        addi x3,x2,3  ;  (no delay slot)
        addi x3,x3,5  ;  (no delay slot)
  jalr x1, x13, 0
        addi x6,x3,6  ; r6 = 18
        nop    ;
        nop    ;
        nop    ;
        nop    ; 40
        nop    ;
        nop    ;

.text_segment PM 100
Fa:  addi x3,x3,1
  nop
  jalr x1,x1,0
  nop    ;     (no delay slot)
  nop    ; 116 (no delay slot), r3 = 12
  nop
  nop
