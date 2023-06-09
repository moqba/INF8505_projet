#!/usr/bin/env tct_tclsh
#
# Copyright (c) 2021 Synopsys, Inc. This Synopsys processor model
# captures an ASIP Designer Design Technique. The model and all associated
# documentation are proprietary to Synopsys, Inc. and may only be used
# pursuant to the terms and conditions of a written license agreement with
# Synopsys, Inc.  All other use, reproduction, modification, or distribution
# of the Synopsys processor model or the associated  documentation is
# strictly prohibited.
#

# Tcl script for generating instruction codes needed by debug client
# Usage: tct_tclsh ins2c.tcl

package require TctTclUtilsParseArgs

set thisdir [file dirname [info script]]

set LIBDIR [file join $thisdir .. lib]
set PROC trv32p5
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

# Get the PDC opcodes generated by Go
set pdc_opcodes [file join $GODIR pdc_opcodes.h]
if {![file exists $pdc_opcodes]} {
    puts stderr "Could not find file '$pdc_opcodes', run Go and re-run this script afterwards."
    exit 1
}
file copy -force $pdc_opcodes $thisdir

set init_opcodes [file join $GODIR pdc_init_bpwp_codes.c]
if {![file exists $init_opcodes]} {
    puts stderr "Could not find file '$init_opcodes', run Go and re-run this script afterwards."
    exit 1
}
file copy -force $init_opcodes $thisdir

set pdc_register_moves [file join $thisdir pdc_register_moves]

puts "Compiling pdc_register_moves.s"
set cmd [list chesscc +a -P $LIBDIR -o $pdc_register_moves.x $pdc_register_moves.s -p $PROC -X darts.ass.conflicts=none]
if {[catch {exec -ignorestderr {*}$cmd} msg]} {
    puts stderr "Could not assemble 'pdc_register_moves.s'."
    puts stderr "Failing command: $cmd"
    exit 1
}

puts "Disassembling pdc_register_moves.x"
set cmd [list chesscc +d -P $LIBDIR -o $pdc_register_moves.dis $pdc_register_moves.x -p $PROC -X darts.dis.noinstr=off -X darts.dis.format=lst -X darts.dis.iradix=bin]
if {[catch {exec -ignorestderr {*}$cmd} msg]} {
    puts stderr "Could not disassemble 'pdc_register_moves.x'."
    puts stderr "Failing command: $cmd"
    exit 1
}

set f [open $pdc_register_moves.h w]

puts $f "
/*
-- File : pdc_register_moves.h
--
-- Contents : Tables with processor specific instruction codes.
--
-- NOTE: this file is generated AUTOMATICALLY from the file pdc_register_moves.s
--       using the commands in ins2c.tcl
*/

#include \"vbit_wrapper.h\"

template <typename map_type>
void get_instr_map(map_type & i) {"

puts "Parsing disassembly pdc_register_moves.dis"
set d [open $pdc_register_moves.dis r]
set dis [read $d]
set ll [split $dis \n]
close $d

set labels [list]

# regular expressions to parse disassembly
set re_bin {"[01]+"(?:\s+"[01]+")*} ; # one or more quoted bin-strings
set re_instr [format {^ \.label \s+ l_(\S+)  \s+ (?:0b|0x|0o)? \d+ \s+ (%s) (.*?) } $re_bin]

# remove quotes and spaces from instruction encodings
proc fmt_instr {m} {
  set b [string map {{"} {} { } {}} $m] ; # remove " and space
  return "VBitWrapper([string length $b],false,\"$b\",2)"
}

# search for all labeled instructions
foreach {m lbl enc asm} [regexp -expanded -line -all -inline $re_instr $dis] {
  puts $f "  i\[\"$lbl\"\] = [fmt_instr $enc]; // $asm"
  lappend labels $lbl
}

if {[llength $labels]} {
  puts "INFO: Found [llength $labels] instructions"
} else {
  puts $f {#error "No instructions identified"}
  puts "ERROR: No instructions identified"
  close $f
  exit
}

# Check if we have register get instructions
set reg_get [lmap lbl $labels {expr {
  [regexp -- {reg_get_(\S+)} $lbl - reg] ? $reg : [continue]
}}]
if {[llength $reg_get]} {
  puts "INFO: Found reg_get codes for [join $reg_get {, }]"
} else {
  puts "WARNING: Found no reg_get codes"
  puts $f {#warning "Found no reg_get codes"}
}

# Check if we have register put instructions
set reg_put [lmap lbl $labels {expr {
  [regexp -- {reg_put_(\S+)} $lbl - reg] ? $reg : [continue]
}}]
if {[llength $reg_put]} {
  puts "INFO: Found reg_put codes for [join $reg_put {, }]"
} else {
  puts "WARNING: Found no reg_put codes"
  puts $f {#warning "Found no reg_put codes"}
}

# Check if we have (a) software break instruction(s)
set swbrk [lmap lbl $labels {expr {
  [regexp -- {swbrk(\d+)} $lbl - ilen] ? $ilen : [continue]
}}]
if {[llength $swbrk]} {
  puts "INFO: Found software break instructions: [join $swbrk]"
} {
  puts $f {#error "No software break instruction identified"}
  puts "ERROR: No software break instruction identified"
}

# Check if we have (an) indirect jump instruction(s)
set jalr [lmap lbl $labels {expr {
  [regexp -- {jalr_(\S+)} $lbl - reg] ? $reg : [continue]
}}]
if {[llength $jalr]} {
  puts "INFO: Found indirect jump instruction for [join $jalr {, }]"
} {
  puts $f {#error "No indirect jump instruction identified"}
  puts "ERROR: No indirect jump instruction identified"
}

puts $f "}";
close $f

puts "Generated pdc_register_moves.h"


set f [open $pdc_opcodes r]
set opc [read $f]
close $f

set re_opc {^ \s* const \s+ int \s+ (\w+ _ INSTR) \s* = \s* ( (?:0x)? [a-zA-Z\d]+ ) \s* ;}

set opcodes [list]
foreach {m name instr} [regexp -expanded -line -all -inline $re_opc $opc] {
  lappend opcodes "{ $instr, \"$name\" }"
}

# optional
set f [open [file join $thisdir pdc_opcodes_dbg.h] w]
puts $f [join $opcodes ",\n"]
close $f
