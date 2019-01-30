#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include "utils.h"

int main(int argc, char **argv) {
	int p[2];
	
	if (pipe(p) < 0) {
		zprintf(2, "error: pipe()\n");
		exit(1);
	}
	
	zprintf(1, "p[0] (read side) = %d\n", p[0]);
	zprintf(1, "p[1] (write side) = %d\n", p[1]);
	
	exit(0);
}
