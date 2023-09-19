#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "../utils/utils.h"

int main(int argc, char **argv) {
    char *usage = "usage: %s string\n";
    int i;
    char c;
    int counter[256];
    
    if (argc != 2) {
        zprintf(2, usage, argv[0]);
        exit(1);
    }
    
    for (i = 0; i < strlen(argv[1]); i++) {
        counter[(int)argv[1][i]]++;
    }
    
    for (;;) {
        if (read(0, &c, 1) != 1) break;
        if (counter[(int)c] != 1) write(1, &c, 1);
    }
    
    exit(0);
}
