; Copyright (c) 2021 Synopsys, Inc. This Synopsys processor model
; captures an ASIP Designer Design Technique. The model and all associated
; documentation are proprietary to Synopsys, Inc. and may only be used
; pursuant to the terms and conditions of a written license agreement with
; Synopsys, Inc.  All other use, reproduction, modification, or distribution
; of the Synopsys processor model or the associated  documentation is
; strictly prohibited.

; test_24_jal.s -- assembly test program for call instruction

.text_segment PM 0
.entry_point
        addi x4,x0,1  ;  0
        addi x4,x4,2  ;
  nop             ;
        addi x5,x4,3  ; (no delay slot)
  jal x1, Fa     ; 12
        addi x5,x5,5  ;
        addi x6,x5,6  ; r6 = 18
        nop    ;
        nop    ;
        nop    ;
        nop    ; 40

.text_segment PM 100
Fa:  addi x5,x5,1
  nop
  jalr x1,x1,0
  nop    ;     (no delay slot)
  nop    ; 116 (no delay slot), r3 = 7
  nop
  nop
