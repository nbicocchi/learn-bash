#!/bin/bash

if [ $# -ne 2 ]; then
  echo "usage: $0 arg1 arg2"
  exit 1
fi

if [ ! -d "$1" -o ! -w "$1" ]; then
  echo "usage: $0 arg1 (writable directory) arg2"
  exit 1
fi

cd "$1"
pwd > "$2"

exit 0
