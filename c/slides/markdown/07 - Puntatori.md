---
date: Aprile 2023
author: Dr. Nicola Bicocchi
institute: DIEF/UNIMORE
title: Puntatori
subtitle: Corso di Programmazione di Sistema
section-titles: true
theme: Madrid
colortheme: crane
fontsize: 10pt
aspectratio: 1610
lang: it
---

# Puntatori a void

* La parola chiave **void** può essere usata per dichiarare dei puntatori che non puntano a nessun tipo di dato in particolare
* E' sempre consentito l'assegnamento di un puntatore a **void** a qualunque altro tipo di puntatore. Lo è pure l'assegnamento di qualunque puntatore ad un puntatore a **void**
* L'assegnamento tra puntatori di tipi diversi da void causa invece la generazione di un messaggi di warning
  
```c
void *ptr;
int *i;
float *f;

i = ptr;
ptr = i;

/* Incompatible pointer types assigning to 'int *' from 'float *' */
i = f;
```


# Puntatori a void
```c
void stampa_bit(void *ptr) {
    int i;
    printf("%p ", ptr);
    for (i = 31; i >= 0; i--) {
        printf("%d", (*ptr) >> i) & 0x01);
    }
    printf("\n");
}

int main(void) {
    int a = 100;
    float b = 100.0F;
    stampa_bit((void *)&a);
    stampa_bit((void *)&b);
}
```

```
0x7ffee58cc8dc 00000000000000000000000001100100
0x7ffee58cc8d8 01000010110010000000000000000000
```


# Aritmetica dei puntatori
* Ai puntatori possono essere sommati e sottratti numeri interi. Il risultato della somma di un puntatore e di un numero intero è l'indirizzo dell'elemento n-esimo del vettore. 
* Il valore numerico del puntatore (indirizzo in memoria espresso in byte) viene incrementato/decrementato della dimensione di un oggetto puntato (sizeof(\*p))

```c
int main(void) {
    int i, v[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int *p = v;

    for (i = 0; i < 10; i++) {
        printf("[%d] %d %d %d\n", i, v[i], *(v + i), *(p + i));
    }

    for (i = 0; i < 10; i++, p++) {
        printf("[%d] %d %d %d\n", i, v[i], *(v + i), *p);
    }
}
```


