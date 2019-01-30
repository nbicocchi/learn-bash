#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "utils.h"

int terminated = 0;

void sig_usr1_handler(int s) {
		zprintf(1, "received SIGUSR1!\n");
}

void sig_usr2_handler(int s) {
		zprintf(1, "received SIGUSR2! quitting...!\n");
		terminated = 1;
}

/* child function */
int child() {
	signal(SIGUSR1, sig_usr1_handler);
	signal(SIGUSR2, sig_usr2_handler);
	
	while(!terminated) {
		/* avoids cpu waste */
		sleep(1);
	}
	
	exit(0);
}


/* father function */
int father(int child_n, int *pids) {
	int i;
	
	/* wait for children */
	sleep(1);
	
	for (i = 0; i < child_n ; i++) { 
		zprintf(1, "[%d] sending SIGUSR1 to child (%d, %d)...\n", getpid(), i, pids[i]);
		kill(pids[i], SIGUSR1);
	}
	
	/* wait for children */
	sleep(1);
	
	for (i = 0; i < child_n ; i++) { 
		zprintf(1, "[%d] sending SIGUSR2 to child (%d, %d)...\n", getpid(), i, pids[i]);
		kill(pids[i], SIGUSR2);
	}
	
	/* wait for children */
	for (i = 0; i < child_n; i++) {
		wait(NULL);
	}
	
	exit(0);
}


/* main function */
int main(int argc, char **argv) {
	int i, *pids, child_n;
	
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
	
	/* allocate memory for pids */
	pids = (int *)malloc(sizeof(int) * child_n);
	
	/* init child processes */
	for (i=0; i < child_n; i++) { 
		pids[i] = fork(); 
		switch(pids[i]) {
			case 0: 
				child();
			case -1:
				zprintf(1, "[%d] error fork()\n", getpid());
				exit(1);
		}
	}
	
	father(child_n, pids);
}

