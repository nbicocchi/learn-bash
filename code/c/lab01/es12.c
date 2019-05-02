#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int n = 8;
    char c = 'M';
    char *str = "Hello World";
    
    fprintf(stdout, "[int] %d\n", n);
    fprintf(stdout, "[char] %c\n", c);
    fprintf(stdout, "[char *] %s\n", str);
    
    exit(0);
}
