#!/bin/csh

# setup virtualizer
source /u/ccmaster/releases/vp/images/O-2018.09-SP3/VPProducts/SLS/linux/setup.csh -vauth

# setup arc nsim and metware debugger
module load arcnsim mwdt
setenv NSIM_HOME $NSIM_HOME/../nSIM_64

# install arc PSP (to be done only once). Set ARC_PSP_INSTALL in the arc_dlx_platform.tcl script to <vs_install_dir>
## cd $NSIM_HOME/systemc/virtualizer_studio
## vssh -s -d <vs_install_dir> install.py

# set the offset of shared space between ARC and DLX
setenv SNPS_DLX_SHARED_MEMORY_OFFSET 0x90000000
