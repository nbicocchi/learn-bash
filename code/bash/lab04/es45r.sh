#!/bin/bash

# $1 contains current dir
# $2 contains dirname

TMPFILE=/tmp/flist

cd "$1"

# recursion
for file in *; do
  if [ -d "$file" -a -x "$file" ]; then
    "$0" "$file" "$2"
  fi
done

# process directory
if [ $(basename $(pwd)) != "$2" ]; then
  exit 0
fi

for fname in *; do
  if [ -f "$fname" -a -r "$fname" ]; then
    
    lines=$(cat "$fname" | wc -l | tr -d " ")
    if [ $lines -ge 3 ]; then
    	line=$(tail -n 3 "$fname" | head -n 1)
    	echo "$line" > "$fname".line
    	echo $(pwd)/"$fname.line" >> "$TMPFILE"
    else
    	echo "" > "$fname".noline
    	echo $(pwd)/"$fname.noline" >> "$TMPFILE"
    fi
  fi
done

exit 0