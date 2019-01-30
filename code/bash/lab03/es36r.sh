#!/bin/bash

# $1 contains current dir
# $2 contains the number of lines

cd "$1"

# recursion
for file in *; do
  if [ -d "$file" -a -x "$file" ]; then
    "$0" "$file" "$2"
  fi
done

# process directory
match=N
for fname in *; do
  if [ -f "$fname" -a -r "$fname" ]; then
    lines=$(cat "$fname" | wc -l)
    if [ $lines -eq $2 ]; then
      match=Y
      sort "$fname" > "$fname".sort
    fi
  fi
done
    
if [ "$match" == "Y" ]; then
  echo $(pwd)
fi

exit 0