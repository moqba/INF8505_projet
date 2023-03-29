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

source [file join [file dirname [info script]] scr cliargs-build.tcl]

chessmk -r $issprx >& reset.log

file delete -force [file join [file dirname $issprx] export]

log "Done"