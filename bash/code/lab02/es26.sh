#!/bin/bash

USAGE="usage: $0 arg"

if [ $# -ne 1 ]; then
  echo "$USAGE"
  exit 1
fi

case "$1" in
  /*) echo "Absolute filename"
      ;;
  */*) echo "Relative filename"
       ;;
  *) echo "Simple, relative filename"
     ;;
esac

exit 0
