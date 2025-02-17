#!/bin/bash

TIME=5
MESSAGE="Hello World!"
DEBUG=FALSE

usage() { 
    echo "Usage: $0 [-t <1|5|10>] [-m <string>] [-d] filename" 1>&2; 
    exit 1; 
}

while getopts "t:m:dh" o; do
    case "$o" in
        t)  TIME="$OPTARG"
            [ $TIME -eq 1 ] || [ $TIME -eq 5 ] || [ $TIME -eq 10 ] || usage
            ;;
        m)  MESSAGE="$OPTARG"
            ;;
        d)  DEBUG=TRUE
            ;;
        h)  usage
            ;;
        *)  usage
            ;;
    esac
done

# Shift parameters away. $1 becomes filename
shift $(expr $OPTIND - 1)

# Check if filename exists
[ -e "$1" ] || usage

echo t = "$TIME"
echo m = "$MESSAGE"
echo d = "$DEBUG"
echo filename = "$1"

exit 0