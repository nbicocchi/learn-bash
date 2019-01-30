#!/bin/bash

for fname in *; do
  case "$fname" in
    *.sh) echo "$fname" 1>&2 
          ;;
    *) echo "$fname"
       ;;
  esac
done
