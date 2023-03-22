#!/bin/env tct_tclsh

# Tcl script for generating instruction codes needed by debug client
# Usage: tct_tclsh ins2c.tcl

package require TctTclUtilsParseArgs

set thisdir [file dirname [file normalize [info script]]]

set LIBDIR [file join $thisdir .. lib]
set PROC blx
set HDL vlog
set GODIR [file join $thisdir .. hdl ${PROC}_${HDL}]

# parse script args
if {[llength $::argv] > 0} {
  # positional arguments
  set vargs {
    # arg or {arg set}
  }

  # options
  set vopts {
    {{-P}          v LIBDIR}
    {{-p}          v PROC}
    {{-hdl}        v HDL}
    {{-go-dir}     v GODIR}
    # {"-pat*" b/v/l name}
    # {"-pat*" b/v/l name set}
    # b: boolean, v: variable, l: list
  }

  if { [catch {::tclutils::parse_args $vargs $vopts $::argv [info script]} msg] } {
    puts "ERROR: $msg"
    exit 1
  }
}

set pdc_register_moves [file join $thisdir pdc_register_moves]

# Get the opcodes as generated by Go
set opcodes [file join $GODIR pdc_opcodes.h]
if {![file exists $opcodes]} {
    puts stderr "Could not find file '$opcodes', run Go and re-run this script afterwards."
    exit 1
}
file copy -force $opcodes $thisdir
set init_opcodes [file join $GODIR pdc_init_bpwp_codes.c]
if {![file exists $init_opcodes]} {
    puts stderr "Could not find file '$init_opcodes', run Go and re-run this script afterwards."
    exit 1
}
file copy -force $init_opcodes $thisdir

# Assemble and disassemble the register moves
puts {Compiling pdc_register_moves.s}
set cmd [list chesscc +a -P $LIBDIR -o $pdc_register_moves.x $pdc_register_moves.s -p $PROC -X darts.ass.conflicts=none]
if {[catch {exec -ignorestderr {*}$cmd} msg errd]} {
    puts stderr "Could not assemble 'pdc_register_moves.s'."
    puts stderr "Failing command: $cmd"
    exit 1
}

puts {Disassembling pdc_register_moves.x}
set cmd [list chesscc +d -P $LIBDIR -o $pdc_register_moves.dis $pdc_register_moves.x -p $PROC -X darts.dis.noinstr=off -X darts.dis.format=lst -X darts.dis.iradix=bin]
if {[catch {exec -ignorestderr {*}$cmd} msg]} {
    puts stderr "Could not disassemble 'pdc_register_moves.x'."
    puts stderr "Failing command: $cmd"
    exit 1
}

# Extract the register moves
set f [open $pdc_register_moves.c w]

puts $f "";
puts $f "/*";
puts $f "-- File : pdc_register_moves.c";
puts $f "--";
puts $f "-- Contents : Tables with processor specific register move instruction codes.";
puts $f "--";
puts $f "-- NOTE: this file is generated AUTOMATICALLY from the file pdc_register_moves.s";
puts $f "--       using the commands in ins2c.tcl";
puts $f "*/";
puts $f "";
puts $f "";
puts $f "#include \"pdc_commands.h\" ";
puts $f "";
puts $f "void pdc_commands::init_reg_move_codes() {";

puts {Parsing disassembly pdc_register_moves.dis}
set d [open $pdc_register_moves.dis r]
set ll [split [read $d] \n]
close $d

set swbreak 0
set indjump 0
set reg_get {}
set reg_put {}

# regular expressions to parse disassembly
set re_bin {"[01]+"(?:\s+"[01]+")*} ; # one or more quoted bin-strings
set re_reg_get [format %s%s ($re_bin) {\s+ sw \s+ (\S+?) \s* ,}]
set re_reg_put [format %s%s ($re_bin) {\s+ lw \s+ (\S+?) \s* ,}]
set re_jmp     [format %s%s ($re_bin) {\s+ jr \s+ r1}]
set re_brk32   [format %s%s ($re_bin) {\s+ swbrk}]

# remove quotes and spaces from instruction encodings
proc fmt_instr {m} {
  set b [string map {{"} {} { } {}} $m] ; # remove " and space
  return "instr_type([string length $b],false,\"$b\",2)"
}

foreach l $ll {
    if {[regexp -expanded $re_reg_get $l m instr reg]} {
        puts $f "    reg_get_code\[\"[string tolower $reg]\"\] = [fmt_instr $instr]; // $m"
        lappend reg_get $reg
    }
    if {[regexp -expanded $re_reg_put $l m instr reg]} {
        puts $f "    reg_put_code\[\"[string tolower $reg]\"\] = [fmt_instr $instr]; // $m"
        lappend reg_put $reg
    }
    if {[regexp -expanded $re_jmp $l m instr]} {
        puts $f "    goto_r1_code = [fmt_instr $instr]; // $m"
        set indjump 1
        puts "INFO: Found indirect jump instruction"
    }
    if {[regexp -expanded $re_brk32 $l m instr]} {
        puts $f "    core_sw_break_instr = [fmt_instr $instr]; // $m"
        set swbreak 1
        puts "INFO: Found 32b software break instruction"
    }
}

if {$swbreak == 0} {
  puts $f {#error "No software break instruction identified"}
  puts "ERROR: No software break instruction identified"
}
if {$indjump == 0} {
  puts $f {#error "No indirect jump instruction identified"}
  puts "ERROR: No indirect jump instruction identified"
}

puts $f "}";
close $f

puts "INFO: Found reg_get codes for [join $reg_get {, }]"
puts "INFO: Found reg_put codes for [join $reg_put {, }]"

puts {Generated pdc_register_moves.c}