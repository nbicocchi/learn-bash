#!/bin/bash

USAGE="usage: $0 dirname(abs) c1 .. cn"

if [ $# -lt 2 ]; then
  echo "$USAGE"
  exit 1
fi

case "$1" in 
  /*) ;;
  *) echo "$USAGE"
     exit 2
     ;;
esac

if [ ! -d "$1" -o ! -x "$1" ]; then
  echo "$USAGE"
  exit 3
fi

export PATH=$(pwd):$PATH
es34r.sh $*

exit 0
