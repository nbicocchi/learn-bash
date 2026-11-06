#!/bin/bash

LOG=/tmp/script.log

usage() { 
    echo "usage: $0 [-h] -d dirname f1 .. fn" 1>&2 
    exit 1
}

while getopts "d:h" o; do
    case "$o" in
        d)  D="$OPTARG"
            case "$D" in 
                /*) [ ! -d "$D" ] || [ ! -x "$D" ] && usage
                    ;;
                *)  usage
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
shift $(( OPTIND - 1 ))

# Check if parameters have been acquired
[ $# -eq 0 ] && usage
[ -z "$D" ] && usage

# Main body
echo "processing..."
rm -rf "$LOG"
dirs=$(find "$D" -type d 2>/dev/null)
for dir in $dirs; do
    found=0
    for file in "$@"; do
        if [ -f "$dir"/"$file" ] && [ -r "$dir"/"$file" ]; then
            found=$(( found + 1 ))
        fi
    done
    if [ $found -gt 0 ]; then
        echo "$found;""$dir" 
        echo "$found;""$dir" >> "$LOG"
    fi
done 

echo "summary..."
sort -n "$LOG"

exit 0
