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
    pid_t pid;
    int n = 1;
    int i;
    int opt;

    for (;;) {
        opt = getopt(argc, argv, "n:");
        if (opt == -1) break;
        switch (opt) {
            case 'n':
                n = atoi(optarg);
                break;
        }
    }
    
    for (i = 0; i < n; i++) {
        pid = fork();
        switch (pid) {
            case -1: /* error */
                zprintf(2, "error: fork()\n");
                exit(EXIT_FAILURE);
            case 0: /* child */
                child(i);
        }
    }
    
    /* father */
    zprintf(1, "[%d] Father started...\n", getpid());
    for (i = 0; i < n; i++) {
        wait_child();
    }
    exit(EXIT_SUCCESS);
}
