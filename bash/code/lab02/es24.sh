#!/bin/bash

USAGE="usage: $0 arg1 (writable directory) arg2"

if [ $# -ne 2 ]; then
  echo "$USAGE"
  exit 1
fi

if [ ! -d "$1" ] || [ ! -w "$1" ]; then
  echo "$USAGE"
  exit 1
fi

cd "$1" || exit 1
pwd > "$2"

exit 0

