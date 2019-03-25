#!/bin/bash

USAGE="usage: $0 n(>0) d1(abs) .. dn(abs)"

if [ $# -lt 3 ]; then
  echo "$USAGE"
  exit 1
fi

n="$1"
shift

expr "$n" + 0 >/dev/null 2>&1
case $? in
  [0-1]) ;; 
  *) echo "$USAGE" 
     exit 2
     ;; 
esac

if [ "$n" -le 0 ]; then
  echo "$USAGE"
  exit 3
fi

for dname in $*; do
  case "$dname" in 
    /*) ;;
    *) echo "$USAGE"
       exit 4
       ;;
  esac

  if [ ! -d "$dname" -o ! -x "$dname" ]; then
    echo "$USAGE"
    exit 5
  fi
done

rm -rf /tmp/flist >/dev/null 2>&1
export PATH=$(pwd):$PATH

for dname in $*; do
  es46r.sh "$dname" "$n"
done

echo "files created: $(wc -l < /tmp/flist)"
for fname in $(cat /tmp/flist); do
  case "$fname" in 
    *noline) content="empty"
             ;;
    *) content=$(cat "$fname")
       ;;
  esac
  echo "$fname" ":" "$content"
done

exit 0


