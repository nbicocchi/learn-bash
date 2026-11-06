#!/bin/bash

usage() {
  echo "usage: $0 dirname(abs)"
  exit 1
}

# Functions
recurse_dir() {
  # $1 is the directory name
  # $2 is current depth level 

  cd "$1" || return
    
  # Scan for sub-directories
  for fname in *; do
    if [ -d "$fname" ] && [ -x "$fname" ]; then
      recurse_dir "$fname" $(( "$2" + 1 ))
    fi
  done

  # Process current directory
  echo ["$2"] "$(pwd)" 

  cd ..
}

# Check arguments
if [ $# -ne 1 ]; then
  usage
fi

case "$1" in
  /*) ;;
  *)  usage
      ;;
esac

if [ ! -d "$1" ] || [ ! -x "$1" ]; then
  usage
fi

# Variables
D="$1"
L=0

# Main body
recurse_dir "$D" "$L"

exit 0

