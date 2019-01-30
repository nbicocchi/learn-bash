#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include "utils.h"

/* Reads a char from a file
 * @param filename, name of the file
 * @param index, index of the char to be read
 * @param side, side of the file (SEEK_SET, SEEK_END)
 */ 
char read_char(char *filename, int index, int side) {
    char c;
    int nr;
    int fd;
    
    /* apertura file */
    if ((fd = open(filename, O_RDONLY)) < 0) {
        zprintf(2, "error: open()\n");
        exit(1);
    }
    
    /* spostamento all'interno del file */
    if (side == SEEK_SET) {
        lseek(fd, (long) index, SEEK_SET);
    } else if (side == SEEK_END) {
        lseek(fd, -(long) (index + 1), SEEK_END);
    }
    
    /* lettura di un byte */
    nr = read(fd, &c, 1);
    if (nr != 1) {
        zprintf(2, "error: read()\n");
        exit(1);
    }
    
    /* chiusura file */
    close(fd);
    
    return c;
}

int main (int argc, char **argv) {
    char *usage = "usage: %s f1 .. fn (n must be even)\n";
    char c;
    int i;
    
    if (argc < 2) {
        zprintf(2, usage, argv[0]);
        exit(1);
    }
    
    if (((argc - 1) % 2) != 0) {
        zprintf(2, usage, argv[0]);
        exit(1);
    }
    
    for (i = 0; i < (argc - 1) / 2; i++) {
        c = read_char(argv[i + 1], i , SEEK_SET);
        write(1, &c, 1);
        
        c = read_char(argv[argc - i - 1], i , SEEK_END);
        write(1, &c, 1);
    }
    
    exit(0);
}
