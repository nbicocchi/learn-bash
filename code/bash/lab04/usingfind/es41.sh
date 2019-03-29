#!/bin/bash

source oslib.sh

process_phase_A() {
    IFS=$'\n'
    for dirname in $DIRLIST; do
	   if [ -d "$dirname"/"$2" ]; then
		  echo "$dirname"
	   fi
    done
    return 0
}

process_phase_B() {
    IFS=$'\n'
    for dirname in $DIRLIST; do
       if [ ! -d "$dirname"/"$2" ]; then
          mkdir "$D"
       fi
    done
    return 0
}


# Check arguments
check_argc $# 2 
check_dir_absolute "$1"
check_dir_explorable "$1"
check_dir_relative_simple "$2"

# Recursive exploration
DIRLIST=$(gfind "$G" ! -path "$1" -type d -printf '%p\n' 2>/dev/null | grep -v "Permission denied")

echo "Phase A... "
process_phase_A

echo -n "Execute Phase B (Y/N)? "
read answer
case "$answer" in
	Y|y) ;;
	N|n) exit 0;;
esac

echo "Phase B... "
process_phase_B

echo "Phase A... "
process_phase_A

exit 0
