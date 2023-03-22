#!/bin/bash

if ! (return 0 2>/dev/null)
then  # not sourced
  echo "Script needs to be sourced"
else

  # Define the 'module' function in the current bash shell
  unset MODULEPATH
  export MODULESHOME=/global/etc/modules/default
  export MODULES_RC=/global/etc/modules/modulesrc
  export MODULES_PLATFORM=`$MODULESHOME/bin/platform`
  . $MODULESHOME/init/bash

  module load vcstatic
  export LD_LIBRARY_PATH=$(echo $LD_LIBRARY_PATH | sed -r -e 's#/usr/local/lib##g' -e 's#/usr/lib##g' -e 's#::##g' -e 's#:$##g' -e 's#^:##g')

  QSC=R

  export PATH=/depot/qsc/QSC${QSC}/bin:/depot/qsc/QSC${QSC}/binutils/bin:/depot/qsc/QSC${QSC}/GCC/bin:$PATH
  export LD_LIBRARY_PATH=/depot/qsc/QSC${QSC}/GCC/lib64:/depot/qsc/QSC${QSC}/GCC/lib:/depot/qsc/QSC${QSC}/binutils/lib:$LD_LIBRARY_PATH

fi

