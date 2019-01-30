#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "utils.h"

sig_t default_handler;
int count = 0;

void sig_int_handler(int s) {
	zprintf(1, "CTRL-Pressed!\n");
	if (++count > 2) {
		signal(SIGINT, default_handler);
	}
}

/* main function */
int main(int argc, char **argv) {
	default_handler = signal(SIGINT, sig_int_handler);
	
	while(TRUE) {
		/* avoids cpu waste */
		sleep(1);
	}
	
	exit(0);
}

