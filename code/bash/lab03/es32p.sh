#!/bin/bash

if [ $# -ne 2 ]; then
  echo "usage: $0 dir(abs) str"
  exit 1
fi

case "$1" in 
  /*) ;;
  *) echo "usage: $0 dir(abs) str"
     exit 1
    ;;
esac

if [ ! -d "$1" -o ! -x "$1" ]; then
  echo "usage: $0 dir(abs) str"
  exit 1
fi

export PATH=$(pwd):$PATH
es43r.sh $*

exit 0
