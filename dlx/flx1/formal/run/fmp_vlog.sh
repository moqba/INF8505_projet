#!/bin/bash

cd $(dirname $(readlink -f ${BASH_SOURCE[0]}))

vcf -fmode dpv -f ../tcl/fmp_vlog.tcl -gui -out_dir fmp