#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "utils.h"

int main(int argc, char **argv) {
	pid_t pid;
	int status;
	
	pid = fork();
	switch (pid) {
		case -1: /* error */
			zprintf(2, "error: fork()\n");
			exit(1);
		case 0: /* child */
			zprintf(1, "Hello, I'm the child! [fork() %d]\n", pid);
			exit(0);
		default: /* father */
			zprintf(1, "Hello, I'm the father! [fork() %d]\n", pid);
			wait(&status);
			zprintf(1, "[%d] Child exited %d\n", getpid(), WEXITSTATUS(status));
			exit(0);
	}
}


