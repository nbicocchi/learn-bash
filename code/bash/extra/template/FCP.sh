#!/bin/bash

USAGE="usage: $0 dir(abs) fname(rel) n(>0)"

# check argument number
if [ $# -ne 3 ]; then
  echo "$USAGE"
  exit 1
fi

# check absolute path
case "$1" in 
  /*) ;;
  *) echo "$USAGE"
     exit 2
    ;;
esac

# check if path is a directory and executable
if [ ! -d "$1" -o ! -x "$1" ]; then
  echo "$USAGE"
  exit 3
fi

# check relative path
case "$2" in
  */*) echo "$USAGE"
       exit 4
       ;;
  *) ;;
esac

# check number
expr "$3" + 0 >/dev/null 2>&1
case $? in
  0) ;; # result != 0
  1) ;; # result == 0
  2) echo "$USAGE"; 
     exit 5
     ;; 
esac

# check number greater than 0 (man test for other options)
if [ "$3" -le 0 ]; then
  echo "$USAGE"
  exit 6
fi

# needed for global aggregates
rm -rf /tmp/flist >/dev/null 2>&1

# launch recursive script
export PATH=$(pwd):$PATH
FCR.sh $*

# global aggregates computation
count=0
if [ -f "/tmp/flist" ]; then
  count=$(wc -l < /tmp/flist)
fi
echo "found: "$count" files!"

exit 0
