; Copyright (c) 2021 Synopsys, Inc. This Synopsys processor model
; captures an ASIP Designer Design Technique. The model and all associated
; documentation are proprietary to Synopsys, Inc. and may only be used
; pursuant to the terms and conditions of a written license agreement with
; Synopsys, Inc.  All other use, reproduction, modification, or distribution
; of the Synopsys processor model or the associated  documentation is
; strictly prohibited.

; test_10_breakpoints.s -- assembly program for breakpoints

.text_segment PM 0
.entry_point
        ori x1,x0, 1  ;  0
        ori x2,x0, 2  ;  4
        ori x3,x0, 3  ;  8
        ori x4,x0, 4  ; 12
        ori x5,x0, 5  ; 16
        ori x6,x0, 6  ; 20
        nop   ; 24
        nop   ; 28
