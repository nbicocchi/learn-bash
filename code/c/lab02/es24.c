#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include "utils.h"

int child(int index) {
    zprintf(1, "[%d] Child %d started...\n", getpid(), index);
    exit(EXIT_SUCCESS);
}

int main(int argc, char **argv) {
    pid_t pid, *pids;
    int n = 1, i, opt, status;

    for (;;) {
        opt = getopt(argc, argv, "n:");
        if (opt == -1) break;
        switch (opt) {
            case 'n':
                n = atoi(optarg);
                break;
        }
    }
    
    pids = (pid_t *)malloc(sizeof(pid_t) * n);
    for (i = 0; i < n; i++) {
        pids[i] = fork();
        switch (pids[i]) {
            case -1: /* error */
                zprintf(2, "error: fork()\n");
                exit(EXIT_FAILURE);
            case 0: /* child */
                child(i);
        }
    }
    
    /* father */
    zprintf(1, "[%d] Father started...\n", getpid());
    for (i = n - 1; i >= 0; i--) {
        if ((pid = waitpid(pids[i], &status, 0)) == -1 ) {
            zprintf(1, "[%d] error: wait()", getpid());
            exit(EXIT_FAILURE);
        }
        if (WIFEXITED(status)) {
            zprintf(1, "[%d] child pid=%d exit=%d (normal)\n", getpid(), pid, WEXITSTATUS(status));
        }
        else if (WIFSIGNALED(status)) {
            zprintf(1, "[%d] child pid=%d signal=%d (terminated)\n", getpid(), pid, WTERMSIG(status));
        }
        else if (WIFSTOPPED(status)) {
            zprintf(1, "[%d] child pid=%d signal=%d (stopped)\n", getpid(), pid, WSTOPSIG(status));
        }
    }
    free(pids);
    exit(EXIT_SUCCESS);
}
