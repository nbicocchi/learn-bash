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
  if [ ! -f "$fname" -o ! -r "$fname" ]; then
    continue
  fi
    
  if [ $(wc -l < "$fname") -eq $2 ]; then
    echo $(pwd)
    match=Y
    break
  fi
done
    
if [ "$match" == "Y" ]; then
  for fname in *; do
    if [ ! -f "$fname" -o ! -r "$fname" ]; then
      continue
    fi
    
    if [ $(wc -l < "$fname") -eq $2 ]; then
      sort "$fname" > "$fname".sort
    fi
  done
fi

exit 0

