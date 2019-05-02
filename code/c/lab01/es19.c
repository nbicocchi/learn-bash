#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include "utils.h"

int main (int argc, char **argv) {
    char c, *usage = "usage: %s f1 .. fn (n must be even)\n";
    int i, n, *fd;
    
    /* checking command line parameters */
    if (argc < 2 || (argc - 1) % 2 != 0) {
        zprintf(2, usage, argv[0]);
        exit(1);
    }

    /* allocating array for file descriptors */
    fd = (int *)malloc((argc - 1) * sizeof(int));
    if (fd == NULL) {
        zprintf(2, "error: malloc()\n");
        exit(1);
    }

    /* opening files */
    for (i = 0; i < argc - 1; i++) {
    	zprintf(1, "f=%s\n", argv[i+1]);
        if ((fd[i] = open(argv[i+1], O_RDONLY)) < 0) {
            zprintf(2, "error: open()\n");
            exit(1);
        }
    }

    /* reading chars */
    for (i = 0; i < (argc - 1) / 2; i++) {
        lseek(fd[i], (long) i, SEEK_SET);
        n = read(fd[i], &c, 1);
        if (n != 1) break;
        write(1, &c, 1);

        lseek(fd[argc - i - 2], -(long) (i + 1), SEEK_END);
        n = read(fd[argc - i - 2], &c, 1);
        if (n != 1) break;
        write(1, &c, 1);
    }

    /* closing files */
    for (i = 0; i < argc - 1; i++) {
        close(fd[i]);
    }

    /* exit */
    if (n != 1) exit(1);
    exit(0);
}