# Aritmetica dei puntatori
* Il puntatore *p* è utilizzato per scorrere il vettore (inizializzato all'indirizzo del primo elemento)
* Il ciclo termina quando il valore puntato \*p, è nullo (il valore 0 equivale alla condizione logica *falso*)
* L'unico valore di *v* con valore zero deve essere ultimo, altrimenti il puntatore assumerà valori non validi andando ad accedere oltre la fine del vettore oppure il ciclo terminerà in modo prematuro
* Approccio seguito nella gestione delle stringhe ma **non adatto** a vettori numerici

```c
char string[] = "hello world!";
char *p;

// prints "hello world!" letter by letter
for (p = string; *p; p++) {
    printf("%c", *p);
}
```


# Aritmetica dei puntatori
* E' possibile fare la differenza (ma non la somma!) tra puntatori dello stesso tipo
* Il risultato della differenza fra puntatori è un numero intero che rappresenta **il numero di elementi** (non di bytes!) che separano i due puntatori
* La dimensione di un singolo elemento è quella definita dal tipo di dato puntato

```c
int main(void) {
    int *p, *q, v[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    p = &v[0];  /* equivalente a p = v */
    
    q = p + 2;
    printf("%ld\n", q - p);     /* Output: 2 */
    printf("%d %d\n", *p, *q);  /* Output: 0 2 */

    q = p + 4;
    printf("%ld\n", q - p);     /* Output: 4 */
    printf("%d %d\n", *p, *q);  /* Output: 0 4 */
}
```


# Operatori
Gli operatori fondamentali per usare i puntatori sono:

* \* (da leggere *il valore puntato da*)
* & (da leggere *l'indirizzo di*)
* [] accedo ad un elemento particolare di un vettore
* Si noti che \*p == p[0], \*(p+i) == p[i]

```c
int i;
int v[10];
int *p;

p = v;      /* p punta ad indice 0 di v */
p = &v[0];  /* p punta ad elemento con indice 0 di v */
p = &v[4];  /* p punta ad elemento con indice 4 di v */
p = v + 4;  /* p punta ad elemento con indice 4 di v */
p++;        /* p punta ad elemento con indice 5 di v */
i = p - v;  /* i == 5 */
```

# Puntatori e stringhe
* Vettori e puntatori sono concetti affini, ma esistono sottili differenze
  * I puntatori possono contenere indirizzi variabili nel corso dell'esecuzione, mentre i vettori rappresentano *indirizzi costanti* (non è possibile modificare l'indirizzo ad un vettore!)
  * Le stringhe memorizzate in un vettore possono essere modificate in ogni momento o accedendo ai singoli elementi oppure tramite apposite funzioni (e.g., *strcpy*). Le stringhe memorizzate attraverso puntatore sono invece memorizzate in aree di memoria in *sola lettura*
  * *sizeof* si comporta in modo diverso. Ritorna la dimensione del vettore o la dimensione del puntatore
  * *&* si comporta in modo diverso. Ritorna l'indirizzo del primo elemento o l'indirizzo del puntatore
  
```c
int main(void) {
    char s1[] = "nicola";
    char *s2 = "nicola";

    s1 = s2;        /* Errore in compilazione */
    s2[0] = 'a';    /* Errore a runtime */
    printf("%lu %lu\n", sizeof(s1), sizeof(s2));    /* Output: 7 8 */
}
```


# Puntatori e stringhe
```c
char s1[] = "prova";
char s2[] = {'p', 'r', 'o', 'v', 'a', '\0'};
char c, *t;

c = *s1;        /* c == 'p' */
t = s1 + 2;     /* t contine indirizzo del carattere 'o' */

s1[0] = *t;     /* s1 == "orova" */

t++;            /* t contine indirizzo del carattere 'v' */

s1++;           /* errore in compilazione */
```

# Puntatori e stringhe
* L'esempio seguente mostra un possibile utilizzo dell'aritmetica dei puntatori al fine di calcolare la lunghezza di una stringa *zero-terminata*

```c
unsigned str_len(char *ptr) {
    unsigned size = 0;

    for (; *ptr; ptr++) size++;
    return size;
}

int main(void) {
    char s[] = "prova";
    printf("%u\n", str_len(s));
}
```

# Vettori di stringhe
```c
int main(void) {
    int i;
    char *strings[] = {
            "Sara", "Sebastiano", "Paolo", "Agostino", "Elvira", NULL
    };
    char **p;

    for (i = 0; i < 5; i++) {
        printf("[%d] %s\n", i, strings[i]);
    }

    for (i = 0; i < 5; i++) {
        printf("[%d] %s\n", i, *(strings + i));
    }

    i = 0;
    for (p = strings; *p; p++) {
        printf("[%d] %s\n", i++, *p);
    }
}
```

# Vettori di stringhe
![Vettore di Stringhe](./images/vettore_stringhe.avif)

# Vettori di stringhe
```c
int main(void) {
    char *strings[] = {
            "Sara", "Sebastiano", "Paolo", "Agostino", "Elvira", NULL
    };
    char **p = strings;

    /* Indirizzo del primo puntatore a carattere */
    printf("%p %p %p\n", strings, &strings[0], p);

    /* Indirizzo del secondo puntatore a carattere */
    printf("%p %p %p\n", strings + 1, &strings[1], p + 1);

    /* Indirizzo del primo carattere della prima stringa */
    printf("%p %p\n", &strings[0][0], *p);

    /* Valore del primo carattere della prima stringa */
    printf("%c %c\n", strings[0][0], **p);
}
```


# L'allocazione dinamica della memoria
* Il linguaggio C permette di effettuare l'allocazione di memoria anche durante l'esecuzione del programma, sulla base di opportune condizioni che possono verificarsi durante l'esecuzione
* Questo tipo di allocazione di memoria è detta dinamica (*heap*), proprio perché avviene dinamicamente durante l'esecuzione. L'allocazione cosiddetta statica (*stack*) è quella che invece viene effettuata dal compilatore a seguito della dichiarazione delle variabili
* Il tempo di vita di porzioni di memoria allocate dinamicamente **non dipende** da quello della funzione in cui l'allocazione avviene

```c
#include <stdlib.h>
void *malloc(size_t size);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size);
free(void *ptr);
```

```c
#include <string.h>
void *memset(void *ptr, int c, size_t size)
void *memcpy(void *destination, const void *source, size_t size);
void *memmove(void *destination, const void *source, size_t size)
```

# L'allocazione dinamica della memoria (malloc)

```c
void *malloc(size_t size);
```

* **malloc** (Memory ALLOCation) richiede come argomento il numero di byte da allocare in memoria
* Restituisce l'indirizzo al quale la memoria è stata allocata
* Restituisce NULL se non è stato possibile allocare la memoria
* *Lo spazio allocato in memoria è contiguo*

```c
int *p;
/* Dipendente dal tipo di dato */
p = malloc(10 * sizeof(int));

/* Indipendente dal tipo di dato, da preferire */
p = malloc(10 * sizeof(*p));    
```


# L'allocazione dinamica della memoria (malloc)
* Viene allocato lo spazio necessario per memorizzare 10 valori interi contigui, uno spazio di memoria che può quindi essere acceduto come fosse un vettore
* E' possibile utilizzare il puntatore tramite indici (notazione []) per accedere alla memoria allocata

```c
int *p;
p = malloc(10 * sizeof(*p));

if (!p) {
    /* gestione dell'errore */
}

for (int i = 0; i < 10; i++) {
    p[i] = i;
    /* oppure *(p + i) = i; */
}

free(p);
```

# L'allocazione dinamica della memoria (malloc)
* Tecniche per azzerare gli elementi di un vettore (allocato dinamicamente e non)

```c
/* for e puntatori */
for(i = 0; i < 10; i++) {
    p[i] = 0;
}

for (i = 0; i < 10; i++, p++) {
    *p = 0;
}

/* memset */
memset(p, 0, 10 * sizeof(*p));

/* bzero */
bzero(p, 10 * sizeof(*p));
```

# L'allocazione dinamica della memoria (free)
```c
free(void *ptr);
```

* Libera il blocco di memoria di indirizzo *p* precedentemente allocato tramite *malloc*, *calloc* o *realloc*. La memoria liberata dall'invocazione di *free* diventa disponibile per altre applicazioni
* La memoria allocata dinamicamente deve essere rilasciata quando non è più necessaria, per evitare di occupare inutilmente memoria
* Con *memory leak* si intende il mancato utilizzo della funzione *free*. Come conseguenza, il sistema perde di continuo memoria disponibile 


# L'allocazione dinamica della memoria (calloc, realloc)
```c
void *calloc(size_t nmemb, size_t size);
```
* Alloca un puntatore ad un blocco di memoria in grado di contenere un vettore di *nmemb* elementi ciascuno dei quali ha dimensione *size*
* Il blocco di memoria viene inizializzato a 0 byte per byte

```c
void *realloc(void *ptr, size_t size);
```
* Ridimensiona a *size* un blocco di memoria già allocato e puntato da *ptr* 
* Preserva il contenuto della memoria già allocata e non inizializza il blocco di memoria aggiuntivo
* *In caso \*p sia un puntatore non allocato o su cui è già stata chiamata free(), il comportamento è non definito*


# L'allocazione dinamica della memoria (calloc, realloc)
* In questo esempio viene allocato dinamicamente (e inizializzato a 0) lo spazio necessario a contenere 10 interi. Successivamente, lo spazio allocato viene allargato per contenere 20 interi e la memoria aggiuntiva viene, a sua volta, inizializzata a 0.

```c
int main(void) {
    int i, *p;

    p = calloc(10, sizeof(*p));
    for (i = 0; i < 10; i++) {
        printf("%d\n", p[i]);
    }

    p = realloc(p, 20 * sizeof(*p));
    for (i = 10; i < 20; i++) {
        p[i] = 0;
    }
}
```

# L'allocazione dinamica della memoria (esempio strdup)

* Esistono funzioni di libreria che utilizzano *malloc* per svolgere i loro compiti

```c
char *strdup(const char *s);
```
  
* *strdup* (STRing DUPlicate) dichiarata in string.h, ritorna un puntatore a una nuova stringa che è un duplicato
  della stringa *s* passata come parametro
* La funzione, al suo interno, alloca memoria per la nuova stringa con malloc. Quando la copia generata non viene più utilizzata, la memoria deve essere esplicitamente liberata con *free*

```
The strdup() function returns a pointer to a new string which is
a duplicate of the string s.  Memory for the new string is
obtained with malloc(3), and can be freed with free(3).
```

# L'allocazione dinamica della memoria (esempio strdup)

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char *str = "hello world!";
    char *str_copy = strdup(str);

    printf("%s %s\n", str, str_copy);

    free(str_copy);
    
    /* error: pointer being freed was not allocated */
    free(str);
}
```

# Problemi con i puntatori (dangling references)
* Un puntatore *dangling* è puntatore che punta ad un'area di memoria non valida

```c
int *p;                         /* puntatore a intero (definizione) */
  
