#!/bin/bash

# $1 contains a directory
# $2 contains the current depth

cd "$1"

# recursion
for file in *; do
  if [ -d "$file" -a -x "$file" ]; then
    $0 "$file" $(expr $2 + 1)
  fi
done

# process directory
echo "[$2] $(pwd)"
if [ $2 -gt $(cat /tmp/maxlevel) ]; then
  echo "$2" > /tmp/maxlevel
fi

exit 0
