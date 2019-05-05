#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <sys/wait.h>
#include "utils.h"

/* child function */
int child(struct test_pipe *t, int *p) {
    zprintf(1, "[%d] child started...\n", getpid());

    /* close write-side pipe */
    close(p[1]);

    /* read data 
     * write() is atomic. read() can 
     * (a) return a complete data structure 
     * (b) suspend the process until data is available
     * (c) return 0 for indicating that no one can write on the pipe
     */
    if (read(p[0], t, sizeof(struct test_pipe)) != sizeof(struct test_pipe)) {
        zprintf(1, "error: read()\n");
        exit(EXIT_FAILURE);
    }
        
    /* debug */
    zprintf(1, "[%d] (read) completed!\n", getpid());
    zprintf(1, "[%d] cid = %d\n", getpid(), t->child_id);
    zprintf(1, "[%d] pid = %d\n", getpid(), t->process_id);
    zprintf(1, "[%d] data = %f, %f\n", getpid(), t->data[0], t->data[1]);
    zprintf(1, "[%d] message = %s\n", getpid(), t->msg);
    exit(EXIT_SUCCESS);
}

/* father function */
int father(struct test_pipe *t, int *p) {
    zprintf(1, "[%d] father started...\n", getpid());
    
    /* close read-side pipe */
    close(p[0]);
    
    /* fill data structure */
    fill_test_pipe(t, 18, getpid(), 7.2, 8.3, "Hello World!");
    
    /* write on pipe */
    if (write(p[1], t, sizeof(struct test_pipe)) != sizeof(struct test_pipe)) {
        zprintf(1, "error: write()\n");
        exit(EXIT_FAILURE);
    }
        
    /* debug */
    zprintf(1, "[%d] (write) completed!\n", getpid());
    
    /* wait child before exit */
    wait_child();
    exit(EXIT_SUCCESS);
}

int main(int argc, char **argv) {
    pid_t pid;
    int p[2];
    struct test_pipe t;
    
    /* shared pipe */
    if (pipe(p) < 0) {
        zprintf(1, "error: pipe()\n");
        exit(EXIT_FAILURE);
    }
    
    /* fork process */
    pid = fork();
    switch (pid) {
        case -1: /* error */
            zprintf(1, "error: fork()\n");
            exit(EXIT_FAILURE);
        case 0: /* child */
            child(&t, p);
    }
    father(&t, p);
}
