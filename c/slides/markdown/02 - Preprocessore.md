---
date: Aprile 2023
author: Dr. Nicola Bicocchi
institute: DIEF/UNIMORE
title: Preprocessore
subtitle: Corso di Programmazione di Sistema
section-titles: true
theme: Madrid
colortheme: crane
fontsize: 10pt
aspectratio: 1610
lang: it
---

# Processo di compilazione
![Processo di compilazione](./images/compilazione.avif)

# Compilazione

* Direttiva per eseguire solamente il preprocessore
```shell
$ gcc -E helloworld.c
```

* Direttiva per disabilitare la fase di linking e produrre file oggetto (.o)
```shell
$ gcc -c helloworld.c
$ file helloworld.o
helloworld.o: Mach-O 64-bit object x86_64
```

* Direttiva per compilazione completa
```shell
$ gcc helloworld.c -o helloworld
$ file helloworld
helloworld: Mach-O 64-bit executable x86_64
```

# Preprocessore
* Non è un comando o programma aggiuntivo, ma solo un termine con cui si definisce questa fase del processo di compilazione
* La si può immaginare come una procedura di manipolazione di testo: l’input è codice sorgente l’output è codice sorgente
* Le direttive al preprocessore non esistono più nel codice sorgente che viene effettivamente compilato nè tantomento nel codice compilato. Si tratta di un meccanismo per manipolare il codice sorgente prima della compilazione
* Per mostrare/salvare solo l’output del preprocessore si può usare:


# Direttive preprocessore
* Il simbolo **#** (diesis, cancelletto, o hash) precede tutte le operazioni che vengono gestite dal *preprocessore*
* Sono operazioni eseguite durante il processo di compilazione
* Servono, in particolare, a manipolare il codice sorgente *prima* della compilazione vera e propria. In particolare, sono utilizzate per aggiungere, modificare ed escludere parti di codice sorgente

```c
#include <stdio.h>

int main(){
    printf("Hello, World!\n");
    return 0;
}
```

# Direttive rilevanti
**\#include** aggiunta di codice

**\#define** modifica del codice

**\#ifdef (\#ifndef) \#else \#endif** esclusione condizionata di codice

# Direttiva #include
* Aggiunge codice sorgente presente in file esterni
* Utilizzato di solito con file header con estensione .h

```c
#include <stdio.h>
#include "mymath.h"
```

* Il preprocessore genera un file sorgente intermedio in cui la direttiva \#include <stdio.h> è sostituita dal contenuto dell'intero file indicato (/usr/include, /usr/local/include)

```shell
$ cat /usr/include/stdio.h
```

# Esempio (mymath.h e mymath.c)
* All'interno del file mymath.h posizioniamo i prototipi delle funzioni

```c
unsigned mypow(unsigned int base, unsigned int exp);
```

* All'interno del file mymath.c posizioniamo le implementazioni delle funzioni e includiamo math.h in cui potremmo aver definito costanti utili

```c
#include "mymath.h"

unsigned mypow(unsigned int base, unsigned int exp) {
    unsigned int result;
    for (result = 1; exp > 0; exp--) {
        result *= base;
    }
    return result;
}
```

# Esempio (main.c)
```c
#include <stdio.h>
#include "mymath.h"

int main(){
    unsigned int base=3,exp=5;
    printf("%u^%u=%u\n", base, exp, mypow(base, exp));
    return 0;
}
```

```cmake
cmake_minimum_required(VERSION 3.15)
project(mymath C)
set(CMAKE_C_STANDARD 99)

add_executable(main main.c mymath.c)
```

# Direttiva #define
* La direttiva \#define INPUT OUTPUT modifica il codice sorgente sostituendo tutte le occorrenze di INPUT con OUTPUT
* *Attenzione: \#define non definisce variabili e/o funzioni globali!*

```c
#define INPUT OUTPUT
```

```c
#include <stdio.h>
#define MAX 10
int main() {
    printf("Il valore massimo è %d\n", MAX);
    return 0;
}
```

# Direttiva #define parametrica

* Il valore di sostituzione può anche essere parametrico

```c
#define N(x) (10*(x))
int main(){
    int a=N(5);
    return 0;
}
```

* *Attenzione: N non è una funzione!*
* Il preprocessore crea un nuovo codice sorgente sostituendo tutte le occorrenze di N(argomento) con (10 * (argomento)) senza effettuare alcun controllo!
* E' importante utilizzare in modo opportuno le parentesi per evitare problemi di priorità!

# Parentesi

* Una definizione robusta si ottiene mettendo tra parentesi sia gli argomenti da sostituire che la macro stessa

```c
#define SQUARE(a) a*a

SQUARE(3);  // Output:9
SQUARE(1+2) // Sostituito in s = 1+2*1+2 -> Output:5
```

* Definizione robusta

```c
#define SQUARE(a) ((a)*(a))
```

# Direttiva #undef
* La direttiva \#define non ha scope
* Il preprocessore non conosce le funzioni o altri costrutti di aggregazione/visibilità del linguaggio. Legge i sorgenti e opera in modo sequenziale dall’inizio alla fine del file sorgente
* Per eliminare una definizione è necessario utilizzare la direttiva \#undef in modo esplicito

```c
int main(void) {
#define MAX 128
    printf("%d\n", MAX);
#undef MAX
    printf("%d\n", MAX);    /* Errore! MAX non è più definita */
}
```

# Direttiva #if
* E' possibile abilitare o disabilitare porzioni di codice attraverso l'uso del preprocessore e la direttiva \#if
* Il preprocessore non può valutare il contenuto di variabili o di codice a runtime
* Le uniche *variabili* nel preprocessore sono quelle definite attraverso la direttiva \#define (macro)
* Utile per: (a) scegliere tipi diversi di implementazione, (b) stabilire tipi di dati utilizzati, (c) stabilire comportamenti speciali per la fase di sviluppo (debug)

```c
#define ARCH amd64

int main(void) {
#if (ARCH==amd64)
    printf("amd64\n");
#else
    printf("i386\n");
#endif
}
```

# Direttiva #if (Esempi)
* message(S) stampa il messaggio solo se la MACRO DEBUG è definita
```c
#define DEBUG

#ifdef DEBUG
#define message(S) printf(S)
#else
#define message(S)
#endif

int main(void) {
    message("Hello world!");
}
```

# Direttiva #if (Esempi)
* Per evitare errori dovuti ad inclusioni multiple dello stesso file header (.h) vengono utilizzate le *include guards* come nell'esempio sotto. Il file viene incluso solo se la direttiva *MYMATH_H* non è definita. 
* In questo caso, cioè alla prima inclusione, la costante *MYMATH_H* viene definita per evitare future inclusioni.

```c
/* mymath.h with include guards */
#ifndef MYMATH_H
#define MYMATH_H

unsigned mypow(unsigned, unsigned);

#endif // MYMATH_H
```
