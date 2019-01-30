#!/bin/bash

# $1 contains current dir
# $2 contains dirname (simple)
# $3 contains phase (A/B)

cd "$1"

# recursion
for file in *; do
  if [ -d "$file" -a -x "$file" ]; then
    "$0" "$file" "$2" "$3"
  fi
done

# process directory (phase A)
if [ "$3" == "A" ]; then
  if [ -d "$2" ]; then
    echo $(pwd)
  fi
fi

# process directory (phase B)
if [ "$3" == "B" ]; then
  if [ ! -d "$2" ]; then
    mkdir "$2"
  fi
fi

exit 0