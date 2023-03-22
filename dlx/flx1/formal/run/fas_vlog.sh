#!/bin/bash

cd $(dirname $(readlink -f ${BASH_SOURCE[0]}))

vcf -fmode dpv -f ../tcl/fas_vlog.tcl -gui -out_dir fas