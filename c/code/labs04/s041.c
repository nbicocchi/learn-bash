#include <stdlib.h>
#include <unistd.h>
#include "../utils/utils.h"

int main(int argc, char **argv) {
    zprintf(1, "Hello ");
    sleep(3);
    zprintf(1, "World\n");
    exit(EXIT_SUCCESS);
}

