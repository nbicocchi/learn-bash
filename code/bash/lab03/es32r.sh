#!/bin/bash

# $1 contains current dir
# $2 contains filename

cd "$1"

# recursion
for file in *; do
  if [ -d "$file" -a -x "$file" ]; then
    "$0" $(pwd)/"$file" "$2"
  fi
done

# directory processing
# check names
if [ ! -f "$2".1 -o ! -r "$2".1 ]; then
  exit 0
fi

if [ ! -f "$2".2 -o ! -r "$2".2 ]; then
  exit 0
fi

# check lines and chars
f1l=$(wc -l < "$2".1)
f1c=$(wc -c < "$2".1)

f2l=$(wc -l < "$2".2)
f2c=$(wc -c < "$2".2)

if [ "$f1l" -eq "$f2l" -a "$f1c" -eq "$f2c" ]; then
  echo $(pwd)
fi

exit 0
