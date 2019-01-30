#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <sys/wait.h>
#include "utils.h"

/* 
	topology definition 
	
	------- F <------
	| p0            | p3
	V               |
	c0 ---> c1 ---> c2
	    p1      p2
	
*/

/* when multiple pipes are needed this definition is useful */
typedef int pipe_t[2];

/* child function */
int child(struct test_pipe *t, pipe_t *p, int child_n, int child_id) {
	int i;
	char cmd;
	
	/* close unused pipe sides */
	for (i = 0; i < child_n; i++) {
		if (i != child_id + 1) close(p[i][1]);
		if (i != child_id) close(p[i][0]);
	}
	
	/* wait for command */			
	if (read(p[child_id][0], &cmd, 1) != 1) {
		zprintf(1, "[%d] read() failed\n", getpid());
		exit(1);
	}
	
	/* print received command and pid */
	zprintf(1, "[%d] command (%c) received\n", getpid(), cmd);
	
	/* change command for debug purposes */
	cmd += 1;
	
	/* write command to next child */
	if (write(p[child_id + 1][1], &cmd, 1) != 1) {
		zprintf(1, "[%d] write() failed\n", getpid());
		exit(1);
	}
	
	exit(0);
}


/* father function */
int father(struct test_pipe *t, pipe_t *p, int child_n) {
	int i;
	char cmd = 'a';
	
	/* close unused pipe sides */
	for (i = 0; i < child_n; i++) { 
		if (i != 0) close(p[i][1]);
		if (i != child_n - 1) close(p[i][0]);
	}
	
	zprintf(1, "[%d] writing to child 0...\n", getpid());
	if (write(p[0][1], &cmd, 1) != 1) {
		zprintf(1, "[%d] write() failed\n", getpid());
		exit(1);
	}
	
	/* wait for command */			
	if (read(p[child_n][0], &cmd, 1) != 1) {
		zprintf(1, "[%d] read() failed\n", getpid());
		exit(1);
	}
	
	/* print received command and pid */
	zprintf(1, "[%d] command (%c) received\n", getpid(), cmd);
	
	/* wait for children */
	for (i = 0; i < child_n; i++) {
		wait(NULL);
	}
	
	exit(0);
}


/* main function */
int main(int argc, char **argv) {
	int i, pid, child_n;
	pipe_t *p;
	struct test_pipe t;
	
	/* arguments check */
	if (argc < 2) {
		zprintf(1, "error: %s n_children\n", argv[0]);
		exit(1);
	}
	
	/* get child_n from command line */
	child_n = atoi(argv[1]);
	if (child_n <= 0) { 
		zprintf(1, "error: n_children must be positive\n");
		exit(1);
	}
	
	/* allocate memory for pipes */
	p = (pipe_t *) malloc(sizeof(pipe_t) * (child_n + 1));
	if (p == NULL) {
		zprintf(1, "[%d] error malloc()\n", getpid());
		exit(1);
	}
	
	/* init pipes */
	for (i = 0; i < child_n + 1; i++) { 
		if (pipe(p[i]) < 0) { 
			zprintf(1, "[%d] error pipe()\n", getpid());
			exit(1);
		}
	}
	
	/* init child processes */
	for (i=0; i < child_n; i++) { 
		pid=fork(); 
		switch(pid) {
			case 0: 
				child(&t, p, child_n, i);
			case -1:
				zprintf(1, "[%d] error fork()\n", getpid());
				exit(1);
		}
	}
	
	father(&t, p, child_n);
}

