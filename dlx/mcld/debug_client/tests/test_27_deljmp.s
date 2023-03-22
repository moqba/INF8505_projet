
; test_25_jalr.s -- assembly test program for call instruction

.text_segment PM 0
.entry_point
        addi r2,r0,#100
        addi r3,r0,#10
        addi r4,r0,#1
        addi r5,r0,#1000
        addi r6,r0,#10000
        addi r7,r0,#12500
        slli r7,r7,#3
        addi r8,r0,#15625
        slli r8,r8,#6
        addi r9,r0,#1024
        ori r14, r0, #Fa

        nop
        nop

        lhi  r20,#-1
        ori r20,r20,#0xFFFF
        div r20, r20

        add  r2,r2,r3
        sw   r2,(r9+=4)   ; DMw[1024]
        nop
        nop
        jalr r14
        add  r2,r2,r12    ; delay slot - hw_stall due to div
        add  r2,r2,r5     ; delay slot

        add  r2,r2,r8
        sw   r2,(r9+=4)   ; DMw[1032]

        nop
        nop
        nop
        nop
        nop
        nop

.text_segment PM 140
Fa:
        add  r2,r2,r6
        sw   r2,(r9+=4)   ; DMw[1028]
        jr   r15
        add  r2,r2,r7     ; delay slot
        nop
        nop
