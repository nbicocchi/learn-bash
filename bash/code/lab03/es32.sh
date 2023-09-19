#!/bin/bash

USAGE="usage: $0 dir(abs) str n1 n2"

# Check arguments
if [ $# -ne 4 ]; then
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

expr "$3" + 0 1>/dev/null 2>&1
if [ $? -gt 1 -o "$3" -le 0 ]; then
  echo "$USAGE"; 
  exit 1
fi

expr "$4" + 0 1>/dev/null 2>&1
if [ $? -gt 1 -o "$4" -lt 0 ]; then
  echo "$USAGE"; 
  exit 1
fi

# Main body
list=$(find "$1" -type f -name "$2" -readable 2>/dev/null)
for item in $list; do
  lines=$(cat "$item" | wc -l)
  if [ "$lines" -ge "$3" -a "$lines" -le "$4" ]; then
    echo "$item" ["$lines" lines]
  fi
done

exit 0
