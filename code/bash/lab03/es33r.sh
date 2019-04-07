#!/bin/bash

# $1 contains current dir
# $2 contains char Cx
# $3 contains char Cy

cd "$1"

# recursion
for fname in *; do
  if [ -d "$fname" -a -x "$fname" ]; then
    "$0" $(pwd)/"$fname" "$2" "$3"
  fi
done

# process directory
for fname in *; do
	if [ ! -f "$fname" -o ! -r "$fname" ]; then
	  continue
	fi
		
	case "$fname" in
	  *$2*$3*) ;;
	  *$3*$2*) ;;
	  *) continue
	     ;;
	esac
		
	grep -q $2 "$fname"
	if [ $? -ne 0 ]; then
	  continue
	fi
		
	grep -q $3 "$fname"
	if [ $? -ne 0 ]; then
	  continue
	fi
		
	echo $(pwd)
done

exit 0

