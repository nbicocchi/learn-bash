#!/bin/bash

source oslib.sh

# Process a single directory
process_dir_phase_A() {
	if [ -d "$D" ]; then
		echo $(pwd)/"$1"
	fi
    return 0
}

# Process a single directory
process_dir_phase_B() {
	if [ ! -d "$D" ]; then
		mkdir "$D"
	fi
    return 0
}

# Loop folders recusively
recurse_dir() {
    cd "$1"
    
    # Eventually notifies the name of current dir
    if [ "$DEBUG" == "ON" ]; then
	echo "# entering " $(pwd)
    fi
    
    # Scan for sub-directories
	for fname in *; do
        if [ -d "$fname" -a -x "$fname" ]; then
            recurse_dir "$fname"
        fi
    done
    
    # Process current dir
    $PROCESS_DIR "$2"
    
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
echo "Phase A... "
PROCESS_DIR=process_dir_phase_A
recurse_dir "$G"

echo -n "Execute Phase B (Y/N)? "
read answer
case "$answer" in
	Y|y) ;;
	N|n) exit 0;;
esac

echo "Phase B... "
PROCESS_DIR=process_dir_phase_B
recurse_dir "$G"

echo "Phase A... "
PROCESS_DIR=process_dir_phase_A
recurse_dir "$G"

exit 0
