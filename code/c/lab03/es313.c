#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <sys/wait.h>
#include "utils.h"

/* 
	topology definition 
    
	c0 <---> F <---> c2
	   p0,p1 ^  p4,p5
	         |
	         | p2,p3
	         V
	         c1
*/

/* when multiple pipes are needed this definition is useful */
typedef int pipe_t[2];

/* return true is n is prime */
int is_prime(int n) {
	int i;

	for (i = 2; i < n; i++) {
		if (n % i == 0) return FALSE;
	}
	return TRUE;
}

/* child function */
int child(struct test_primes *t, pipe_t *p, int child_n, int child_id) {
	int i;
	
	/* close unused pipe sides (shared with father)*/
	for (i = 0; i < child_n; i++) {
		if (i != child_id) {
			close(p[i*2][0]);
			close(p[i*2][1]);
			close(p[i*2+1][0]);
			close(p[i*2+1][1]);
		} else {
			close(p[i*2][1]);
			close(p[i*2+1][0]);
		}
	}

	/* read from nephew */
	if (read(p[child_id*2][0], t, sizeof(struct test_primes)) != sizeof(struct test_primes)) {
		zprintf(1, "[%d] read() failed\n", getpid());
		exit(1);
	}

	/* computation */
	for (i = 0; i < NPRIMES; i++) {
		t->is_prime[i] = is_prime(i);
	}
	
	/* write number of lines to father */
	if (write(p[child_id*2+1][1], t, sizeof(struct test_primes)) != sizeof(struct test_primes)) {
		zprintf(1, "[%d] write() failed\n", getpid());
		exit(1);
	}

	exit(0);
}

/* father function */
int father(struct test_primes *t, pipe_t *p, int child_n) {
	int i, j;
	
	/* close unused pipe sides */
	for (i = 0; i < child_n; i++) { 
		close(p[i*2][0]);
		close(p[i*2+1][1]);
	}

	/* fill struct test primes */
	for (i = 0; i < NPRIMES; i++) {
		t->numbers[i] = i;
		t->is_prime[i] = 0;
	}

	/* write number of lines to father */
	for (i = 0; i < child_n; i++) {	
		if (write(p[i*2][1], t, sizeof(struct test_primes)) != sizeof(struct test_primes)) {
			zprintf(1, "[%d] write() failed\n", getpid());
			exit(1);
		}
	}
	
	/* wait for number of lines */		
	for (i = 0; i < child_n; i++) {	
		if (read(p[i*2+1][0], t, sizeof(struct test_primes)) != sizeof(struct test_primes)) {
			zprintf(1, "[%d] read() failed\n", getpid());
			exit(1);
		}

		/* show results */
		for (j = 0; j < NPRIMES; j++) {
			zprintf(1, "[%d] received from child=%d (%d, %d)\n", getpid(), i, t->numbers[j], t->is_prime[j]);
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
	struct test_primes t;
	
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
	p = (pipe_t *) malloc(2 * sizeof(pipe_t) * (child_n));
	if (p == NULL) {
		zprintf(1, "[%d] error malloc()\n", getpid());
		exit(1);
	}
	
	/* init pipes */
	for (i = 0; i < 2 * child_n; i++) { 
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