#!/bin/bash

# $1 contains current dir
# $2 contains dirname (simple)
# $3 contains filesize 

TMPFILE=/tmp/flist
SUMFILE=SOMMA

cd "$1"

# recursion
for file in *; do
  if [ -d "$file" -a -x "$file" ]; then
    "$0" $(pwd)/"$file" "$2" "$3"
  fi
done

# process directory
# check current directory name
if [ $(basename $(pwd)) != "$2" ]; then
  exit 0
fi

# check for files and sizes
rm -rf "$SUMFILE" >/dev/null 2>&1
count=0
for file in *; do
  if [ -f "$file" ]; then
    if [ $(wc -c < "$file") -gt "$3" ]; then
      if [ "$count" -eq 0 ]; then
        echo $(pwd)
      fi 
      count=$(expr "$count" + 1)

      echo $(pwd)/"$file" >> $TMPFILE
      cat "$file" >> "$SUMFILE"
    fi
  fi
done

exit 0