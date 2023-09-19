#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "../utils/utils.h"

int read_bytes(int fd) {
    int n = 0;
    char buf;
    
    while (read(fd, &buf, 1) > 0) n++;
    return n;
}

int main(int argc, char **argv) {
    char *usage = "usage: %s filename\n";
    pid_t pid;
    int fd;
    
    if (argc != 2) {
        zprintf(2, usage, argv[0]);
        exit(EXIT_FAILURE);
    } 
    
    fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        zprintf(2, "error: open()\n");
        exit(EXIT_FAILURE);
    } 
    
    pid = fork();
    switch (pid) {
        case -1: /* error */
            zprintf(2, "error: fork()\n");
            exit(EXIT_FAILURE);
        case 0: /* child */
            zprintf(1, "[%d] Child started...\n", getpid());
            zprintf(1, "[%d] Child counted %d bytes\n", getpid(), read_bytes(fd));
            exit(EXIT_SUCCESS);
    }
    
    /* father */   
    zprintf(1, "[%d] Father started...\n", getpid());     
    zprintf(1, "[%d] Father counted %d bytes\n", getpid(), read_bytes(fd));
    wait_child();
    exit(EXIT_SUCCESS);
}
