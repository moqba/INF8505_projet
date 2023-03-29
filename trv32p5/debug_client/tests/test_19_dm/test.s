; Copyright (c) 2021 Synopsys, Inc. This Synopsys processor model
; captures an ASIP Designer Design Technique. The model and all associated
; documentation are proprietary to Synopsys, Inc. and may only be used
; pursuant to the terms and conditions of a written license agreement with
; Synopsys, Inc.  All other use, reproduction, modification, or distribution
; of the Synopsys processor model or the associated  documentation is
; strictly prohibited.

.text_segment PM 0
.entry_point
        ori  x2,x0,1000
        ori  x3,x0,256
        ori  x4,x0,500
        ori  x5,x0,1024
        nop
        nop
        sw x2,0(x3)
        sw x3,0(x2)
        sw x4,0(x5)
        nop
        nop
        nop


