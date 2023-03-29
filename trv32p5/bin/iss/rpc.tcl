#
# Copyright (c) 2019-2021 Synopsys, Inc. This Synopsys processor model
# captures an ASIP Designer Design Technique. The model and all associated
# documentation are proprietary to Synopsys, Inc. and may only be used
# pursuant to the terms and conditions of a written license agreement with
# Synopsys, Inc.  All other use, reproduction, modification, or distribution
# of the Synopsys processor model or the associated  documentation is
# strictly prohibited.
#
# Helper functions for ISS RPC interface
#
namespace eval issrpc {
  variable skt_iss
  namespace export connect disconnect execute

  proc encode {s} {
    return [string map {\n %NEWLINE% \r %CARRIGERETURN% \{ %LBRACE% \} %RBRACE%} $s]
  }

  proc decode {s} {
    set rt [string index $s 0]
    set s [string map { %NEWLINE% \n %CARRIGERETURN% \r %LBRACE% \{ %RBRACE% \} } [string range $s 1 end]]
    return [list $rt $s]
  }

  proc execute {args} {
    # Write command on the socket
    set cmd [encode [join $args]]
    #puts "ISS cmd: $cmd"
    puts $::issrpc::skt_iss $cmd
    # Read return value
    lassign [decode [gets $::issrpc::skt_iss]] err value
    #puts "ISS rsp: err='$err' value='$value'"
    if {$err eq ""} {
      return ""
    }
    if {!$err} {
      error $value
    }
    return $value
  }

  proc disconnect {} {
    close $::issrpc::skt_iss
    puts "ISSRPC: disconnect"
  }

  proc connect {} {
    if {[info exists ::env(ISS_RPC_SERVER_PORT_FILE)] && [string length $::env(ISS_RPC_SERVER_PORT_FILE)]} {
      set cf [open $::env(ISS_RPC_SERVER_PORT_FILE) r]
    } else {
      set cf [open "ISS_RPC_SERVER_PORT" r]
    }
    gets $cf sc_server_port
    close $cf

    puts "ISSRPC: connect to port $sc_server_port"

    set ::issrpc::skt_iss [socket localhost $sc_server_port]
    fconfigure $::issrpc::skt_iss -buffering line
  }
}
