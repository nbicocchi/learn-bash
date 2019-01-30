#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <sys/wait.h>
#include "utils.h"

/* child function */
int child(struct test_pipe *t, int *p) {

	/* close write-side pipe */
	close(p[1]);

	/* read from pipe */
	if (read(p[0], t, sizeof(struct test_pipe)) != sizeof(struct test_pipe)) {
		zprintf(2, "error: read()\n");
		exit(1);
	}
		
	/* debug */
	zprintf(1, "[%d] (read) completed!\n", getpid());
	zprintf(1, "[%d] cid = %d\n", getpid(), t->child_id);
	zprintf(1, "[%d] pid = %d\n", getpid(), t->process_id);
	zprintf(1, "[%d] data = %f, %f\n", getpid(), t->data[0], t->data[1]);
	zprintf(1, "[%d] message = %s\n", getpid(), t->msg);
	exit(0);
}

/* father function */
int father(struct test_pipe *t, int *p) {
	int status;
	
	/* close read-side pipe */
	close(p[0]);
	
	/* fill data structure */
	fill_test_pipe(t, 18, getpid(), 7.2, 8.3, "Hello World!");
	
	/* write on pipe */
	if (write(p[1], t, sizeof(struct test_pipe)) != sizeof(struct test_pipe)) {
		zprintf(2, "error: write()\n");
		exit(1);
	}
		
	/* debug */
	zprintf(1, "[%d] (write) completed!\n", getpid());
	
	/* wait child before exit */
	wait(&status);
	exit(0);
}

int main(int argc, char **argv) {
	int pid;
	int p[2];
	struct test_pipe t;
	
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
			child(&t, p);
	}
	
	father(&t, p);
}
