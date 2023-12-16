#!/bin/bash

USAGE="usage: $0 filename"

if [ $# -ne 1 ]; then
	echo "$USAGE"
	exit 1
fi

echo '#!/bin/bash' > "$1"
echo "echo \"Hello World!\"" >> "$1"
echo "exit 0" >> "$1"

chmod 755 "$1"

exit 0

