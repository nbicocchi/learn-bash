#!/bin/bash

source oslib.sh

# Process a single directory
process() {
    IFS=$'\n'
    for dirname in $DIRLIST; do
 
        if [ $(basename "$dirname") != "$2" ]; then
            continue
        fi
    
        for fname in *; do
            if [ -f "$fname" -a -r "$fname" -a "$fname" != "SOMMA" ]; then
                if [ $(cat "$fname" | wc -c) -gt "$N" ]; then
                    cat "$fname" >> SOMMA
                    F_COUNT=$(expr $F_COUNT + 1)
                fi
            fi
        done
		
    return 0
}

# Check arguments
check_argc $# 3 
check_dir_absolute "$1"
check_dir_explorable "$1"
check_dir_relative_simple "$2"
check_number "$3"
check_number_positive_strict "$3"

# Recursive exploration
DIRLIST=$(gfind "$G" ! -path "$1" -type d -printf '%p\n' 2>/dev/null | grep -v "Permission denied")

# Result
echo $F_COUNT
exit 0
