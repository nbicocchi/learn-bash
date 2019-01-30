#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    char c;
    int lines = 0, fdin = 0, fdout = 1, n = 10;

    if (argc > 1) n = atoi(argv[1]);
    if (argc > 2) fdin = open(argv[2], O_RDONLY);

    while(read(fdin, &c, 1) > 0) {
        write(fdout, &c, 1);
        if (c == '\n') lines++;
        if (lines >= n) break;
    }     
    
    exit(0);
}
