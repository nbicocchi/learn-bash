#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "../utils/utils.h"

int terminated = 0;

void sig_usr1_handler(int s) {
        zprintf(1, "received SIGUSR1!\n");
}

void sig_usr2_handler(int s) {
        zprintf(1, "received SIGUSR2! quitting...!\n");
        terminated = 1;
}

/* child function */
int child() {
    zprintf(1, "[%d] child started...\n", getpid());
    signal(SIGUSR1, sig_usr1_handler);
    signal(SIGUSR2, sig_usr2_handler);
    
    while(!terminated) {
        /* avoids cpu waste */
        sleep(1);
    }
    exit(EXIT_SUCCESS);
}


/* father function */
int father(int child_n, int *pids) {
    int i;

    zprintf(1, "[%d] father started...\n", getpid());
    
    /* wait for children */
    sleep(1);
    
    for (i = 0; i < child_n ; i++) { 
        zprintf(1, "[%d] sending SIGUSR1 to child (%d, %d)...\n", getpid(), i, pids[i]);
        kill(pids[i], SIGUSR1);
    }
    
    /* wait for children */
    sleep(1);
    
    for (i = 0; i < child_n ; i++) { 
        zprintf(1, "[%d] sending SIGUSR2 to child (%d, %d)...\n", getpid(), i, pids[i]);
        kill(pids[i], SIGUSR2);
    }
    
    /* wait child before exit */
    for (i = 0; i < child_n ; i++) { 
        wait_child();
    }
    exit(EXIT_SUCCESS);
}


/* main function */
int main(int argc, char **argv) {
    pid_t *pids;
    int i, child_n;
    
    /* arguments check */
    if (argc != 2) {
        zprintf(1, "error: %s n_children\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    /* get child_n from command line */
    child_n = atoi(argv[1]);
    if (child_n <= 0) { 
        zprintf(1, "error: n_children must be positive\n");
        exit(EXIT_FAILURE);
    }
    
    /* allocate memory for pids */
    pids = (int *)malloc(sizeof(int) * child_n);
    
    /* init child processes */
    for (i=0; i < child_n; i++) { 
        pids[i] = fork(); 
        switch(pids[i]) {
            case -1:
                zprintf(1, "[%d] error fork()\n", getpid());
                exit(EXIT_FAILURE);
            case 0: 
                child();
        }
    }
    father(child_n, pids);
}

