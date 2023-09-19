#!/bin/bash

for fname in *; do
	# output is discarded because we are looking for $?
	grep "#!/bin/bash" "$fname" 1>/dev/null 2>&1
	if [ $? -eq 0 ]; then
		echo "$fname matches!"
	fi
done

exit 0

