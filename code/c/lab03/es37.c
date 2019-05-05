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
            |
            | 
     | ---> | <---|
   p0|    p1|   p2|
     V      V     V 
    c0     c1    c2
    
*/

/* when multiple pipes are needed this definition is useful */
typedef int pipe_t[2];

/* child function */
int child(struct test_pipe *t, pipe_t *p, int child_n, int child_id) {
    int i;
    char cmd;

    zprintf(1, "[%d] child started...\n", getpid());
    
    /* close unused pipe sides */
    for (i = 0; i < child_n; i++) { 
        close(p[i][1]); 
        if (i != child_id) close(p[i][0]); 
    }
    
    /* wait for command */          
    if (read(p[child_id][0], &cmd, 1) != 1) {
        zprintf(1, "[%d] read() failed\n", getpid());
        exit(EXIT_FAILURE);
    }
    
    zprintf(1, "[%d] command (%c) received\n", getpid(), cmd);
    exit(EXIT_SUCCESS);
}


/* father function */
int father(struct test_pipe *t, pipe_t *p, int child_n) {
    int i;
    char cmd = 'a';

    zprintf(1, "[%d] father started...\n", getpid());
    
    /* close unused pipe sides */
    for (i = 0; i < child_n; i++) { 
        close(p[i][0]); 
    }
    
    for (i = 0; i < child_n ; i++) { 
        zprintf(1, "[%d] writing to child %d...\n", getpid(), i);
        if (write(p[i][1], &cmd, 1) != 1) {
            zprintf(1, "[%d] write() failed\n", getpid());
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
    int i, child_n;
    pid_t pid;
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

