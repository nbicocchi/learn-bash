#!/bin/bash

USAGE="usage: $0 dirname(abs) dirname(rel)"

if [ $# -ne 2 ]; then
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

case "$2" in
  */*) echo "$USAGE"
       exit 4
       ;;
  *) ;;
esac

rm -rf /tmp/flist >/dev/null 2>&1

export PATH=$(pwd):$PATH
es43r.sh $*

count=0
if [ -f "/tmp/flist" ]; then
  count=$(wc -l < /tmp/flist)
fi

echo "dirs created: $(expr 2 \* $count)"

exit 0
