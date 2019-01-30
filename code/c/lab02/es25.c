#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdarg.h>
#include "utils.h"

void child(int index) {	
	zprintf(1, "[%d] executing echo...\n", getpid());
	execlp("/bin/echo", "echo", "Hello!", (char *)0); 
}

int main(int argc, char **argv) {
	pid_t pid;
	int n = 1;
	int i;
	int opt;
	int status;

	for (;;) {
		opt = getopt(argc, argv, "n:");
		if (opt == -1) break;
		switch (opt) {
			case 'n':
				n = atoi(optarg);
				break;
		}
	}
	
	for (i = 0; i < n; i++) {
		pid = fork();
		switch (pid) {
			case 0: /* child */
				child(i);
			case -1: /* error */
				zprintf(2, "error: fork()\n");
				exit(1);
		}
	}
	
	/* father */
	zprintf(1, "[%d] Father starting...\n", getpid());
	for (i = 0; i < n; i++) {
		pid = wait(&status);
		zprintf(1, "[%d] Child pid=%d exit=%d\n", getpid(), pid, WEXITSTATUS(status));
	}
	
	exit(0);
}