p = malloc(sizeof(*p));        /* allocazione della memoria */
  
*p = 57;                        /* impiego dell'area allocata */

free(p);                        /* deallocazione memoria */
  
*p = 20;                        /* Errore! Dangling Reference */
                                /* L'area di memoria puntata da p non e' piu' disponibile !!!! */

p = NULL;                       /* Non accedo alla memoria puntata da p */
                                /* Accedo a p e lo faccio puntare a NULL */
```

# Problemi con i puntatori (dangling references)
* In questo caso viene ritornato l'indirizzo di una variabile memorizzata nella porzione di stack riservata alla funzione *func*. Sfortunatamente, quella porzione di memoria viene resa disponibile non appena la funzione *func* termina. Questa circostanza genera un warning in compilazione.

```c
int *func(void) {
    int n = 13;
    return &n;
}

int main(void) {
    int *p;

    p = func();
    printf("%d\n", *p);
}
```

# Problemi con i puntatori (aree non piu' utilizzabili)
* Questo problema avviene quando, per un qualsiasi motivo, viene perso l'indirizzo di un'area di memoria ancora allocata. Chiaramente l'area di memoria interessata non e' piu' referenziabile e nemmeno deallocabile!

```c
int *p1, *p2;               /* definizione di 2 puntatori a intero */

