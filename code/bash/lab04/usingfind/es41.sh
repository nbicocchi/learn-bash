#!/bin/bash

source oslib.sh

process_phase_A() {
  IFS=$'\n'
  for dirname in $DIRLIST; do
    if [ -d "$dirname"/"$D" ]; then
      echo "$dirname"
    fi
  done
  return 0
}

process_phase_B() {
  IFS=$'\n'
  for dirname in $DIRLIST; do
    if [ ! -d "$dirname"/"$D" ]; then
      mkdir "$dirname"/"$D"
    fi
  done
  return 0
}

# Assign variable to make them available inside functions
G="$1"
D="$2"

# Check arguments
check_argc $# 2 
check_dir_absolute "$G"
check_dir_explorable "$G"
check_dir_relative_simple "$D"

# Recursive exploration (on Linux use find, on OSX use gfind)
# The option ! -path "$G" excludes the root of the search
DIRLIST=$(gfind "$G" ! -path "$G" -type d -printf '%p\n' 2>/dev/null | grep -v "Permission denied")

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
