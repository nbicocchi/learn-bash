#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <sys/wait.h>
#include "utils.h"

#define SLOTS 16

/* child function */
int child(int *v, int *p) {
    int i;

    zprintf(1, "[%d] child started...\n", getpid());
    
    /* close write-side pipe */
    close(p[1]);
    
    for (i = 0; i < SLOTS; i++) {
        /* read from pipe */
        if (read(p[0], &v[i], sizeof(int)) != sizeof(int)) {
            zprintf(1, "error: read()\n");
            exit(EXIT_FAILURE);
        }
        
        /* debug */
        zprintf(1, "[%d] (read) v[%d] = %d\n", getpid(), i, v[i]);
    }
    exit(EXIT_SUCCESS);
}

/* father function */
int father(int *v, int *p) {
    int i;

    zprintf(1, "[%d] father started...\n", getpid());

    /* close read-side pipe */
    close(p[0]);
    
    /* Initialize random numbers generator */
    srand(9786875L);
    
    sleep(1);
        
    for (i = 0; i < SLOTS; i++) {
        /* generate random number */
        v[i] = rand() % 10;
        
        /* write on pipe */
        if (write(p[1], &v[i], sizeof(int)) != sizeof(int)) {
            zprintf(1, "error: write()\n");
            exit(EXIT_FAILURE);
        }
        
        /* debug */
        zprintf(1, "[%d] (write) v[%d] = %d\n", getpid(), i, v[i]);
    }
    
    /* wait child before exit */
    wait_child();
    exit(EXIT_SUCCESS);
}

int main(int argc, char **argv) {
    pid_t pid;
    int p[2];
    int v[SLOTS];
    
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
            child(v, p);
    }
    father(v, p);
}
