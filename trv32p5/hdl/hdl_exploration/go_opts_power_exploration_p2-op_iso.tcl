#############################################################################
# Copyright (c) 2021 Synopsys, Inc. This Synopsys processor model
# captures an ASIP Designer Design Technique. The model and all associated
# documentation are proprietary to Synopsys, Inc. and may only be used
# pursuant to the terms and conditions of a written license agreement with
# Synopsys, Inc.  All other use, reproduction, modification, or distribution
# of the Synopsys processor model or the associated  documentation is
# strictly prohibited.
#############################################################################
# ASIP DESIGNER - RTL EXPLORER
# File: go_opts_power_exploration_p2-op_iso.tcl
# Usage:
#   cd trv32p5/hdl/
#   asip_rtl_explorer -i hdl_exploration/go_opts_power_exploration_p2-op_iso.tcl


# The (-c) option can be used to preset current_projet for the session
# So, no need to modify the script to be used for example with trv32p5_vhdl
if { [current_project] == "" } {
  current_project trv32p5_vlog
}

#Part2: Evaluating effect for power savings increasingly
#       enabling operand isolation in registers, muxes and
#       functional unit

# Operand Isolation in registers:

#Go Manual: register_address_from_decoder is set by default
#           this is the normal option to obtain operand
#           isolation in registers (also beneficial for timing)

# Ensure register_address_from_decoder is set and that
# operand isolation for muxes and FUs is zero.
create_variant oi_reg \
  -go_options { register_addresses_from_decoder:1
                operand_isolation_multiplexers:0
                operand_isolation_functional_units:0 }


# Enabling Operand Isolation in Multiplexers

# Go Manual: mentions that multiplexers might lead to the largest
#            power reduction and that operand isolation in FU effect
#            can be neglictable, if the operands are passing
#            through multiplexers. It is recommended to enable
#            it together with extra_enable_bit and
#            default_multiplexer_operations

create_variant oi_reg+mux \
  -go_options { register_addresses_from_decoder:1
                operand_isolation_multiplexers:1
                operand_isolation_functional_units:0
                extra_enable_bit:1
                default_multiplexer_operations:1 }

# Enabling Operand Isolation in Functional Units

# Go Manual: recommends it together with extra_enable_bit
#            and default_primitive operation to prevent
#            possible optimization of the operand isolation
#            logic during synthesis (same as for muxes in
#            previous variant)

create_variant oi_reg+mux+fu \
  -go_options { register_addresses_from_decoder:1
                operand_isolation_multiplexers:1
                operand_isolation_functional_units:1
                extra_enable_bit:1
                default_primitive_operations:1 }

# Beside reducing toggling in operands, now also reducing toggling
# in opcode registers and unit/muxes outputs
create_variant oi_reg+mux+fu_sor1 \
  -no_reference_cfg \
  -include    go_opts.[current_project]_oi_reg+mux+fu.cfg \
  -go_options split_opcode_registers:1

create_variant oi_reg+mux_sor1 \
  -no_reference_cfg \
  -include    go_opts.[current_project]_oi_reg+mux.cfg \
  -go_options split_opcode_registers:1

# Note: these last two adds the Go Option file of previous generated variants,
# which included already the reference/base Go Configurations file,
# then here explicitly excluding it (w/ -no_reference_cfg)

foreach rtl_id [list_variants] {
  build_variant $rtl_id
}

puts "\nRTL Versions Ready! For starting exploration, execute:\n"
puts "cd [current_project]_[lindex [list_variants] 0]/syn_rtla;"
puts "make explore RTL_ID_LIST=\"[list_variants]\" ASIP_LIB_SETUP=..."
puts "\nTo inspect results:"
puts "make view_qor"
puts "\n To clean:"
puts "asip_rtl_explorer -c [current_project] -r all"