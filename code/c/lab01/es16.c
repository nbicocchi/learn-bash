#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "utils.h"

int main(int argc, char **argv) {
    char *usage = "usage: %s n filename n\n";
    int fd, n, k;
    char *f, buffer[256];
    
    /* check parameters number */
    if (argc != 4) {
        zprintf(2, usage, argv[0]);
        exit(1);
    } 
    
    /* acquiring parameters */
    n = atoi(argv[1]);
    f = argv[2];
    k = atoi(argv[3]);
    
    /* limit n */
    if (n >= 100) n = 99; 
    
    fd = open(f, O_RDWR);
    if (fd < 0) {
        zprintf(2, "error: open()\n");
        exit(1);
    }
    
    if (read(fd, buffer, n) != n) {
        zprintf(2, "error: read()\n");
        exit(1);
    }
    
    if (lseek(fd, k, SEEK_SET) != k) {
        zprintf(2, "error: fseek()\n");
        exit(1);
    }
    
    if (write(fd, buffer, n) != n) {
        zprintf(2, "error: write()\n");
        exit(1);
    }
    
    if (close(fd) != 0) {
        zprintf(2, "error: close()\n");
        exit(1);
    }
    
    exit(0);
}

