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
	char *usage = "usage: %s cmd [opt]\n";
	int i, pid, status;
	char **argv_child;

	if (argc < 2) {
        zprintf(2, usage, argv[0]);
        exit(1);
    } 

	pid = fork();
	switch (pid) {
		case 0: /* child */
			/* set up new argv for child */
			argv_child = (char **)malloc(sizeof(char *) * argc);
			for (i = 1; i <= argc; i++) {
				argv_child[i - 1] = argv[i];
			}
			/* command execution */
			zprintf(1, "[%d] executing %s...\n", getpid(), argv_child[0]);
			execvp(argv_child[0], argv_child); 
		case -1: /* error */
			zprintf(2, "error: fork()\n");
			exit(1);
	}
	
	/* father */
	pid = wait(&status);
	zprintf(1, "[%d] Child pid=%d exit=%d\n", getpid(), pid, WEXITSTATUS(status));
	exit(0);
}

