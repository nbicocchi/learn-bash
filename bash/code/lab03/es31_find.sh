#!/bin/bash

USAGE="usage: $0 dirname(abs)"

# Check arguments
if [ $# -ne 1 ]; then
  echo "$USAGE"
  exit 1
fi

case "$1" in
  /*) ;;
  *)  echo "$USAGE"
      exit 1
      ;;
esac

if [ ! -d "$1" -o ! -x "$1" ]; then
  echo "$USAGE"
  exit 1
fi

# Main body
find "$1" -type d -printf "[%d] %p\n"

exit 0
