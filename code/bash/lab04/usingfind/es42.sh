#!/bin/bash

source oslib.sh

# Process each item of DIRLIST
process_dirs() {
    F_COUNT=0
    IFS=$'\n'
    for dirname in $DIRLIST; do
        if [ $(basename "$dirname") != "$D" ]; then
            continue
        fi
    
        rm -rf "$dirname"/SOMMA >/dev/null 2>&1
        L_COUNT=0
        for fname in "$dirname"/*; do
            if [ -f "$fname" -a -r "$fname" ]; then
                if [ $(wc -c < "$fname") -gt "$N" ]; then
                    if [ $L_COUNT == 0 ]; then
                        echo "$dirname"
                    fi
                    cat "$fname" >> "$dirname"/SOMMA
                    F_COUNT=$(expr $F_COUNT + 1)
                    L_COUNT=$(expr $L_COUNT + 1)
                fi
            fi
        done
    done
    return 0
}

# Assign variable to make them available inside functions
G="$1"
D="$2"
N="$3"

# Check arguments
check_argc $# 3 
check_dir_absolute "$G"
check_dir_explorable "$G"
check_dir_relative_simple "$D"
check_number "$N"
check_number_positive_strict "$N"

# Recursive exploration (on Linux use find, on OSX use gfind)
DIRLIST=$(gfind "$G" -type d -printf '%p\n' 2>/dev/null | grep -v "Permission denied")
process_dirs

exit 0