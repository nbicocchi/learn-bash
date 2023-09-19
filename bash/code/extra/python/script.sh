#!/bin/bash

if [ $# -lt 1 ]; then
	echo "usage: $0 f1 .. fn"
    exit 1
fi

l=0
for fname in $*; do
	l=$(wc -l "$fname" | cut -d ' ' -f 1)
	echo "$fname": "$l"
done

exit 0

