#!/bin/bash

usage() {
  echo "usage: $0 dir(abs) str n1 n2"
  exit 1
}

# Check arguments
if [ $# -ne 4 ]; then
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

case "$3" in
  ''|*[!0-9]*) usage
    ;;
  *) 
    ;;
esac

case "$4" in
  ''|*[!0-9]*)
    usage
    ;;
  *) 
    ;;
esac

# Main body
list=$(find "$1" -type f -name "$2" -readable 2>/dev/null)
for item in $list; do
  lines=$(wc -l < "$item")
  if [ "$lines" -ge "$3" ] && [ "$lines" -le "$4" ]; then
    echo "$item" ["$lines" lines]
  fi
done

exit 0
