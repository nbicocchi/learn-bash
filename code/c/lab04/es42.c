#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "utils.h"

char msg[] = "Hello World!";
char msg2[256];

int main(int argc, char **argv) {
	int p[2]; 
	int nw, nr;
	int status;
	
	if (pipe(p) != 0) {
		zprintf(2, "[%d] error: pipe()\n", getpid());
		exit(1);
	}
	
	zprintf(1, "[%d] p[0]=%d, p[1]=%d\n", getpid(), p[0], p[1]);
	
	/* use this line for changing behaviour */
	close(p[0]);
	
	/* utilizziamo la fork per lasciare al processo figlio
	 * l'incombenza di scrivere sulla pipe e recuperiamo
	 * le informazioni di terminazione con la wait */
	switch (fork()) {
		case 0: 
			/* figlio */
			nw = write(p[1], msg, strlen(msg)); /* su msg->pipe */
			nr = read(p[0], msg2, sizeof(msg2)); /* da pipe->msg2 */
			
			zprintf(1, "[%d] [nr=%d] [nw=%d] msg received: %s\n", getpid(), nr, nw, msg2);
			exit(0);
		case -1: /* errore fork */
			zprintf(2, "[%d] error: fork()\n", getpid());
			exit(1);
	}
	
	/* padre: attendo il figlio (unico, non devo recuperare il pid) */
	wait(&status);
	if (WIFEXITED(status)) { 
		/* terminazione "naturale", exit value valido */
		zprintf(1, "[%d] child returned %d\n", getpid(), WEXITSTATUS(status));
	} else { 
		/* terminazione forzata, no exit value ma id segnale */
		zprintf(1, "[%d] child received signal %d\n", getpid(), WTERMSIG(status));
	}
	
	exit(0);
}

