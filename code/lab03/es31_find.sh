#!/bin/bash

usage() {
  echo "usage: $0 dirname(abs)"
  exit 1
}

# Check arguments
if [ $# -ne 1 ]; then
  usage
fi

case "$1" in
  /*) ;;
  *)  usage
      ;;
esac

if [ ! -d "$1" ] || [ ! -x "$1" ]; then
  usage
fi

# Main body
find "$1" -type d -printf "[%d] %p\n"

exit 0
