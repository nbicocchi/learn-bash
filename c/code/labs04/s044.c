#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../utils/utils.h"

sig_t default_handler;
int count = 0;

/* 
 * This handler, for restoring the default handler, 
 * uses the function pointer default_handler stored main()
 */
void sig_int_handler_v1(int s) {
    zprintf(1, "CTRL-Pressed!\n");
    if (count++ >= 2) {
        signal(SIGINT, default_handler);
    }
}

/* 
 * This handler, for restoring the default handler, 
 * uses the SIG_DFL handler
 */
void sig_int_handler_v2(int s) {
    zprintf(1, "CTRL-Pressed!\n");
    if (count++ >= 2) {
        signal(SIGINT, SIG_DFL);
    }
}

/* main function */
int main(int argc, char **argv) {
    default_handler = signal(SIGINT, sig_int_handler_v1);
    
    while(TRUE) {
        /* avoids cpu waste */ß
        sleep(1);
    }
    exit(EXIT_SUCCESS);
}

