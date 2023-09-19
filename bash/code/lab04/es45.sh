#!/bin/bash

LINKDIR="/tmp/links"

usage() { 
    echo "usage: $0 d1 .. dn" 1>&2
    exit 1
}

# Process arguments
while getopts "h" o; do
    case "$o" in
        h)  usage
            ;;
        *)  usage
            ;;
    esac
done

# Shift parameters away. $1 become first directory
shift $(expr $OPTIND - 1)

# Check parameters
[ $# -lt 1 ] && usage

# Check dirs
for dname in $*; do
  case "$dname" in 
    /*) ;;
    *)  usage
        ;;
  esac

  [ ! -d "$dname" ] && usage
  [ ! -x "$dname" ] && usage
done

# Main body
rm -rf "$LINKDIR"
mkdir -p "$LINKDIR"
count=0
for dname in $*; do
  list=$(find "$dname" -type f -readable -mtime -1 2>/dev/null)
  for item in $list; do
    echo "$item"
    ln -s "$item" "$LINKDIR"/$(basename "$item")."$count"
    count=$(expr "$count" + 1)
  done
done

exit 0