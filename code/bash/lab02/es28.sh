#!/bin/bash

for fname in *; do
  grep "#!/bin/bash" "$fname" >/dev/null 2>&1
  if [ $? -eq 0 ]; then
    echo "$fname"
  fi
done
