#!/bin/bash

USAGE="usage: $0 arg1 (writable directory) arg2"

if [ $# -ne 2 ]; then
  echo "$USAGE"
  exit 1
fi

if [ ! -d "$1" -o ! -w "$1" ]; then
  echo "$USAGE"
  exit 1
fi

cd "$1"
echo $(pwd) > "$2"

exit 0

