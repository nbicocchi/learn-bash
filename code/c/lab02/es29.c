#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include "utils.h"

int read_bytes(int fd) {
	int n = 0;
	char buf;
	
	while (read(fd, &buf, 1) > 0) n++;
	return n;
}

int main(int argc, char **argv) {
	char *usage = "usage: %s filename\n";
	pid_t pid;
	int fd;
	int status;
	
	if (argc < 2) {
        zprintf(2, usage, argv[0]);
        exit(1);
    } 
	
	fd = open(argv[1], O_RDONLY);
	if (fd < 0) {
        zprintf(2, "error: open()\n");
        exit(1);
    } 
	
	pid = fork();
	switch (pid) {
		case 0: /* child */
			zprintf(1, "[%d] Child counted %d bytes\n", getpid(), read_bytes(fd));
			exit(0);
		case -1: /* error */
			zprintf(2, "error: fork()\n");
			exit(1);
		default: /* father */
			zprintf(1, "[%d] Father counted %d bytes\n", getpid(), read_bytes(fd));
			wait(&status);
			zprintf(1, "[%d] Child exited %d\n", getpid(), WEXITSTATUS(status));
			exit(0);
	}
}
