#!/bin/bash

usage() {
	echo "usage: $0 filename"
	exit 1
}
if [ $# -ne 1 ]; then
	usage
fi

echo '#!/bin/bash' > "$1"
echo 'echo "Hello World!"' >> "$1"
echo 'exit 0' >> "$1"

chmod 755 "$1"

exit 0

