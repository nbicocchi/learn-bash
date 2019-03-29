#!/bin/bash

# Ho scelto bash...

USAGE="usage: $0 dirname(abs) name(rel)"

if [ $# -ne 2 ]; then
	echo "$USAGE"
	exit 1
fi

case "$1" in
	/*) ;;
	*) echo "$USAGE"
	   exit 2
	   ;;
esac

if [ ! -d "$1" -o ! -x "$1" ]; then
	echo "$USAGE"
	exit 3
fi

case "$2" in
	*/*) echo "$USAGE"
		 exit 4
		 ;;
	*) ;;
esac

export PATH=$(pwd):"$PATH"

echo "phase A..."
for fname in "$1"/*; do
	if [ -d "$fname" -a -x "$fname" ]; then
		testr.sh "$fname" $2 A
	fi
done

echo -n "Continue with phase B (Y/N)? "
read ans
case "$ans" in
	Y|y) ;;
	N|n) exit 0
		 ;;
esac

echo "phase B..."
for fname in "$1"/*; do
	if [ -d "$fname" -a -x "$fname" ]; then
		testr.sh "$fname" $2 B
	fi
done

echo "phase A..."
for fname in "$1"/*; do
	if [ -d "$fname" -a -x "$fname" ]; then
		testr.sh "$fname" $2 A
	fi
done

exit 0



