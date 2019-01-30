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
	        | p0
	 | ---> | <---|
	 |      |     |	 
	c0      c1    c2
*/


/* child function */
int child(struct test_pipe *t, int *p) {
	/* close unused pipe sides */
	close(p[0]); 
	
	/* filling data structure */
	fill_test_pipe(t, 0, getpid(), 2.2, 2.3, "System OK!");
	
	/* writing phase */
	zprintf(1, "[%d] writing...\n", getpid());			
	if (write(p[1], t, sizeof(struct test_pipe)) != sizeof(struct test_pipe)) {
		zprintf(1, "[%d] write() failed\n", getpid());
		exit(1);
	}
	
	exit(0);
}

/* father function */
int father(struct test_pipe *t, int *p, int n_children) {
	int i;
	
	/* close unused pipe sides */
	close(p[1]); 
	
	for (i = 0; i < n_children; i++) { 
		/* clear data structure */
		clear_test_pipe(t);
		
		/* read data 
		 * nota: nella pipe vengono inserite dai figli dei "blocchi"
		 * di byte la cui dimensione e' quella di struct test_pipe.
		 * considerata l'atomicità di write(), il padre o legge una 
		 * intera struttura, o si sospende fino al momento opportuno
		 * o, ancora, ottiene 0 per indicare che la pipe
		 * ha il lato scrittura chiuso
		 */
		if (read(p[0], t, sizeof(struct test_pipe)) != sizeof(struct test_pipe)) {
			zprintf(1, "[%d] error read()\n", getpid());
			exit(1);
		}

		zprintf(1, "[%d] cid = %d\n", getpid(), t->child_id);
		zprintf(1, "[%d] pid = %d\n", getpid(), t->process_id);
		zprintf(1, "[%d] data = %f, %f\n", getpid(), t->data[0], t->data[1]);
		zprintf(1, "[%d] message = %s\n", getpid(), t->msg);
	}
	
	/* wait for children */
	for (i = 0; i < n_children; i++) {
		wait(NULL);
	}
	
	exit(0);
}


/* main function */
int main(int argc, char **argv) {
	int i;
	int pid;
	int n_children;
	int p[2];
	struct test_pipe t;
	
	/* arguments check */
	if (argc < 2) {
		zprintf(1, "error: %s n_children\n", argv[0]);
		exit(1);
	}
	
	/* get n_children from command line */
	n_children = atoi(argv[1]);
	if (n_children <= 0) { 
		zprintf(1, "error: n_children must be positive\n");
		exit(1);
	}
	
	/* init pipe */
	if (pipe(p) != 0) { 
		zprintf(1, "[%d] error pipe()\n", getpid());
		exit(1);
	}
	
	/* init child processes */
	for (i=0; i < n_children; i++) { 
		pid=fork(); 
		switch(pid) {
			case 0: 
				child(&t, p);
			case -1:
				zprintf(1, "[%d] error fork()\n", getpid());
				exit(1);
		}
	}
	
	father(&t, p, n_children);
}

