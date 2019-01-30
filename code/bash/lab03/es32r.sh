#!/bin/bash

# $1 contains current dir
# $2 contains filename

cd "$1"

# recursion
for file in *; do
  if [ -d "$file" -a -x "$file" ]; then
    "$0" "$file" "$2"
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
f1l=$(cat "$2".1 | wc -l)
f1c=$(cat "$2".1 | wc -c)

f2l=$(cat "$2".2 | wc -l)
f2c=$(cat "$2".2 | wc -c)

if [ "$f1l" -eq "$f2l" -a "$f1c" -eq "$f2c" ]; then
  echo $(pwd)
fi

exit 0
