#!/bin/bash

USAGE="usage: $0 dirname(abs) Cx(number) Cy(number)"

if [ $# -ne 3 ]; then
  echo "$USAGE"
  exit 1
fi

# Parameters checks
case "$1" in
	/*) ;;
	*) echo "$USAGE"
	   exit 1
	   ;;
esac

if [ ! -d "$1" -o ! -x "$1" ]; then
	echo "$USAGE"
	exit 1
fi

case "$2" in
	[0-9]) ;;
	*) echo "$USAGE"
	   exit 1
	   ;;
esac

case "$2" in
	[0-9]) ;;
	*) echo "$USAGE"
	   exit 1
	   ;;
esac

# Recursive call
export PATH=$(pwd):$PATH
es33r.sh $*

exit 0