; Copyright (c) 2021 Synopsys, Inc. This Synopsys processor model
; captures an ASIP Designer Design Technique. The model and all associated
; documentation are proprietary to Synopsys, Inc. and may only be used
; pursuant to the terms and conditions of a written license agreement with
; Synopsys, Inc.  All other use, reproduction, modification, or distribution
; of the Synopsys processor model or the associated  documentation is
; strictly prohibited.

.text_segment PM 0
.entry_point
        add x10, x0, x0
        nop
        nop
        nop
        ori x10, x10, 1
        ori x10, x10, 2
        ori x10, x10, 4
        ori x10, x10, 8
        ori x10, x10, 16
        ori x10, x10, 32
        ori x10, x10, 64
        nop
        nop
        nop
        nop
        ; too far
        ori x10, x10, 128
        jal x0, 0
