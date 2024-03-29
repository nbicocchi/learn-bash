#!/bin/bash

usage() {
  echo "usage: $0 dirname(abs) filename"
  exit 1
}

# Check arguments
if [ $# -ne 2 ]; then
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
  */*)  usage
        ;;
    *)  ;;
esac

# Main body
list=$(find "$1" -type f -readable -name "$2" 2>/dev/null)
for item in $list; do
  nlines=$(wc -l < "$item")
  echo "$item"
  
  echo -n "1: "
  head -n 1 < "$item"

  echo -n "2: "
  head -n 2 < "$item" | tail -n 1

  echo -n "$(( nlines - 1 )): "
  tail -n 2 < "$item" | head -n 1

  echo -n "$nlines: "
  tail -n 1 < "$item"
done

exit 0
