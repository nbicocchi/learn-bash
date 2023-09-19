#include <stdio.h>

void *my_memcpy(void *dst, void *src, size_t size) {
    unsigned long i;
    for (i = 0; i < size; i++) {
        *((char *)dst + i) = *((char *)src + i);
    }
    return dst;
}

void *my_memmove(void *dst, void *src, size_t size) {
    char buffer[size];
    my_memcpy(buffer, src, size);
    my_memcpy(dst, buffer, size);
    return dst;
}

void show_array(int *src, size_t size) {
    unsigned long i;
    for (i = 0; i < size; i++) {
        printf("%d ", src[i]);
    }
    printf("\n");
}

int main(void) {
    int src[8] = {0,1,2,3,4,5,6,7};

    show_array(src, sizeof(src) / sizeof(*src));
    my_memcpy(src + 4, src + 2, 4 * sizeof(*src));
    show_array(src, sizeof(src) / sizeof(*src));
}
