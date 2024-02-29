#!/bin/bash

# Both stdout and stderr are attached to the same terminal
# For testing try the following commands:
# $ ./es27.sh 1>/dev/null  (shows only stderr) 
# $ ./es27.sh 2>/dev/null  (shows only stout)

for fname in *; do
  case "$fname" in
    *.sh) echo "$fname" 1>&2 
          ;;
    *) echo "$fname"
       ;;
  esac
done

exit 0

