#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define SIZE 128

void frequencies(unsigned *freqs, const char *src) {
    unsigned long len;

    for (unsigned long i = 0; i < 26; i++) {
        freqs[i] = 0;
    }

    len = strlen(src);
    for (unsigned long i = 0; i < len; i++) {
        if (isalpha(src[i])) {
            freqs[tolower(src[i]) - 'a'] += 1;
        }
    }
}

int main(void) {
    char src[SIZE] = "Give a man a fish and you feed him for a day; teach a man to fish and you feed him for a lifetime.";
    unsigned freqs[26];

    frequencies(freqs, src);
    for (int i = 0; i < 26; i++) {
        printf("%c: %d\n", 'a' + i, freqs[i]);
    }

}