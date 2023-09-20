#!/bin/bash

DEBUG=N

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
shift $(( OPTIND - 1 ))

# Check if parameters have been acquired
[ $# -eq 0 ] && usage
[ -z "$EXT" ] && usage

for dir in "$@"; do
    case "$dir" in
        /*) ;;
        *)  usage
            ;;
    esac
done

# Main body
echo "processing..."
for dir in "$@"; do
    files=$(find "$dir" -type f -readable -name '*'"$EXT" 2>/dev/null)

    if [ -z "$files" ]; then
        average=0
    else
        tsize=0
        nfiles=0
        for file in $files; do
            size=$(wc -c < "$file")
            tsize=$(( tsize + size ))
            nfiles=$(( nfiles + 1 ))
            [ $DEBUG = "Y" ] && echo ["$nfiles"] [size="$size"] "$file"
        done
        average=$(( tsize / nfiles ))
    fi
    echo "$dir"\;"$nfiles"\;"$average"  
done

exit 0
