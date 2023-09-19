#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "../utils/utils.h"

int main(int argc, char **argv) {
	char *usage = "usage: %s [n] [filename]\n";
    char c;
    int lines = 0, fdin = 0, fdout = 1, n = 10;

    if (argc > 3) {
        zprintf(2, usage, argv[0]);
        exit(1);
    }

    if (argc == 2) n = atoi(argv[1]);
    if (argc == 3) fdin = open(argv[2], O_RDONLY);

    while(read(fdin, &c, 1) > 0) {
        write(fdout, &c, 1);
        if (c == '\n') lines++;
        if (lines >= n) break;
    }     
    
    exit(0);
}
