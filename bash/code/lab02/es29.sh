#!/bin/bash

USAGE="usage: $0 dirname"

# Check the number of parameters
if [ $# -ne 1 ]; then 
  echo "$USAGE"
  exit 1
fi

# Check if "$1" is a directory and explorable
if [ ! -d "$1" -o ! -x "$1" ]; then
  echo "$USAGE"
  exit 1
fi

# Main body
F=0
D=0
for fname in "$1"/*; do
  if [ -f "$fname" ]; then
    echo [F] "$fname"
    F=$(expr $F + 1)
  fi
  
  if [ -d "$fname" ]; then
    echo [D] "$fname"
    D=$(expr $D + 1)
  fi
done

echo "#files =" $F
echo "#directories =" $D

exit 0
