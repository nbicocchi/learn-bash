#!/bin/bash

LOG="/tmp/script.log"
LINES=10

usage() { 
    echo "usage: $0 [-h] [-l lines] -f filename d1 .. dn" 1>&2
    exit 1
}

# Process arguments
while getopts "f:l:h" o; do
    case "$o" in
        f)  F="$OPTARG"
            case "$F" in 
                */*)  usage
                      ;;
                *)    ;;
            esac
            ;;
        l)  LINES="$OPTARG"
            case "$LINES" in
              ''|*[!0-9]*)
                usage
                ;;
              *)
                [ "$LINES" -lt 2 ] && usage 
                ;;
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
    if [ "$(wc -l < "$item")" -ge "$LINES" ]; then
      echo "$item"
      tail -n 2 "$item" | head -n 1 >> "$LOG"
    fi
  done
done

exit 0
