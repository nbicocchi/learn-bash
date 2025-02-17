#!/bin/bash

usage() {
  echo "usage: $0 arg1 (writable directory) arg2"
  exit 1
}

if [ $# -ne 2 ]; then
  usage
fi

if [ ! -d "$1" ] || [ ! -w "$1" ]; then
  usage
fi

cd "$1" || exit 1
pwd > "$2"

exit 0

