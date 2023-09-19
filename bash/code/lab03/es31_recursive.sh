#!/bin/bash

USAGE="usage: $0 dirname(abs)"

# Functions
recurse_dir() {
  # $1 is the directory name
  # $2 is current depth level 

  cd "$1"
    
  # Scan for sub-directories
  for fname in *; do
    if [ -d "$fname" -a -x "$fname" ]; then
      recurse_dir "$fname" $(expr "$2" + 1)
    fi
  done

  # Process current directory
  echo ["$2"] $(pwd) 

  cd ..
}

# Check arguments
if [ $# -ne 1 ]; then
  echo "$USAGE"
  exit 1
fi

case "$1" in
  /*) ;;
  *)  echo "$USAGE"
      exit 1
      ;;
esac

if [ ! -d "$1" -o ! -x "$1" ]; then
  echo "$USAGE"
  exit 1
fi

# Variables
D="$1"
L=0

# Main body
recurse_dir "$D" "$L"

exit 0

