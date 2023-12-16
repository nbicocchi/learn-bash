#!/bin/bash

USAGE="usage: $0 dirname(abs) n"

# Check arguments
if [ $# -ne 2 ]; then
    echo "$USAGE"
    exit 1
fi

case "$1" in
    /*) ;;
    *) echo "$USAGE"
       exit 1
       ;;
esac

if [ ! -d "$1" ] || [ ! -x "$1" ]; then
    echo "$USAGE"
    exit 1
fi

case "$2" in
    [0-9]) ;;
    *) echo "$USAGE"
       exit 1
       ;;
esac

# Main body
list=$(find "$1" -type f -name "*$2*" -readable 2>/dev/null)
for item in $list; do
    if grep "$2" <"$item" 1>/dev/null 2>&1; then
        echo "$item"
    fi
done

exit 0