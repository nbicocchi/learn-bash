#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* trim spaces both at the beginning and at the end of the string */
void trim(char *str) {
    long length = (unsigned)strlen(str), trimmed_length;
    char *begin = str, *end = str + length - 1;

    while(isspace((unsigned char)*begin)) begin++;
    end = str + length - 1;
    while(end > str && isspace((unsigned char)*end)) end--;
    trimmed_length = end - begin + 1;

    memmove(str, begin, trimmed_length);
    memset(str + trimmed_length, 0, length - trimmed_length);
}

/* count the number of space separated words in a string */
unsigned word_count(const char *s) {
    unsigned count = 0, length, i;

    length = (unsigned) strlen(s);
    for (i = 0; i < length; i++) {
        if (isspace(s[i])) count++;
    }
    return count + 1;
}

/* splits the string str into an array of strings */
char **split(const char *str) {
    int index = 0;
    char *copy, *ptr, **list;
    unsigned words;

    /* create a copy of str because of strtok modifies the passed string */
    copy = strdup(str);
    trim(copy);

    words = word_count(copy);
    /* allocate the NULL-terminated list of pointers */
    list = malloc((words + 1) * sizeof(*list));
    if (!list) return NULL;
    list[words] = NULL;

    ptr = strtok(copy, " ");
    while (ptr != NULL) {
        /* allocate each string */
        list[index] = malloc((strlen(ptr) + 1) * sizeof(**list));
        if (!list[index]) return NULL;

        strcpy(list[index], ptr);
        index++;

        ptr = strtok(NULL, " ");
    }
    free(copy);
    return list;
}

int main(void) {
    char **list, str[] = "   Rosso di sera bel tempo si spera    ";
    int i;

    list = split(str);

    /* show the result */
    for (i = 0; list[i] != NULL; i++) {
        printf("%s\n", list[i]);
    }

    /* free actual strings */
    for (i = 0; list[i] != NULL; i++) {
        free(list[i]);
    }

    /* free array of char pointers */
    free(list);
}