#!/bin/bash

USAGE="usage: $0 filename permissions"

if [ $# -ne 2 ]; then
	echo "$USAGE"
	exit 1
fi

if [ -f "$1" ]; then
	echo "$USAGE"
	exit 1
fi

touch "$1"
chmod "$2" "$1"

exit 0

