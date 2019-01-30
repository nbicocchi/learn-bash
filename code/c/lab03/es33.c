#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <sys/wait.h>
#include "utils.h"

#define SLOTS 16

/* child function */
int child(int *v, int *p) {
	int i;
	
	/* close write-side pipe */
	close(p[1]);
	
	for (i = 0; i < SLOTS; i++) {
		/* read from pipe */
		if (read(p[0], &v[i], sizeof(int)) != sizeof(int)) {
			zprintf(2, "error: read()\n");
			exit(1);
		}
		
		/* debug */
		zprintf(1, "[%d] (read) v[%d] = %d\n", getpid(), i, v[i]);
	}
	
	exit(0);
}

/* father function */
int father(int *v, int *p) {
	int status;
	int i;
	
	/* close read-side pipe */
	close(p[0]);
	
	/* Initialize random numbers generator */
	srand(9786875L);
	
	sleep(1);
		
	for (i = 0; i < SLOTS; i++) {
		/* generate random number */
		v[i] = rand() % 10;
		
		/* write on pipe */
		if (write(p[1], &v[i], sizeof(int)) != sizeof(int)) {
			zprintf(2, "error: write()\n");
			exit(1);
		}
		
		/* debug */
		zprintf(1, "[%d] (write) v[%d] = %d\n", getpid(), i, v[i]);
	}
	
	/* wait child before exit */
	wait(&status);
	exit(0);
}

int main(int argc, char **argv) {
	int pid;
	int p[2];
	int v[SLOTS];
	
	/* shared pipe */
	if (pipe(p) < 0) {
		zprintf(2, "error: pipe()\n");
		exit(1);
	}
	
	/* fork process */
	pid = fork();
	switch (pid) {
		case -1: /* error */
			zprintf(2, "error: fork()\n");
			exit(1);
		case 0: /* child */
			child(v, p);
	}
	
	father(v, p);
}
