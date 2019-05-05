#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "utils.h"

char msg[] = "Hello World!";
char msg2[256];

int main(int argc, char **argv) {
    int p[2]; 
    int nw, nr;
    
    if (pipe(p) != 0) {
        zprintf(1, "[%d] error: pipe()\n", getpid());
        exit(EXIT_FAILURE);
    }
    
    zprintf(1, "[%d] p[0]=%d, p[1]=%d\n", getpid(), p[0], p[1]);
    
    /* use this line for changing behaviour */
    close(p[0]);
    
    switch (fork()) {
        case -1: 
            zprintf(1, "[%d] error: fork()\n", getpid());
            exit(EXIT_FAILURE);
        case 0: 
            zprintf(1, "[%d] child started...\n", getpid());
            nw = write(p[1], msg, strlen(msg)); 
            nr = read(p[0], msg2, sizeof(msg2));
            zprintf(1, "[%d] [nr=%d] [nw=%d] msg received: %s\n", getpid(), nr, nw, msg2);
            exit(EXIT_SUCCESS);
    }
    
    /* father */
    zprintf(1, "[%d] father started...\n", getpid());
    wait_child();
    exit(EXIT_SUCCESS);
}

