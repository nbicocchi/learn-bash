#!/bin/bash

usage() {
  echo "usage: $0 arg1 arg2 .. argn"
  exit 1
}

if [ $# -lt 2 ]; then
  usage
fi

echo "first arg: $1"

while [ $# -gt 1 ]; do
  shift
done  

echo "last arg: $1"

exit 0
