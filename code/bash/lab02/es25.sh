#!/bin/bash

if [ $# -lt 1 ]; then
  echo "usage: $0 arg1 .. argn"
  exit 1
fi

while [ $# -gt 1 ]; do
  shift
done
  
echo "$1"
exit 0