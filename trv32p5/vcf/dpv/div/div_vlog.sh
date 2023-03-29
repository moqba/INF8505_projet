#!/usr/bin/env bash

cd $(dirname ${BASH_SOURCE[0]})

vcf -fmode dpv -f div_vlog.tcl -gui -out_dir div
