#!/bin/bash

usage() {
  echo "usage: $0 dirname(abs) filename filename"
  exit 1
}

# Check arguments
if [ $# -ne 3 ]; then
  usage
fi

case "$1" in 
  /*) ;;
  *) usage
     ;;
esac

if [ ! -d "$1" ] || [ ! -x "$1" ]; then
  usage
fi

case "$2" in
  */*) usage
       ;;
    *) ;;
esac

case "$3" in
  */*) usage
       ;;
    *) ;;
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
