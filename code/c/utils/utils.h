#ifndef UTILS_INCLUDED
#define UTILS_INCLUDED

/* Human readable boolean constants */
#define TRUE 1
#define FALSE 0

/* Example data structures to be to be used in exercises */
#define STRLEN 256
struct test_pipe {
    int child_id;
    int process_id;
    float data[2];
    char msg[STRLEN];
};

#define NPRIMES 8
struct test_primes {
    int numbers[NPRIMES];
    char is_prime[NPRIMES];
};

void fill_test_pipe(struct test_pipe *t, int cid, int pid, float d0, float d1, char *msg);
void clear_test_pipe(struct test_pipe *t);
void zprintf(int fd, const char *fmt, ...);
void wait_child(void);

#endif