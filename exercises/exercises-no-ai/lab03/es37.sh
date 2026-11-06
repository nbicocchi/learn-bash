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
n=0
list=$(find "$1" -type f -readable -name "$2" 2>/dev/null)
for src in $list; do
  dst=/tmp/link_"$n"
  echo "$src" "-->" "$dst" 
  rm -rf "$dst"
  ln -s "$src" "$dst"
  n=$(( n + 1 ))
done

exit 0
