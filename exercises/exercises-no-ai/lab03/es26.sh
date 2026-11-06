#!/bin/bash

usage() {
  echo "usage: $0 arg"
  exit 1
}

if [ $# -ne 1 ]; then
  usage
fi

case "$1" in
  /*) echo "Absolute filename"
      ;;
  */*) echo "Relative filename"
       ;;
  *) echo "Simple, relative filename"
     ;;
esac

exit 0
