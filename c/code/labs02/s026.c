#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "../utils/utils.h"

void child(int index, int argc, char **argv) {
    zprintf(1, "[%d] Child %d started...\n", getpid(), index);
    zprintf(1, "[%d] executing %s...\n", getpid(), argv[1]);
    execlp(argv[1], argv[1], (char *)0); 
    zprintf(2, "error: exec()\n");
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
    char *usage = "usage: %s cmd\n";
    pid_t pid;
    
    if (argc != 2) {
        zprintf(2, usage, argv[0]);
        exit(EXIT_FAILURE);
    } 

    pid = fork();
    switch (pid) {
        case -1: /* error */
            zprintf(2, "error: fork()\n");
            exit(EXIT_FAILURE);
        case 0: /* child */
            child(0, argc, argv);
    }
    
    /* father */
    zprintf(1, "[%d] Father started...\n", getpid());
    wait_child();
    exit(EXIT_SUCCESS);
}

