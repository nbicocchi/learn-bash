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

    zprintf(1, "[%d] child started...\n", getpid());
    
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
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}


/* father function */
int father(struct test_pipe *t, pipe_t *p, int child_n) {
    int i;
    int nr;

    zprintf(1, "[%d] father started...\n", getpid());
    
    /* close unused pipe sides */
    for (i = 0; i < child_n; i++) { 
        close(p[i][1]); 
    }
    
    for (i = child_n - 1; i >= 0; i--) { 
        /* clear data structure */
        clear_test_pipe(t);
        
        /* read data 
         * considerata l'atomicità di write(), il processo 
         * (a) o legge una struttura dati intera, 
         * (b) o si sospende fino al momento opportuno,
         * (c) o ottiene 0 per indicare che la pipe ha il lato scrittura chiuso
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
                exit(EXIT_FAILURE);
        }
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
    pipe_t *p;
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
    
    /* allocate memory for pipes */
    p = (pipe_t *) malloc(sizeof(pipe_t) * child_n);
    if (p == NULL) {
        zprintf(1, "[%d] error malloc()\n", getpid());
        exit(EXIT_FAILURE);
    }
    
    /* init pipes */
    for (i = 0; i < child_n; i++) { 
        if (pipe(p[i]) < 0) { 
            zprintf(1, "[%d] error pipe()\n", getpid());
            exit(EXIT_FAILURE);
        }
    }
    
    /* init child processes */
    for (i=0; i < child_n; i++) { 
        pid=fork(); 
        switch(pid) {
            case -1:
                zprintf(1, "[%d] error fork()\n", getpid());
                exit(EXIT_FAILURE);
            case 0: 
                child(&t, p, child_n, i);
        }
    }
    father(&t, p, child_n);
}

