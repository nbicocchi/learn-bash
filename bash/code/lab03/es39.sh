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

case "$3" in
  */*)  echo "$USAGE"
        exit 1
        ;;
    *)  ;;
esac

# Main body
count_f1=$(find "$1" -type f -readable -name "$2" | wc -l 2>/dev/null)
count_f2=$(find "$1" -type f -readable -name "$3" | wc -l 2>/dev/null)

if [ "$count_f1" -gt 0 -a "$count_f2" -gt 0 ]; then
  echo "Test passed for" "$1" 
  echo "$2": "$count_f1"
  echo "$3": "$count_f2"
fi

exit 0
