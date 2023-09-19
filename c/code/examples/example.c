#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int main(void) {
    char str[1024];
    sprintf(str, "%f;%f;%f", 3.3, 5.66, 3.44);
    fwrite((void *)str, strlen(str), 1, stdout)
}