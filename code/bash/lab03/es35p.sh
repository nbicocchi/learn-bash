#!/bin/bash

USAGE="usage: $0 dirname(abs) n(>0)"

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

expr "$2" + 0 > /dev/null 2>&1
case $? in
  0) ;; # result != 0
  1) ;; # result == 0
  2) echo "$USAGE"; exit 1;; # syntax error, es. K='+'
  3) echo "$USAGE"; exit 1;; # non-numeric argument, es. K='a'
esac

if [ "$2" -le 0 ]; then
  echo "$USAGE"
  exit 1
fi

export PATH=$(pwd):$PATH
es35r.sh $*

exit 0