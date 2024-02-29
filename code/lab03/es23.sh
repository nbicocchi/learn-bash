#!/bin/bash

USAGE="usage: $0 arg (readable directory)"

if [ $# -ne 1 ]; then
  echo "$USAGE"
  exit 1
fi

if [ ! -d "$1" ] || [ ! -r "$1" ]; then
  echo "$USAGE"
  exit 1
fi

exit 0
