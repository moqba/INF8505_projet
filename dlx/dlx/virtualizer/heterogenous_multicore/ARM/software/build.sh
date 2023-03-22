#!/bin/bash -f
#############################################################################
# Copyright 1996-2021 Synopsys, Inc.                                        #
#                                                                           #
# This Synopsys software and all associated documentation are proprietary   #
# to Synopsys, Inc. and may only be used pursuant to the terms and          #
# conditions of a written license agreement with Synopsys, Inc.             #
# All other use, reproduction, modification, or distribution of the         #
# Synopsys software or the associated documentation is strictly prohibited. #
#############################################################################

# This script requires that the ARM's Compiler6 tools can be found in the PATH.
# After building update the /ImageInfo/cpuX/initial_image parameters to point to the rebuilt AXF files.

# Configure the build commands in the second part of this script
src_dir=$(dirname $0)
work_dir=$(pwd)
cflags="--target=arm-arm-none-eabi -mcpu=cortex-a5 -mfpu=none"
aflags="--cpu=Cortex-A5.no_neon.no_vfp"
lflags="--cpu=Cortex-A5.no_neon.no_vfp"
ppdefs="-DMSC_CLOCK -DUSE_SEMIHOSTING_OUTPUT"
bootsrc="$SNPS_VP_HOME/../../IP/ARM_CORTEX_A5_TLM2_LT_PSP/examples/dhrystone_sw/boot_armv7a.spp"

# Build the images, as configured in the first part of the script
armclang -o ${work_dir}/prod.o -c -O3 ${cflags} ${ppdefs} ${src_dir}/prod.c
armclang -E -x assembler-with-cpp ${cflags} ${bootsrc} > ${work_dir}/boot_armv7a.s
armasm -o ${work_dir}/boot_armv7a.o ${aflags} ${work_dir}/boot_armv7a.s
armlink -o ${work_dir}/prod.axf ${lflags} --entry=common_entry_point --scatter ${src_dir}/prod.scat \
            ${work_dir}/boot_armv7a.o ${work_dir}/prod.o

