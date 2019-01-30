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
	 | ---> | <---|
   p0|    p1|   p2|
     |      |     | 
	c0     c1    c2
	
*/

/* when multiple pipes are needed this definition is useful */
typedef int pipe_t[2];

/* child function */
int child(struct test_pipe *t, pipe_t *p, int child_n, int child_id) {
	int i;
	
	/* close unused pipe sides */
	for (i = 0; i < child_n; i++) { 
		close(p[i][0]); 
		if (i != child_id) close(p[i][1]); 
	}
	
	/* filling data structure */
	fill_test_pipe(t, child_id, getpid(), 2.2, 2.3, "System OK!");
	
	/* writing phase */
	zprintf(1, "[%d] writing...\n", getpid());			
	if (write(p[child_id][1], t, sizeof(struct test_pipe)) != sizeof(struct test_pipe)) {
		zprintf(1, "[%d] write() failed\n", getpid());
		exit(1);
	}
	
	exit(0);
}


/* father function */
int father(struct test_pipe *t, pipe_t *p, int child_n) {
	int i, nr;
	
	/* close unused pipe sides */
	for (i = 0; i < child_n; i++) { 
		close(p[i][1]); 
	}
	
	for (i = child_n - 1; i >= 0; i--) { 
		/* clear data structure */
		clear_test_pipe(t);
		
		/* read data 
		 * nota: nella pipe vengono inserite dai figli dei "blocchi"
		 * di byte la cui dimensione e' quella di struct test_pipe.
		 * visto che write() e' atomica, il padre o legge una intera struttura o
		 * si sospende fino al momento della disponibilita'
		 * o, ancora, ottiene 0 per indicare che la pipe
		 * non ha dati e non ne potra' mai piu' avere (lato scrittura chiuso)
		 */
		nr = read(p[i][0], t, sizeof(struct test_pipe));
		switch(nr) {
			case sizeof(struct test_pipe):
				zprintf(1, "[%d] cid = %d\n", getpid(), t->child_id);
				zprintf(1, "[%d] pid = %d\n", getpid(), t->process_id);
				zprintf(1, "[%d] data = %f, %f\n", getpid(), t->data[0], t->data[1]);
				zprintf(1, "[%d] message = %s\n", getpid(), t->msg);
				break;
			default:
				zprintf(1, "[%d] error read()\n", getpid());
				exit(1);
		}
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
	p = (pipe_t *) malloc(sizeof(pipe_t) * child_n);
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
				child(&t, p, child_n, i);
			case -1:
				zprintf(1, "[%d] error fork()\n", getpid());
				exit(1);
		}
	}
	
	father(&t, p, child_n);
}

