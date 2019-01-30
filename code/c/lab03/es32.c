#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include "utils.h"

int main(int argc, char **argv) {
	int n = 0;
	int p[2];
	char c = 'a';
	
	if (pipe(p) < 0) {
		zprintf(2, "error: pipe()\n");
		exit(1);
	}
	
	while(write(p[1], &c, 1) > 0) {
		zprintf(1, "written %d bytes.\n", ++n);
	}
	
	exit(0);
}
