#!/bin/bash

USAGE="usage: $0 filename d1(abs) .. dn(abs)"

if [ $# -lt 3 ]; then
  echo "$USAGE"
  exit 1
fi

fname="$1"
shift

for dname in $*; do
  case "$dname" in 
    /*) ;;
    *) echo "$USAGE"
       exit 2
       ;;
  esac

  if [ ! -d "$dname" -o ! -x "$dname" ]; then
    echo "$USAGE"
    exit 3
  fi
done


rm -rf /tmp/flist >/dev/null 2>&1

export PATH=$(pwd):$PATH
for dname in $*; do
  es47r.sh "$dname" "$fname"
done
  
if [ -f /tmp/flist ]; then
  echo "files found: $(wc -l < /tmp/flist)"
fi

for line in $(cat /tmp/flist); do
  fname=$(echo "$line" | cut -d ";" -f 1)
  nlines=$(echo "$line" | cut -d ";" -f 2)
  if [ $nlines -gt 5 ]; then
    echo "$fname" "[lines="$nlines"]" "[last line]"
    tail -n 1 "$fname"
  fi
done

exit 0