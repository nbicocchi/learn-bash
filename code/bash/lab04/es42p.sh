#!/bin/bash

USAGE="usage: $0 dirname(abs) filename(rel) n(>0)"

if [ $# -ne 3 ]; then
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

expr "$3" + 0 >/dev/null 2>&1
case $? in
  0) ;; # result != 0
  1) ;; # result == 0
  2) echo "$USAGE"; exit 1;; # syntax error, es. K='+'
  3) echo "$USAGE"; exit 1;; # non-numeric argument, es. K='a'
esac

if [ "$3" -le 0 ]; then
  echo "$USAGE"
  exit 1
fi

rm -rf /tmp/flist >/dev/null 2>&1

export PATH=$(pwd):$PATH
es42r.sh $*

count=0
if [ -f "/tmp/flist" ]; then
  count=$(cat /tmp/flist | wc -l)
fi

echo "files found: $count"

exit 0
