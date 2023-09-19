#include <stdio.h>
#include <string.h>
#define FIELD_LEN 30

struct person {
    char name[FIELD_LEN];
    char lastname[FIELD_LEN];
    double age;
};

void init_person(struct person *person, char *name, char *lastname, double age) {
    strncpy(person->name, name, FIELD_LEN);
    strncpy(person->lastname, lastname, FIELD_LEN);
    person->age = age;
}

void show_person(struct person *person) {
    printf("name: %s, lastname: %s, age: %lf\n", person->name, person->lastname, person->age);
}

int main(void) {
    struct person p;
    init_person(&p, "john", "doe", 33.3);
    show_person(&p);
}




