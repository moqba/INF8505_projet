#!/bin/bash

cd $(dirname $(readlink -f ${BASH_SOURCE[0]}))

vcf -fmode dpv -f ../tcl/ffi_vlog.tcl -gui -out_dir ffi