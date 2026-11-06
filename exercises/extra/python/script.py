#!/usr/bin/env python

import sys
import subprocess

if len(sys.argv) < 2:
	sys.stderr.write("usage: %s f1 .. fn\n" % (sys.argv[0]))
	sys.exit(1)

for fname in sys.argv[1:]:
	out = subprocess.check_output(['wc', '-l', fname])
	print("%s: %s" % (fname, out.split(' ')[0]))

sys.exit(0)
