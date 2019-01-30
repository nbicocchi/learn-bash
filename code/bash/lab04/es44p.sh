#!/bin/bash

USAGE="usage: $0 filename d1(abs) .. dn(abs)"

if [ $# -lt 2 ]; then
  echo "$USAGE"
  exit 1
fi

fname="$1"
shift

for dname in $*; do
  case "$dname" in 
    /*) ;;
    *) echo "$USAGE"
       exit 1
       ;;
  esac

  if [ ! -d "$dname" -o ! -x "$dname" ]; then
    echo "$USAGE"
    exit 1
  fi
done


rm -rf /tmp/flist >/dev/null 2>&1

export PATH=$(pwd):$PATH
for dname in $*; do
  rm -rf /tmp/plist >/dev/null 2>&1
  es44r.sh "$dname" "$fname"
  
  n=0
  if [ -f /tmp/plist ]; then
    n=$(cat /tmp/plist | wc -l)
  fi
  echo "[""$dname""]: $n"
done 

n=0
if [ -f /tmp/flist ]; then
  n=$(cat /tmp/flist | wc -l)
fi
echo "[full search]: $n"

exit 0