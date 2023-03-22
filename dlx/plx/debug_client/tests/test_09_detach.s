
; infinite counting loop

.text_segment PM 0
.entry_point
        lw r2,4(r0)
        addi r2,r2,#1
        sw r2,4(r0)
        j #-12
        nop
