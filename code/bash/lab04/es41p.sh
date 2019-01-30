#!/bin/bash

USAGE="usage: $0 dirname(abs) dirname(rel)"

if [ $# -ne 2 ]; then
  echo "$USAGE"
  exit 1
fi

case "$1" in 
  /*) ;;
  *) echo "$USAGE"
     exit 1
     ;;
esac

if [ ! -d "$1" -o ! -x "$1" ]; then
  echo "$USAGE"
  exit 1
fi

case "$2" in
  */*) echo "$USAGE"
       exit 1
       ;;
  *) ;;
esac

export PATH=$(pwd):$PATH
es41r.sh $* A

echo "Create missing folders (y/n)? "
read ans

if [ "$ans" == "y" ]; then
  es41r.sh $* B
  es41r.sh $* A
fi

exit 0
