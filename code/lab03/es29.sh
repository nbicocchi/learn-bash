#!/bin/bash

usage() {
  echo "usage: $0 dirname"
  exit 1
}

# Check the number of parameters
if [ $# -ne 1 ]; then 
  usage
fi

# Check if "$1" is a directory and explorable
if [ ! -d "$1" ] || [ ! -x "$1" ]; then
  usage
fi

# Main body
F=0
D=0
for fname in "$1"/*; do
  if [ -f "$fname" ]; then
    echo [F] "$fname"
    F=$(( F + 1 ))
  fi
  
  if [ -d "$fname" ]; then
    echo [D] "$fname"
    D=$(( D + 1 ))
  fi
done

echo "#files =" "$F"
echo "#directories =" "$D"

exit 0