p1 = malloc(sizeof(*p1));   /* alloco 1^ area di memoria */
p2 = malloc(sizeof(*p2));   /* alloco 2^ area di memoria */

/* 
 * Errore! p2 punta all'area di memoria di p1!
 * Non posso piu' accedere alla memoria allocata con la seconda malloc() 
 */
p2 = p1;                            
```

# Allocazione dinamica e matrici
* E' possibile allocare dinamicamente matrici (array bi-dimensionali), utilizzando sia un singolo puntatore (type *matrix) che un puntatore a puntatore (type **matrix)
* Il primo (singolo puntatore) è semplice, immediato, ma impedisce uso di indicizzazione esplicita (matrix[i][j]) e necessita di calcolo manuale dell'offset (offset = i * cols + j)
* Il secondo (puntatore a puntatore) richiede un meccanismo più complesso per allocare e disallocare la memoria, ma consente l'uso di indicizzazione esplicita (matrix[i][j])

# Allocazione dinamica e matrici
![Allocazione_matrici](./images/matrici_memoria.avif)

# Allocazione dinamica e matrici (singolo puntatore)
```c
int *allocate_matrix(unsigned rows, unsigned cols) {
    int *m;

    m = malloc((unsigned long)(rows * cols) * sizeof(*m));
    return m;
}
```

```c
int main(void) {
    int *m;

    m = allocate_matrix(10, 10);
    if (m == NULL) {
        /* allocation error */
    }
    
    /* code here */
    
    free_matrix(m);
}
```

# Allocazione dinamica e matrici (singolo puntatore)
```c
void show_matrix(unsigned rows, unsigned cols, int *m) {
    unsigned i, j, offset;
    
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            offset = i * cols + j;
            printf("%4d", m[offset]);
        }
        printf("\n");
    }
}
```

```c
void free_matrix(int *m) {
    free(m);
}
```

# Allocazione dinamica e matrici (doppio puntatore)
```c
int **allocate_matrix(unsigned rows, unsigned cols) {
    unsigned i; 
    int **m;

    m = malloc((unsigned long)(rows) * sizeof(*m));
    if (m == NULL) return NULL;
    for (i = 0; i < rows; i++) {
        m[i] = malloc((unsigned long)(cols) * sizeof(**m));
        if (m[i] == NULL) return NULL;
    }
    return m;
}
```

```c
int main(void) {
    int **m;
    m = allocate_matrix(3, 2);
    /* code here */
    free_matrix(3, m);
}
```

# Allocazione dinamica e matrici (doppio puntatore)
```c
void show_matrix(unsigned rows, unsigned cols, int **m) {
    unsigned i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%4d", m[i][j]);
        }
        printf("\n");
    }
}
```

```c
void free_matrix(unsigned rows, unsigned cols, int **m) {
    unsigned i;
    for (i = 0; i < rows; i++) {
        free(m[i]);
    }
    free(m);
}
```

# Allocazione dinamica e strutture
* Nel caso di oggetti relativamente complessi come le matrici, in cui i dati veri e propri (il contenuto della matrice) è sempre abbinato ad informazioni aggiuntive come al esempio il numero di righe e di colonne, l'utilizzo di strutture (aggregazione di aspetti diversi della stessa entità) è consigliabile!

```c
struct matrix {
    size_t rows, cols;
    double **data;
};
```

```c
int main(void) {
    struct matrix *m, *m_trans;
    
    m = allocate_matrix(3, 2);
    fill_matrix(m);
    m_trans = matrix_transpose(m);
    free_matrix(m);
    free_matrix(m_trans);
}
```

# Allocazione dinamica e strutture

```c
struct matrix *allocate_matrix(size_t rows, size_t cols) {
    struct matrix *m;
    size_t i;

