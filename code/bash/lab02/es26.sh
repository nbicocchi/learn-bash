#!/bin/bash

if [ $# -ne 1 ]; then
  echo "usage: $0 arg"
  exit 1
fi

case "$1" in
  /*) echo "Absolute filename"
      exit 0
      ;;
  */*) echo "Relative filename"
       exit 0
       ;;
  *) echo "Simple, relative filename"
     exit 0
     ;;
esac

  