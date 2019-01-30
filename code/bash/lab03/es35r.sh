#!/bin/bash

# $1 contains current dir
# $2 contains max nfile

cd "$1"

# recursion
for file in *; do
  if [ -d "$file" -a -x "$file" ]; then
    "$0" "$file" "$2"
  fi
done

# process directory
file_n=0
file_last=""
for fname in *; do
  if [ -f "$fname" ]; then
    file_n=$(expr $file_n + 1)
    file_last="$fname"
  fi
done

if [ $file_n -ge 1 -a $file_n -le $2 ]; then
  echo $(pwd) "$file_last"
fi

exit 0

