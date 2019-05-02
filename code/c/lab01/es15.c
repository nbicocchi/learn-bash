#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "utils.h"

int main(int argc, char **argv) {
    char *usage = "usage: %s filename\n";
    int fd;
    char buf[] = "Hello";
    
    if (argc != 2) {
        zprintf(2, usage, argv[0]);
        exit(1);
    } 
    
    fd = open(argv[1], O_WRONLY);
    if (fd < 0) {
        zprintf(2, "error: open()\n");
        exit(1);
    }
    
    if (write(fd, buf, 5) != 5) {
        zprintf(2, "error: write()\n");
        exit(1);
    }
    
    if (ftruncate(fd, 16) != 0) {
        zprintf(2, "error: ftruncate()\n");
        exit(1);
    }
    
    if (close(fd) != 0) {
        zprintf(2, "error: close()\n");
        exit(1);
    }
    
    exit(0);
}