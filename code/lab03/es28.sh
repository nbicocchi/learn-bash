#!/bin/bash

for fname in *; do
	# output is discarded because we are looking for $?
	if grep "#!/bin/bash" "$fname" 1>/dev/null 2>&1; then
		echo "$fname matches!"
	fi
done

exit 0

