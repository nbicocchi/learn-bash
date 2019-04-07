#!/bin/bash

# $1 contains current dir
# $2 contains filename

PARTLIST=/tmp/plist
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
  echo $(pwd) >> "$PARTLIST"
  echo $(pwd) >> "$FULLLIST"
  sort "$2" > sorted
fi 

exit 0