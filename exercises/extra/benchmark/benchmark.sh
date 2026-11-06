#!/bin/bash

FNAME="/tmp/ftest"

function benchmark() {
    echo "* executing $1..."
    start=$(python -c "import time; print (int(time.time() * 1000))")
    echo "output=$(bash -c "$1")"
    end=$(python -c "import time; print (int(time.time() * 1000))")
    echo "time=$(expr $end - $start)ms"
    echo ""
}

echo "Generating test file..."
python -c "for i in range(10000000): print(i)" > "$FNAME"

echo "Starting benchmarks..."
benchmark "cat $FNAME | wc -l"
benchmark "wc -l $FNAME"
benchmark "wc -l < $FNAME"

rm -rf "$FNAME"

exit 0

