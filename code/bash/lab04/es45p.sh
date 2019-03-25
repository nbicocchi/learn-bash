#!/bin/bash

USAGE="usage: $0 dirname(rel) d1(abs) .. dn(abs)"

if [ $# -lt 3 ]; then
  echo "$USAGE"
  exit 1
fi

d="$1"
shift

case "$d" in 
  /*) echo "$USAGE"
      exit 2
      ;;
  *) ;;
esac

for dname in $*; do
  case "$dname" in 
    /*) ;;
    *) echo "$USAGE"
       exit 3
       ;;
  esac

  if [ ! -d "$dname" -o ! -x "$dname" ]; then
    echo "$USAGE"
    exit 4
  fi
done

rm -rf /tmp/flist >/dev/null 2>&1
export PATH=$(pwd):$PATH

for dname in $*; do
  es45r.sh "$dname" "$d"
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


