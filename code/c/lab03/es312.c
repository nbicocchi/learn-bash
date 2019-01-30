#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <sys/wait.h>
#include "utils.h"

/* 
	topology definition 
    
	        F
	        ^
	        | 
	 |----->|<----|
   p0|    p1|   p2|
     |      |     | 
	c0     c1    c2
     |      |     | 
    cmd0   cmd1  cmd2
*/

/* when multiple pipes are needed this definition is useful */
typedef int pipe_t[2];

int nephew(char **argv, pipe_t p, int child_n, int child_id) {
	/* close unused pipe sides (shared with child)*/
	close(p[0]);

	/* assign stdout to p_l2[1] */
	close(1);
	dup2(p[1], 1);
	close(p[1]);

	/* execute external cmd */
	execlp("wc", "-l", "-l", argv[child_id + 1], (char *)0);

	zprintf(1, "[%d] error exec()\n", getpid());
	exit(1);
}

/* child function */
int child(char **argv, pipe_t *p, int child_n, int child_id) {
	int i;
	int lines;
	int pid;
	pipe_t p_l2;
	char wc_stdout[8];
	
	/* close unused pipe sides (shared with father)*/
	for (i = 0; i < child_n; i++) {
		if (i != child_id) close(p[i][1]);
		close(p[i][0]);
	}

	/* init pipe shared with nephew */
	if (pipe(p_l2) < 0) { 
		zprintf(1, "[%d] error pipe()\n", getpid());
		exit(1);
	}

	pid=fork(); 
	switch(pid) {
		case 0: 
			nephew(argv, p_l2, child_n, child_id);
		case -1:
			zprintf(1, "[%d] error fork()\n", getpid());
			exit(1);
	}	

	/* close unused pipe sides (shared with nephew)*/
	close(p_l2[1]);

	/* read from nephew */
	if (read(p_l2[0], wc_stdout, sizeof(wc_stdout)) != sizeof(wc_stdout)) {
		zprintf(1, "[%d] read() failed\n", getpid());
		exit(1);
	}

	/* this is for debug purposes */
	/* wc implementations might change */
	zprintf(1, "[%d] received from wc=\"%s\"\n", getpid(), wc_stdout);
	lines = atoi(wc_stdout);
	
	/* write number of lines to father */
	if (write(p[child_id][1], &lines, sizeof(int)) != sizeof(int)) {
		zprintf(1, "[%d] write() failed\n", getpid());
		exit(1);
	}

	/* wait for nephew */
	wait(NULL);

	exit(0);
}

/* father function */
int father(char **argv, pipe_t *p, int child_n) {
	int i;
	int lines;
	
	/* close unused pipe sides */
	for (i = 0; i < child_n; i++) { 
		close(p[i][1]);
	}
	
	/* wait for number of lines */		
	for (i = 0; i < child_n; i++) {	
		if (read(p[i][0], &lines, sizeof(int)) != sizeof(int)) {
			zprintf(1, "[%d] read() failed\n", getpid());
			exit(1);
		}
		zprintf(1, "[%d] received lines=%d from child=%d\n", getpid(), lines, i);
	}
	
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
	
	/* arguments check */
	if (argc < 2) {
		zprintf(1, "error: %s f1 .. fn\n", argv[0]);
		exit(1);
	}
	
	/* get child_n from command line */
	child_n = argc - 1;
	
	/* allocate memory for pipes */
	p = (pipe_t *) malloc(sizeof(pipe_t) * (child_n));
	if (p == NULL) {
		zprintf(1, "[%d] error malloc()\n", getpid());
		exit(1);
	}
	
	/* init pipes */
	for (i = 0; i < child_n; i++) { 
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
				child(argv, p, child_n, i);
			case -1:
				zprintf(1, "[%d] error fork()\n", getpid());
				exit(1);
		}
	}
	
	father(argv, p, child_n);
}