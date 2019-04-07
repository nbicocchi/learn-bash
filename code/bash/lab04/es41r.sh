#!/bin/bash

# entering folder
cd "$1"

# recursion
for fname in *; do
	if [ -d "$fname" -a -x "$fname" ]; then
		"$0" $(pwd)/"$fname" "$2" "$3"
	fi
done

# processsing dir (phase A)
if [ "$3" == "A" ]; then
	if [ -d "$2" ]; then
		echo $(pwd)
	fi
fi

# processsing dir (phase B)
if [ "$3" == "B" ]; then
	if [ ! -d "$2" ]; then
		mkdir "$2"
	fi
fi

exit 0
