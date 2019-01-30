#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include "utils.h"

int read_bytes(char *filename) {
	int fd, n = 0;
	char buffer;

	/* open file for reading */
	fd = open(filename, O_RDONLY);
	if (fd < 0) {
		zprintf(2, "error: open()\n");
		exit(1);
	}
	
	/* count bytes */
	while (read(fd, &buffer, 1) > 0) n++;
	return n;
}

int main(int argc, char **argv) {
	char *usage = "usage: %s filename\n";
	pid_t pid;
	int status;
	
	if (argc < 2) {
        zprintf(2, usage, argv[0]);
        exit(1);
    } 
		
	pid = fork();
	switch (pid) {
		case 0: /* child */
			zprintf(1, "[%d] Child counted %d bytes\n", getpid(), read_bytes(argv[1]));
			exit(0);
		case -1: /* error */
			zprintf(2, "error: fork()\n");
			exit(1);
		default: /* father */
			zprintf(1, "[%d] Father counted %d bytes\n", getpid(), read_bytes(argv[1]));
			wait(&status);
			zprintf(1, "[%d] Child exited %d\n", getpid(), WEXITSTATUS(status));
			exit(0);
	}
}
