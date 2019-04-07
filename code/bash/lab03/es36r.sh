#!/bin/bash

# $1 contains current dir
# $2 contains the number of lines

cd "$1"

# recursion
for file in *; do
  if [ -d "$file" -a -x "$file" ]; then
    "$0" $(pwd)/"$file" "$2"
  fi
done

# process directory
match=N
for fname in *; do
  if [ ! -f "$fname" -o ! -r "$fname" ]; then
    continue
  fi
    
  if [ $(wc -l < "$fname") -eq $2 ]; then
    if [ "$match" == "N" ]; then
      echo $(pwd)
      match=Y
    fi
    sort "$fname" > "$fname".sort
  fi
done
    
exit 0

