#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "utils.h"

int main(int argc, char **argv) {
	pid_t pid;
	int status;
	
	pid = fork();
	switch (pid) {
		case 0: /* child */
			zprintf(1, "Hello, I'm the child! [fork() %d]\n", pid);
			exit(0);
		default: /* father */
			zprintf(1, "Hello, I'm the father! [fork() %d]\n", pid);
			wait(&status);
			exit(0);
	}
}

