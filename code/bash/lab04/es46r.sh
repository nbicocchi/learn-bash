#!/bin/bash

# $1 contains current dir
# $2 contains a number

TMPFILE=/tmp/flist

cd "$1"

# recursion
for file in *; do
  if [ -d "$file" -a -x "$file" ]; then
    "$0" $(pwd)/"$file" "$2"
  fi
done

# process directory
found=N
for fname in *; do
  lines=$(cat "$fname" | wc -l | tr -d " ")
  if [ "$lines" -eq "$2" ]; then
    found=Y
    break
  fi
done

if [ "$found" == "N" ]; then
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