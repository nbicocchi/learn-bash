#!/bin/sh

## Arguments (number) ##
check_argc() {
    if [ $1 -ne $2 ]; then
	echo "error: $2 parameters required"
	exit 1
    fi
}

check_argc_min() {
    if [ $1 -lt $2 ]; then
	echo "error: $2 parameters required"
	exit 1
    fi
}

check_argc_max() {
    if [ $1 -gt $2 ]; then
	echo "error: $2 parameters required"
	exit 1
    fi
}


## Directories ##
check_dir_absolute() {
    case "$1" in
	/*) ;;
	*) echo "error: $1 must be absolute" 
	   exit 1
	   ;;
    esac
}

check_dir_relative() {
    case "$1" in
	/*) echo "error: $1 must be relative" 
	    exit 1
	    ;;
	*) ;;
    esac
}

check_dir_relative_simple() {
    case "$1" in
	/*) echo "error: $1 must be relative simple" 
	    exit 1
	    ;;
	*/*) echo "error: $1 must be relative simple" 
	    exit 1
	    ;;
	*) ;;
    esac
}

check_dir_explorable() {
    if [ ! -d "$1" -o ! -x "$1" ]; then
		echo "error: $1 must be explorable"
		exit 1
    fi
}


## Numbers ##
check_number() {
    expr "$1" + 0 1>/dev/null 2>&1
    case $? in
		0) ;; # risultato != 0
		1) ;; # risultato == 0
		2) echo "$1 is not a number"; exit 1;; # syntax error, es. K='+'
		3) echo "$1 is not a number"; exit 1;; # non-numeric argument, es. K='a'
    esac
}

check_number_positive() {
    if [ $1 -lt 0 ]; then
		echo "error: $1 must be positive"
		exit 1
    fi
}

check_number_negative() {
    if [ $1 -gt 0 ]; then
		echo "error: $1 must be negative"
		exit 1
    fi
}

check_number_positive_strict() {
    if [ $1 -le 0 ]; then
		echo "error: $1 must be strictly positive"
		exit 1
    fi
}

check_number_negative_strict() {
    if [ $1 -ge 0 ]; then
		echo "error: $1 must be strictly negative"
		exit 1
    fi
}

check_number_even() {
    if [ $(expr $1 % 2) -ne 0 ]; then
		echo "error: $1 must be even"
		exit 1
    fi
}

check_number_odd() {
    if [ $(expr % 2) -eq 0 ]; then
		echo "error: $1 must be odd"
		exit 1
    fi
}

