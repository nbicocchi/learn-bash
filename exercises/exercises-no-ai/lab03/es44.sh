#!/bin/bash

LOG="/tmp/script.log"

usage() { 
    echo "usage: $0 [-h] -f filename d1 .. dn" 1>&2
    exit 1
}

# Process arguments
while getopts "f:h" o; do
    case "$o" in
        f)  F="$OPTARG"
            case "$F" in 
                */*)  usage
                      ;;
                *)    ;;
            esac
            ;;
        h)  usage
            ;;
        *)  usage
            ;;
    esac
done

# Shift parameters away. $1 become first directory
shift $(( OPTIND - 1 ))

# Check parameters
[ $# -lt 1 ] && usage
[ -z "$F" ] && usage

# Check dirs
for dname in "$@"; do
  case "$dname" in 
    /*) 
      [ ! -d "$dname" ] || [ ! -x "$dname" ] && usage
      ;;
    *)  
      usage
      ;;
  esac
done

# Main body
rm -rf "$LOG"
for dname in "$@"; do
  list=$(find "$dname" -type f -readable -name "$F" 2>/dev/null)
  for item in $list; do
    bytes=$(wc -c < "$item")
    lines=$(wc -l < "$item")
    echo "$item"
    echo "$item":"$bytes":"$lines" >> "$LOG"
  done
done

exit 0