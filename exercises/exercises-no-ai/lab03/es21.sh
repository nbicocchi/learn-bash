#!/bin/bash

usage() {
	echo "usage: $0 filename permissions"
	exit 1
}

if [ $# -ne 2 ]; then
	usage
fi

if [ -f "$1" ]; then
	usage
fi

touch "$1"
chmod "$2" "$1"

exit 0

