#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include "utils.h"

int child(int index) {
	zprintf(1, "[%d] Child %d starting...\n", getpid(), index);
	exit(0);
}

int main(int argc, char **argv) {
	pid_t *pids;
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
	
	pids = (pid_t *)malloc(sizeof(pid_t) * n);
	for (i = 0; i < n; i++) {
		pids[i] = fork();
		switch (pids[i]) {
			case 0: /* child */
				child(i);
			case -1: /* error */
				zprintf(2, "error: fork()\n");
				exit(1);
		}
	}
	
	/* father */
	zprintf(1, "[%d] Father starting...\n", getpid());
	for (i = n - 1; i >= 0; i--) {
		waitpid(pids[i], &status, 0);
		zprintf(1, "[%d] Child pid=%d exit=%d\n", getpid(), pids[i], WEXITSTATUS(status));
	}
	
	free(pids);
	exit(0);
}
