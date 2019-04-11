#!/bin/bash

source oslib.sh

# Process a single directory
process_dirs() {
    T_COUNT=0
    IFS=$'\n'
    for dirname in $DIRLIST; do
        if [ $(basename "$dirname") != "$D" ]; then
            continue
        fi
    	
    	f_count=0
    	d_count=0
    	for fname in "$dirname"/*; do
            if [ -d "$fname" ]; then
                d_count=$(expr $d_count + 1) 
            fi
            
            if [ -f "$fname" ]; then
                f_count=$(expr $f_count + 1) 
            fi
        done
        
        if [ $f_count -ne $(expr $d_count + 2) ]; then
        	continue
        fi
        
        echo "$dirname"
        
        echo -n "insert name 1: "
    	read d_name
    	mkdir "$dirname"/"$d_name"
    	
    	echo -n "insert name 2: "
    	read d_name
    	mkdir "$dirname"/"$d_name"

        T_COUNT=$(expr $T_COUNT + 2)
	done
    return 0
}

# Assign variable to make them available inside functions
G="$1"
D="$2"

# Check arguments
check_argc $# 2
check_dir_absolute "$G"
check_dir_explorable "$G"
check_dir_relative_simple "$D"

# Recursive exploration (on Linux use find, on OSX use gfind)
DIRLIST=$(gfind "$1" -type d -printf '%p\n' 2>/dev/null | grep -v "Permission denied")
process_dirs

exit 0
