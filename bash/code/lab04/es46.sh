#!/bin/bash

LOG=/tmp/script.log

usage() { 
    echo "usage: $0 [-h] -a A -b B -d dirname" 1>&2 
    exit 1
}

while getopts "d:a:b:h" o; do
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
        a)  A="$OPTARG"
            expr $A + 0 >/dev/null 2>&1
            [ $? -gt 1 -o $A -lt 0 ] && usage 
            ;;
        b)  B="$OPTARG"
            expr $B + 0 >/dev/null 2>&1
            [ $? -gt 1 -o $B -lt 0 ] && usage 
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
[ -z "$A" ] && usage
[ -z "$B" ] && usage

# Main body
echo "processing..."
rm -rf "$LOG"
list=$(find "$D" -type d 2>/dev/null)
for item in $list; do
  files=$(find "$item" -maxdepth 1 -type f -readable)
  tsize=0
  for file in $files; do
    fsize=$(cat "$file" | wc -c)
    tsize=$(expr "$tsize" + "$fsize")
  done
  if [ "$tsize" -ge "$A" -a "$tsize" -le "$B" ]; then
    echo "$tsize;""$item"
    echo "$tsize;""$item" >> "$LOG"
  fi
done

echo "summary..."
sort -n "$LOG"

exit 0
