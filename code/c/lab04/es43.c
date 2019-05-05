#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "utils.h"

char msg[] = "Hello World!";
char msg2[256];

void sig_handler(int s) {
    zprintf(1, "[%d] received signal %d\n", getpid(), s);
    return;
}

int main(int argc, char **argv) {
    int p[2]; 
    int nw, nr;
    int status;
    int pid;
    
    if (pipe(p) != 0) {
        zprintf(1, "[%d] error: pipe()\n", getpid());
        exit(EXIT_FAILURE);
    }
    
    zprintf(1, "[%d] p[0]=%d, p[1]=%d\n", getpid(), p[0], p[1]);
    
    /* comment this line to change behaviour */
    close(p[0]);
    
    switch (fork()) {
        case -1: 
            zprintf(1, "[%d] error: fork()\n", getpid());
            exit(EXIT_FAILURE);
        case 0: 
            zprintf(1, "[%d] child started...\n", getpid());
            signal(SIGPIPE, sig_handler);
            nw = write(p[1], msg, strlen(msg));
            nr = read(p[0], msg2, sizeof(msg2));
            
            zprintf(1, "[%d] [nr=%d] [nw=%d] msg received: %s\n", getpid(), nr, nw, msg2);
            exit(EXIT_SUCCESS);
    }
    
    /* father */
    zprintf(1, "[%d] father started...\n", getpid());
    if ((pid = wait(&status)) == -1) {
        zprintf(1, "error: wait()\n");
        exit(EXIT_FAILURE);
    }
    if (!WIFEXITED(status)) {
        zprintf(1, "[%d] Child exited abnormally signal=%d\n", pid, WTERMSIG(status));
        exit(EXIT_FAILURE);
    }
    zprintf(1, "[%d] Child pid=%d exit=%d\n", getpid(), pid, WEXITSTATUS(status));
    exit(EXIT_SUCCESS);
}