    m = malloc(sizeof(*m));
    m->rows = rows;
    m->cols = cols;
    m->data = malloc((unsigned long) (rows) * sizeof(*(m->data)));
    if (m == NULL) return NULL;

    for (i = 0; i < rows; i++) {
        m->data[i] = malloc((unsigned long) (cols) * sizeof(**(m->data)));
        if (m->data[i] == NULL) return NULL;
    }

    return m;
}
```

# Allocazione dinamica e strutture
```c
void show_matrix(const struct matrix *m) {
    size_t i, j;
    for (i = 0; i < m->rows; i++) {
        for (j = 0; j < m->cols; j++) {
            printf("%8.2lf", m->data[i][j]);
        }
        printf("\n");
    }
}
```

```c
void free_matrix(struct matrix *m) {
    size_t i;
    for (i = 0; i<m->rows; i++) {
        free(m->data[i]);
    }
    free(m->data);
    free(m);
}
```

# Puntatori a funzione
* In C, così come il nome di un array è un puntatore al suo primo elemento, il nome di una funzione è un puntatore alla funzione stessa. Il C permette la manipolazione esplicita dei puntatori a funzione. Data la funzione *f()*: 

```c
int f(short, double) {}
```

* Allora il nome f è un puntatore di tipo:

```c
int (*)(short, double)
```

* Dichiarando un puntatore dello stesso tipo, si pu`o effettuare, ad esempio, un assegnamento:

```c
int (*ptr_to_f)(short, double);     /* ptrtof puntatore a funzione */
ptr_to_f = f;                       /* assegna indirizzo di f a ptrtof */
(*ptr_to_f)(2,3.14);                /* invoca f attraverso un puntatore */
```

* Si presti attenzione alla sintassi: int \*f(int); dichiara il prototipo di una funzione che restituisce un puntatore a intero. int (\*f)(int); dichiara un puntatore a funzione.