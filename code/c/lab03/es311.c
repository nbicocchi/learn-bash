#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <sys/wait.h>
#include "utils.h"

/* 
    topology definition 
    
            F
            |
            | 
     | ---> | <---|
   p0|    p1|   p2|
     V      V     V 
    c0     c1    c2
    ...     |    ...
        |---|---|
      p5|     p6|
        V       V
       n2      n3    

*/

/* when multiple pipes are needed this definition is useful */
typedef int pipe_t[2];

/* 
 * generic node function 
 * @param p_in array of pipes for communicating with the upper level
 * @param child_id the id the the node within its own level
 * @param level_current the current depth level in hierarchy. es. 0,1,2...
 * @param level_max the max depth level allowed
 * @param child_n the number of nodes for each depth level
 */
int node(pipe_t *p_in, int child_id, int level_current, int level_max, int *child_n) {
    pipe_t *p_out;
    pid_t pid;
    char cmd = 'a';
    int i;
    
    if (level_current > 0) {
        /* close unused input pipe sides
         * this is needed for being able of 
         * receiving commands from the upper level
         * level 0 nodes do not have input pipes */
        for (i = 0; i < child_n[level_current]; i++) { 
            close(p_in[i][1]); 
            if (i != child_id) close(p_in[i][0]); 
        }
    }
    
    if (level_current < level_max) {
        /* allocate memory for output pipes
         * needed for communicating with the 
         * nodes belonging to the next level 
          * level max nodes do not have children */
        p_out = (pipe_t *) malloc(sizeof(pipe_t) * child_n[level_current + 1]);
        if (p_out == NULL) {
            zprintf(1, "[%d] error malloc()\n", getpid());
            exit(EXIT_FAILURE);
        }
    
        /* init output pipes */
        for (i = 0; i < child_n[level_current + 1]; i++) { 
            if (pipe(p_out[i]) < 0) { 
                zprintf(1, "[%d] error pipe()\n", getpid());
                exit(EXIT_FAILURE);
            }
        }
    
        /* init child processes (next depth level) */
        for (i=0; i < child_n[level_current + 1]; i++) { 
            pid=fork(); 
            switch(pid) {
                case 0: 
                    node(p_out, i, level_current + 1, level_max, child_n);
                case -1:
                    zprintf(1, "[%d] error fork()\n", getpid());
                    exit(EXIT_FAILURE);
            }
        }
     
        /* close unused output pipe sides
         * this is needed for being able of 
         * sending commands to the next level */
        for (i = 0; i < child_n[level_current + 1]; i++) { 
            close(p_out[i][0]); 
        }
    }
    
    /* process hierarchy created!
     * the following is about the actual behaviour
     * of each node */
    
    if (level_current > 0) {
        /* wait for a command */            
        if (read(p_in[child_id][0], &cmd, 1) != 1) {
            zprintf(1, "[%d] read() failed\n", getpid());
            exit(EXIT_FAILURE);
        }
    
        zprintf(1, "[%d] [l=%d] command (%c) received\n", getpid(), level_current, cmd);
    }
    
    if (level_current < level_max) {
        /* send commands to the next level (changing command) */
        cmd += 1;
        for (i = 0; i < child_n[level_current + 1] ; i++) { 
            zprintf(1, "[%d] [l=%d] writing to child %d...\n", getpid(), level_current, i);
            if (write(p_out[i][1], &cmd, 1) != 1) {
                zprintf(1, "[%d] write() failed\n", getpid());
                exit(EXIT_FAILURE);
            }
        }
    
        /* wait child before exit */
        for (i = 0; i < child_n[level_current + 1]; i++) {
            wait_child();
        }
    }
    exit(EXIT_SUCCESS);
}


/* main function */
int main(int argc, char **argv) {
    char *usage = "usage: %s child_l1 ... child_ln\n";
    int i, *child_n;
    
    /* arguments check */
    if (argc != 2) {
        zprintf(1, usage, argv[0]);
        exit(EXIT_FAILURE);
    }
    
    child_n = (int *)malloc(sizeof(int) * argc);
    child_n[0] = 0;
    for (i = 1; i < argc; i++) {
        child_n[i] = atoi(argv[i]);
        if (child_n[i] <= 0) { 
            zprintf(1, "error: child_l1_n must be positive\n");
            exit(EXIT_FAILURE);
        }
    }
    node((pipe_t *) NULL, 0, 0, argc - 1, child_n);
}

