#!/bin/bash

# $1 contains current dir

TMPFILE=/tmp/flist

cd "$1"

# recursion
for file in *; do
  if [ -d "$file" -a -x "$file" ]; then
    "$0" $(pwd)/"$file"
  fi
done

# directory processing
echo "#############################################"
echo "absolute current path -> " $(pwd)
echo "relative current path -> " $(basename $(pwd))

# only for global aggregates
echo "absolute current path -> " $(pwd) >> $TMPFILE

for file in *; do
  if [ -f "$file" ]; then
    echo "[F] " "$file" "l=" $(wc -l < "$file") "c=" $(wc -c < "$file") 
  fi
done

for file in *; do
  if [ -d "$file" ]; then
    echo "[D] " "$file"
  fi
done

exit 0