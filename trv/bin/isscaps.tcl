#
# Copyright (c) 2019-2020 Synopsys, Inc. This Synopsys processor model
# captures an ASIP Designer Design Technique. The model and all associated
# documentation are proprietary to Synopsys, Inc. and may only be used
# pursuant to the terms and conditions of a written license agreement with
# Synopsys, Inc.  All other use, reproduction, modification, or distribution
# of the Synopsys processor model or the associated  documentation is
# strictly prohibited.
#

proc has_file_output {iss name} {
    set loptions [$iss info issoptions]
    set options [tclutils::list2dict $::iss::iss_option_keys $loptions]
    set ls [lindex [$iss info storage $name] 0]
    set sd [tclutils::list2dict $::iss::storinfo_keys $ls]
    if {([dict get $options file_output_type] eq "all" && [dict get $sd storage_type] in {register memory}) || \
        ([dict get $options file_output_type] eq "all" && [dict get $sd storage_type] in {transitory} && [dict get $sd is_port]) || \
        ([dict get $options file_output_type] eq "selected" && [dict get $storinfo([dict get $sd top_alias]) storage_name] in [dict get $options file_output_storages])} {
        return true
    }
    return false
}

## Example usage
#iss::create tmicro p
#puts [has_file_output p DM]
#puts [has_file_output p dm_write]
#p close
#exit
