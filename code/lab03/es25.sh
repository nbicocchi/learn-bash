#!/bin/bash

USAGE="usage: $0 arg1 arg2 .. argn"

if [ $# -lt 2 ]; then
  echo "$USAGE"
  exit 1
fi

echo "first arg: $1"

while [ $# -gt 1 ]; do
  shift
done  

echo "last arg: $1"

exit 0
