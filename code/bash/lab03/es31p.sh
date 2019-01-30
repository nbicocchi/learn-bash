#!/bin/bash

USAGE="usage: $0 dirname(abs)"

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

echo "0" > /tmp/maxlevel
export PATH=$(pwd):$PATH
es31r.sh "$1" 0
echo "max depth: $(cat /tmp/maxlevel)"

exit 0
