#!/bin/bash

# $1 contains current dir
# $2 contains filename

FULLLIST=/tmp/flist

cd "$1"

# recursion
for file in *; do
  if [ -d "$file" -a -x "$file" ]; then
    "$0" $(pwd)/"$file" "$2"
  fi
done

# process directory
if [ -f "$2" -a -r "$2" ]; then
  lines=$(wc -l < "$2" | sed 's/ //g')
  if [ $lines -ge 5 ]; then
  	echo "$(pwd)/"$2";$lines" >> "$FULLLIST"
  fi
fi 

exit 0