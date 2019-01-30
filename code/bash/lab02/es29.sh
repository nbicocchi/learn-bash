#!/bin/bash

if [ $# -ne 1 ]; then 
  echo "usage: $0 dirname"
  exit 1
fi

if [ ! -d "$1" -o ! -x "$1" ]; then
  echo "usage: $0 dirname"
  exit 1
fi

F=0
D=0
for fname in "$1"/*; do
  if [ "$fname" == "*" ]; then
    # the directory is empty
    break
  fi
  
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