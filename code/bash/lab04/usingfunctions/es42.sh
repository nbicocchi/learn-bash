#!/bin/bash

source oslib.sh

# Process a single directory
process_dir() {
	if [ $(basename $(pwd)) != "$D" ]; then
		return 1
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

# Loop folders recusively
recurse_dir() {	
    cd "$1"
    
    # Eventually notifies the name of current dir
    if [ "$DEBUG" == "ON" ]; then
		echo "# entering " $(pwd)
    fi
    
    # Process current dir
    process_dir 
    
    # Scan for sub-directories
	for fname in *; do
        if [ -d "$fname" -a -x "$fname" ]; then
            recurse_dir "$fname" 
        fi
    done
    
    cd ..
}

# Check arguments
check_argc $# 3 
check_dir_absolute "$1"
check_dir_explorable "$1"
check_dir_relative_simple "$2"
check_number "$3"
check_number_positive_strict "$3"

# Variables
G="$1"
D="$2"
N="$3"
DEBUG=OFF
F_COUNT=0

# Recursive exploration
recurse_dir "$G"

# Result
echo $F_COUNT
exit 0
