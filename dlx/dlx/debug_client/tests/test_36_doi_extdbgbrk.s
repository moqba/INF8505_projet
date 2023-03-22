
; test_25_jalr.s -- assembly test program for call instruction

.text_segment PM 0
.entry_point
        addi r2,r0,#1
        addi r3,r0,#10
        addi r4,r0,#100
        addi r5,r0,#1000
        addi r6,r0,#10000
        addi r7,r0,#12500
        slli r7,r7,#3
        addi r8,r0,#15625
        slli r8,r8,#6
        addi r9,r0,#1024
        nop
        nop

        add  r2,r2,r3
        sw   r2,(r9+=4)   ; DMw[1024]
        nop
        nop

        doi  3, 8
        add  r2,r2,r4     ; delay slot
        add  r2,r2,r5     ; delay slot

; begin of loop
        add  r2,r2,r6
.eol
        sw   r2,(r9+=4)   ; DMw[1028] DMw[1032] DMw[1036]
; end of loop

        add  r2,r2,r7
        sw   r2,(r9+=4)   ; DMw[1040]

        nop
        nop
        nop
        nop
        nop
        nop
