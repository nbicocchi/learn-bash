#!/bin/bash

USAGE="usage: $0 dirname(abs) filename filename"

# Check arguments
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

if [ ! -d "$1" ] || [ ! -x "$1" ]; then
  echo "$USAGE"
  exit 1
fi

case "$2" in
  */*)  echo "$USAGE"
        exit 1
        ;;
    *)  ;;
esac

case "$3" in
  */*)  echo "$USAGE"
        exit 1
        ;;
    *)  ;;
esac

# Main body
list=$(find "$1" -type d -executable 2>/dev/null)
for item in $list; do
  [ ! -f "$item"/"$2" ] || [ ! -r "$item"/"$2" ] && continue
  [ ! -f "$item"/"$3" ] || [ ! -r "$item"/"$3" ] && continue
  size_1=$(wc -c < "$item"/"$2")
  size_2=$(wc -c < "$item"/"$3")
  echo ["$item": size=$(( size_1 + size_2))] 
done

exit 0
