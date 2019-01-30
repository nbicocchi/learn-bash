#!/bin/bash

source oslib.sh

# Process a single directory
process_dir() {
	if [ $(basename $(pwd)) != "$D" ]; then
		return 1
	fi
	
	f_count=0
	d_count=0
	for fname in *; do
        if [ -d "$fname" ]; then
            d_count=$(expr $d_count + 1) 
        fi
        
        if [ -f "$fname" ]; then
            f_count=$(expr $f_count + 1) 
        fi
    done
    
    if [ $f_count -ne $(expr $d_count + 2) ]; then
    	return 1
    fi
    
    echo $(pwd)
    echo -n "insert name 1: "
	read d_name
	mkdir "$d_name"
	
	echo -n "insert name 2: "
	read d_name
	mkdir "$d_name"
	
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
check_argc $# 2
check_dir_absolute "$1"
check_dir_explorable "$1"
check_dir_relative_simple "$2"

# Variables
G="$1"
D="$2"
DEBUG=OFF

# Recursive exploration
recurse_dir "$G"

# Result
exit 0
