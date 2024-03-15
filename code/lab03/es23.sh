#!/bin/bash

usage() {
  echo "usage: $0 arg (readable directory)"
  exit 1
}

if [ $# -ne 1 ]; then
  usage
fi

if [ ! -d "$1" ] || [ ! -r "$1" ]; then
  usage
fi

exit 0
