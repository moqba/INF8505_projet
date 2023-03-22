#
# Copyright (c) 2019-2021 Synopsys, Inc. This processor model and the associated
# documentation are proprietary to Synopsys, Inc.  This model may only be
# used in accordance with the terms and conditions of a written license
# agreement with Synopsys, Inc.  All other use, reproduction, or distribution
# of this model are strictly prohibited.
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
#iss::create flx p
#puts [has_file_output p DM]
#puts [has_file_output p dm_write]
#p close
#exit
