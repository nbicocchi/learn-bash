#!/bin/bash

LOG=/tmp/script.log

usage() { 
    echo "usage: $0 [-h] -t extension d1 .. dn" 1>&2 
    exit 1
}

while getopts "t:h" o; do
    case "$o" in
        t)  EXT="$OPTARG"
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
[ $# -eq 0 ] && usage
[ -z "$EXT" ] && usage

for dir in $*; do
    case "$dir" in
        /*) ;;
        *)  usage
            ;;
    esac
done

# Main body
rm -rf "$LOG"
echo "processing..."
for dir in $*; do
    files=$(find "$dir" -type f -readable -name '*'$EXT 2>/dev/null)

    if [ -z "$files" ]; then
        average=0
    else
        tsize=0
        nfiles=0
        for file in $files; do
            size=$(cat "$file" | wc -c)
            tsize=$(expr "$tsize" + "$size")
            nfiles=$(expr "$nfiles" + 1)
        done
        average=$(expr "$tsize" / "$nfiles")
    fi

    echo "$average;$dir"
    echo "$average;$dir" >> "$LOG"    
done

echo "summary..."
sort -rn "$LOG"

exit 0
