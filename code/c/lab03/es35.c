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
    zprintf(1, "[%d] child started...\n", getpid());

    /* close unused pipe sides */
    close(p[0]); 
    
    /* filling data structure */
    fill_test_pipe(t, 0, getpid(), 2.2, 2.3, "System OK!");
    
    /* writing phase */
    zprintf(1, "[%d] writing...\n", getpid());          
    if (write(p[1], t, sizeof(struct test_pipe)) != sizeof(struct test_pipe)) {
        zprintf(1, "[%d] write() failed\n", getpid());
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}

/* father function */
int father(struct test_pipe *t, int *p, int child_n) {
    int i;

    zprintf(1, "[%d] father started...\n", getpid());
    
    /* close unused pipe sides */
    close(p[1]); 
    
    for (i = 0; i < child_n; i++) { 
        /* clear data structure */
        clear_test_pipe(t);
        
        /* read data 
         * write() is atomic. read() can 
         * (a) return a complete data structure 
         * (b) suspend the process until data is available
         * (c) return 0 for indicating that no one can write on the pipe
         */
        if (read(p[0], t, sizeof(struct test_pipe)) != sizeof(struct test_pipe)) {
            zprintf(1, "[%d] error read()\n", getpid());
            exit(EXIT_FAILURE);
        }

        zprintf(1, "[%d] cid = %d\n", getpid(), t->child_id);
        zprintf(1, "[%d] pid = %d\n", getpid(), t->process_id);
        zprintf(1, "[%d] data = %f, %f\n", getpid(), t->data[0], t->data[1]);
        zprintf(1, "[%d] message = %s\n", getpid(), t->msg);
    }
    
    /* wait child before exit */
    for (i = 0; i < child_n; i++) {
        wait_child();
    }
    exit(EXIT_SUCCESS);
}


/* main function */
int main(int argc, char **argv) {
    char *usage = "usage: %s nchildren\n";
    pid_t pid;
    int i, child_n;
    int p[2];
    struct test_pipe t;
    
    /* arguments check */
    if (argc != 2) {
        zprintf(1, usage, argv[0]);
        exit(EXIT_FAILURE);
    }
    
    /* get child_n from command line */
    child_n = atoi(argv[1]);
    if (child_n <= 0) { 
        zprintf(1, usage, argv[0]);
        exit(EXIT_FAILURE);
    }
    
    /* init pipe */
    if (pipe(p) != 0) { 
        zprintf(1, "[%d] error pipe()\n", getpid());
        exit(EXIT_FAILURE);
    }
    
    /* init child processes */
    for (i=0; i < child_n; i++) { 
        pid=fork(); 
        switch(pid) {
            case -1:
                zprintf(1, "[%d] error fork()\n", getpid());
                exit(EXIT_FAILURE);
            case 0: 
                child(&t, p);
        }
    }
    father(&t, p, child_n);
}

