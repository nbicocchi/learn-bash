#!/bin/bash

usage() { 
    echo "usage: $0 [-h] -d dirname -m EQ|NE" 1>&2 
    exit 1
}

while getopts "d:m:h" o; do
    case "$o" in
        d)  D="$OPTARG"
            case "$D" in 
                /*) [ ! -d "$D" ] && usage
                    [ ! -x "$D" ] && usage
                    ;;
                *)  usage
                    ;;
            esac
            ;;
        m)  M="$OPTARG"
            case "$M" in
                EQ|NE) ;;
                *)     usage
                       ;;
            esac
            ;;
        h)  usage
            ;;
        *)  usage
            ;;
    esac
done

# Shift parameters away. In this case, useless.
shift $(expr $OPTIND - 1)

# Check if parameters have been acquired
[ -z "$D" ] && usage
[ -z "$M" ] && usage

# Main body
list=$(find "$D" -type d 2>/dev/null)
for item in $list; do
  ndirs=$(find "$item" -mindepth 1 -maxdepth 1 -type d | wc -l 2>/dev/null)
  nfiles=$(find "$item" -mindepth 1 -maxdepth 1 -type f | wc -l 2>/dev/null)
  [ "$M" == "EQ" -a "$ndirs" -eq "$nfiles" ] && echo "$item" ["$ndirs" dirs, "$nfiles" files]
  [ "$M" == "NE" -a "$ndirs" -ne "$nfiles" ] && echo "$item" ["$ndirs" dirs, "$nfiles" files]
done

exit 0
