#!/bin/bash

# $1 contains current dir
# $2 contains dirname (simple)

TMPFILE=/tmp/flist

cd "$1"

# recursion
for file in *; do
  if [ -d "$file" -a -x "$file" ]; then
    "$0" $(pwd)/"$file" "$2"
  fi
done

# process directory
# check current directory name
if [ $(basename $(pwd)) != "$2" ]; then
  exit 0
fi

# count subdirs
subdirs=0
for file in *; do
  if [ -d "$file" ]; then
    subdirs=$(expr "$subdirs" + 1)
  fi
done

# count files
files=0
for file in *; do
  if [ -f "$file" ]; then
    files=$(expr "$files" + 1)
  fi
done

if [ "$subdirs" -eq $(expr "$files" - 2) ]; then
  echo $(pwd) >> $TMPFILE
  
  d1="null"
  d2="null"
  
  while [ "$d1" == "$d2" -o -e "$d1" -o -e "$d2" ]; do
    echo "processing $(pwd)..."
    echo -n "please insert dirname (1) "
    read d1
  
    echo -n "please insert dirname (2) "
    read d2
  done
  
  mkdir "$d1"
  mkdir "$d2"
fi

exit 0