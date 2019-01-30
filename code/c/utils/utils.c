#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include "utils.h"

/* Fill struct test_pipe using parameters */
void fill_test_pipe(struct test_pipe *t, int cid, int pid, float d0, float d1, char *msg) {
	t->child_id = cid;
	t->process_id = pid;
	t->data[0] = d0;
	t->data[1] = d1;
	strncpy(t->msg, msg, STRLEN);
}

/* Clear struct test_pipe */
void clear_test_pipe(struct test_pipe *t) {
	memset(t, 0, sizeof(struct test_pipe));
}

/*
 * Formatted write() funtion. Useful for writing 
 * compact low-lowel code internally using write()
 * Example: zprintf(1, "argc = %d\n", argc);
 */
void zprintf(int fd, const char *fmt, ...) {
	static char msg[1024];
	int n;
	va_list ap;
	
	va_start(ap, fmt);
	n = vsnprintf(msg, 1024, fmt, ap);
	n = write(fd, msg, n);
	va_end(ap);
}

