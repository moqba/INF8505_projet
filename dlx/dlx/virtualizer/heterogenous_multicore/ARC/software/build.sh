#!/bin/sh -f

TCF_FILE=$METAWARE_ROOT/arc/tcf/hs48_full.tcf
ccac -g -Os -tcf=$TCF_FILE -o prod.elf prod.c

