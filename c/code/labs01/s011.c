#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "../utils/utils.h"

/* 
 * $ gcc es11.c
 * Produce un file binario di nome a.out
 *
 * $ gcc es11.c -o es11
 * Produce un file binario di nome es11
 * 
 * $ gcc es11.c -Wall -o es11
 * -W controlla la gestione dei warning (-Wall li attiva tutti)
 *
 * $ ./es11
 * $ echo $?
 * Visualizza exit value di es11. Vedi funzione exit().
 * 
 * $ ./es11 1>/dev/null
 * Ridirige stdout su /dev/null. Se esiste output, proviene da stderr
 * 
 * $ ./es11 2>/dev/null
 * Ridirige stderr su /dev/null. Se esiste output, proviene da stdout
 */

int main(int argc, char **argv) {
	fprintf(stdout, "Hello World!\n");

	char buffer[1024];
	memset(buffer, 0, 1024);
	snprintf(buffer, sizeof(buffer), "Hello World!\n");
	write(1, buffer, strlen(buffer));

	zprintf(1, "Hello World!\n");

	exit(0);
}
