#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "utils.h"

int main(int argc, char **argv) {
    pid_t pid;
    int status;
    
    pid = fork();
    switch (pid) {
        case -1: /* error */
            zprintf(2, "error: fork()\n");
            exit(EXIT_FAILURE);
        case 0: /* child */
            zprintf(1, "[%d] Hello, I'm the child! [fork()=%d]\n", getpid(), pid);
            exit(EXIT_SUCCESS);
    }

    /* father */
    zprintf(1, "[%d] Hello, I'm the father! [fork()=%d]\n", getpid(), getpid(), pid);
    if ((pid = wait(&status)) == -1) {
        zprintf(2, "error: wait()\n");
        exit(EXIT_FAILURE);
    } 
    if (!WIFEXITED(status)) {
        zprintf(1, "[%d] Child %d exited abnormally\n", pid);
        exit(EXIT_FAILURE);
    }
    zprintf(1, "[%d] Child exited %d\n", getpid(), WEXITSTATUS(status));
    exit(EXIT_SUCCESS);
}


