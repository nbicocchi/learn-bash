#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "../utils/utils.h"

int read_bytes(char *filename) {
    int fd, n = 0;
    char buffer;

    /* open file for reading */
    fd = open(filename, O_RDONLY);
    if (fd < 0) {
        zprintf(2, "error: open()\n");
        exit(EXIT_FAILURE);
    }

    /* count bytes */
    while (read(fd, &buffer, 1) > 0) n++;
    return n;
}

void child(int index, int argc, char **argv) {
    zprintf(1, "[%d] Child %d started...\n", getpid(), index);
    zprintf(1, "[%d] Child counted %d bytes\n", getpid(), read_bytes(argv[1]));
    exit(EXIT_SUCCESS);
}

int main(int argc, char **argv) {
    char *usage = "usage: %s filename\n";
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
    zprintf(1, "[%d] Father counted %d bytes\n", getpid(), read_bytes(argv[1]));
    wait_child();
    exit(EXIT_SUCCESS);
}
