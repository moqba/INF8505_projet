
; File: test_20_j.s -- assembly program for jump instruction

.text_segment PM 0
.entry_point
        addi r1,r0,#1        ;  0
        addi r1,r1,#2        ;  4
        j #La                ;  8
        addi r1,r1,#3        ; 12  (delay slot)
        addi r1,r1,#4        ; 16
        addi r1,r1,#5        ; 20
La:     addi r1,r1,#6        ; 24
        addi r1,r1,#7        ; 28
        nop                  ; 32
        nop                  ; 36
        nop                  ; 40
