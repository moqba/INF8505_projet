#!/bin/bash -ex

# rename

set -ex

# compute paths
script_path=$(readlink -f ${BASH_SOURCE[0]})
script_dir=$(dirname $script_path)
projdir=$(readlink -f ${script_dir}/..)

oldname=$(basename $projdir)
newname=${1?Please specify name}

cd $projdir/

while read -r x y; do
  pat="$x" # default
  if [[ ${y#$x} != ${y} ]] ; then # old name is prefix of new name, e.g. core -> core64
    pat="(?!$y)$x" # match oldname unless newname
  elif [[ ${x#$y} != ${x} ]] ; then # new name is prefix old old name, e.g. core64 -> core
    pat="$x"
  fi

  for lvl in {1..20} ; do
    for fname in $(find . -mindepth $lvl -maxdepth $lvl -name "*${x}*") ; do
      newfname=$(echo $fname | perl -pe "s/$pat/$y/g")
      if [[ "$newfname" != "$fname" ]] ; then
        #git mv -f $fname $newfname
        mv $fname $newfname
      fi
    done
  done

  for fname in $(grep -l $x -R . ) ; do
    perl -pi -e "s/$pat/$y/g" $fname
    # git add -f $fname
  done
done <<____HERE
    trv32p3 $(echo $newname | tr [A-Z] [a-z])
    TRV32P3 $(echo $newname | tr [a-z] [A-Z])
____HERE

#cd ..
#git mv -f $oldname $newname
