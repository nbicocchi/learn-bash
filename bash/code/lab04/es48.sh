#!/bin/bash

usage() { 
    echo "usage: $0 [-h] -d dirname f1 .. fn" 1>&2 
    exit 1
}

while getopts "d:h" o; do
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
[ -z "$D" ] && usage

for file in $*; do
    case "$file" in
        */*)    usage
                ;;
        *)      ;;
    esac
done

# Main body
missing=false
missing_list=""
for file in $*; do
    nfound=$(find "$D" -type f -name "$file" 2>/dev/null | wc -l)
    if [ "$nfound" -eq 0 ]; then
        missing=true
        missing_list="$missing_list $file"
    fi
done

if [ "$missing" == "false" ]; then
    echo "[Test passed]"
else
    echo "[Test failed]"
    for file in $missing_list; do 
        echo "[missing] $file"
    done
fi

exit 0
