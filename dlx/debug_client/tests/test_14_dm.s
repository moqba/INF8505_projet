
; test_14_dm.s -- assembly test program for testing DM access

.text_segment PM 0
.entry_point
        ori  r2,r0,#1000 
        ori  r3,r0,#256 
        ori  r4,r0,#500 
        ori  r5,r0,#1024 
        nop
        nop
        sw r2,0(r3)    
        sw r3,0(r2)    
        sw r4,0(r5)    
        nop
        nop
        nop


