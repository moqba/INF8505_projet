
; test_22_br_taken.s -- assembly program for branch instruction

.text_segment PM 0
.entry_point
        addi r2,r0,#1        ;  0
        addi r2,r2,#2        ;
        nop             ;
        seq r13, r0, r0 ;
        bnez r13, #La   ; 16
        addi r3,r2,#3        ; (delay slot)
        addi r3,r3,#4        ; (delay slot)
        addi r3,r3,#5        ;
La:     addi r6,r3,#6        ; 32
        nop                ;
        nop                ;
        nop                ;
        nop                ; 48
