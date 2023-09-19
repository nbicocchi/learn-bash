#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../utils/utils.h"

int main(int argc, char **argv) {
    pid_t pid;
    
    pid = fork();
    switch (pid) {
        case 0: /* child */
            zprintf(1, "[%d] Hello, I'm the child! [fork()=%d]\n", getpid(), pid);
            exit(EXIT_SUCCESS);
        default: /* father */
            zprintf(1, "[%d] Hello, I'm the father! [fork()=%d]\n", getpid(), pid);
            exit(EXIT_SUCCESS);
    }
}

