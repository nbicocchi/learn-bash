#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "utils.h"

int main(int argc, char **argv) {
    char *usage = "usage: %s n\n";
    int n, fdout = 1;
    
    if (argc != 2) {
        zprintf(2, usage, argv[0]);
        exit(1);
    } 
    
    n = atoi(argv[1]);
    if (n == 2) fdout = 2;
    
    zprintf(fdout, "Hello World [%d]!\n", fdout);
    
    exit(0);
}
