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
n=0
list=$(find "$1" -type f -readable -name "$2" 2>/dev/null)
for item in $list; do
  echo "$item"
  rm -rf /tmp/link_"$n"
  ln -s "$item" /tmp/link_"$n"
  n=$(expr "$n" + 1)
done

exit 0
