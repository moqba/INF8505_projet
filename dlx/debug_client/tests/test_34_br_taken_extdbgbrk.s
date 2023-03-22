
; assembly test program

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
        beqz r0, #Fa
        add  r2,r2,r4     ; delay slot
        add  r2,r2,r5     ; delay slot

Ra:
        add  r2,r2,r8
        sw   r2,(r9+=4)   ; DMw[1032]

        nop
        nop
        nop
        nop
        nop
        nop

.text_segment PM 116
Fa:
        add  r2,r2,r6
        sw   r2,(r9+=4)   ; DMw[1028]
        j    #Ra
        add  r2,r2,r7     ; delay slot
        nop
        nop
