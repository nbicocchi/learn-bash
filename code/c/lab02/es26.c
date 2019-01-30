#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdarg.h>
#include "utils.h"

int main(int argc, char **argv) {
	char *usage = "usage: %s cmd\n";
	pid_t pid;
	int status;
	
	if (argc < 2) {
        zprintf(2, usage, argv[0]);
        exit(1);
    } 

	pid = fork();
	switch (pid) {
		case 0: /* child */
			zprintf(1, "[%d] executing %s...\n", getpid(), argv[1]);
			execlp(argv[1], argv[1], (char *)0, (char *)0); 
		case -1: /* error */
			zprintf(2, "error: fork()\n");
			exit(1);
	}
	
	/* father */
	pid = wait(&status);
	zprintf(1, "[%d] Child pid=%d exit=%d\n", getpid(), pid, WEXITSTATUS(status));
	exit(0);
}

