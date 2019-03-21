#!/bin/bash

# $1 contains current dir
# $2 .. $n contains chars

cd "$1"
shift

# recursion
for file in *; do
  if [ -d "$file" -a -x "$file" ]; then
    "$0" "$file" "$*"
  fi
done

# process directory
for fname in *; do
  if [ ! -f "$fname" -o ! -r "$fname" ]; then
    continue
  fi
    
  # check size
  size=$(cat "$fname" | wc -c)
  if [ $(expr $size % 2) -ne 0 ]; then
    continue
  fi
        	
  # check content
  missing=N
  for c in $*; do
    grep $c "$fname" >/dev/null 2>&1
    if [ $? -ne 0 ]; then
      missing=Y
      break
    fi	
  done
  
  if [ "$missing" == "Y" ]; then
    continue
  fi
        	
  echo $(pwd)/"$fname"
done

exit 0