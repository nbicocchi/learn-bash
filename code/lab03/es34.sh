#!/bin/bash

usage() {
  echo "usage: $0 dirname(abs) n"
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
  ''|*[!0-9]*) usage
    ;;
  *) 
    ;;
esac

# Main body
list=$(find "$1" -type d -executable 2>/dev/null)
for item in $list; do
  nfiles=$(find "$item" -maxdepth 1 -type f | wc -l 2>/dev/null)
  if [ "$nfiles" -ge 1 ] && [ "$nfiles" -le "$2" ]; then
    echo "$item" ["$nfiles" files]
  fi
done

exit 0