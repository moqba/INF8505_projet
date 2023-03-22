# read_elf -e -pPMb=8 -mDMb=8 -t../../bin/readelf_vlog.tcl test -o data

# open file for PM
set PM [open data.PMb w]
#open file for each DM bank
set bank(DMb,0) [open data.DM0 w]
set bank(DMb,1) [open data.DM1 w]
set bank(DMb,2) [open data.DM2 w]
set bank(DMb,3) [open data.DM3 w]

foreach seg [readelf::segments] {
    if {[dict get $seg memory_name] eq "PMb"} {
        puts $PM "@0"
        set addr [dict get $seg paddr]
        foreach v [dict get $seg data] {
            puts $PM [format "@%x %x" $addr $v]
            incr addr
        }
    } else {
        set addr [dict get $seg paddr]
        foreach v [dict get $seg data] {
            puts $bank([dict get $seg memory_name],[expr {$addr % 4}]) [format "@%x %x" [expr {$addr >> 2}] $v]
            incr addr
        }
    }
}

foreach {k v} [array get bank] {
    close $v
}


