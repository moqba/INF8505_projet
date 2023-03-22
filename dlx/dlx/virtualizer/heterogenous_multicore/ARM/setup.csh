#!/bin/csh

# setup virtualizer
source /u/ccmaster/releases/vp/images/O-2018.09-SP3/VPProducts/SLS/linux/setup.csh -vauth

# setup arm compiler and license
source /u/ccmaster/SDR/3rdparty/tools/arm/license_setup.csh
setenv PATH /u/ccmaster/SDR/3rdparty/tools/arm/Compiler6/v6.9/linux/bin/:$PATH

# set the offset of shared space between ARM and DLX
setenv SNPS_DLX_SHARED_MEMORY_OFFSET 0x8000000
