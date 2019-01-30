#!/bin/bash

if [ $# -ne 1 ]; then
  echo "usage: $0 arg"
  exit 1
fi

if [ ! -d "$1" -o ! -r "$1" ]; then
  echo "usage: $0 arg (readable directory)"
  exit 1
fi

exit 0
