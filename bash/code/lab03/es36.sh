#!/bin/bash

USAGE="usage: $0 dirname(abs) filename"

# Check arguments
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
  */*)  echo "$USAGE"
        exit 1
        ;;
    *)  ;;
esac

# Main body
list=$(find "$1" -type f -readable -name "$2" 2>/dev/null)
for item in $list; do
  nlines=$(cat "$item" | wc -l)
  echo "$item"
  
  echo -n "1: "
  cat "$item" | head -n 1

  echo -n "2: "
  cat "$item" | head -n 2 | tail -n 1

  echo -n "$(expr "$nlines" - 1): "
  cat "$item" | tail -n 2 | head -n 1

  echo -n "$nlines: "
  cat "$item" | tail -n 1
done

exit 0
