# Programmazione di Sistema - DIEF/UNIMORE

## Esercizi C (Matrici e strutture)

Si propongono alcuni esercizi relativi all’utilizzo di matrici (array bi-dimensionali) e strutture (struct).

---

Esercizio 1. Implementare una funzione *matrix_edge* che, data una matrice come input, calcoli la somma di tutti i
valori presenti nella sua *cornice*. La funzione deve rispettare il seguente prototipo:

```c
long matrix_edge(unsigned rows, unsigned cols, int m[][cols]);
```

dove:

* **m** è la matrice di input, con **n_rows** righe e **n_cols** colonne;
* la funzione calcola il risultato e restuisce la somma tramite il suo valore di ritorno.

---

Esercizio 2. Implementare una funzione *diagonals* che estrae la diagonale principale e la diagonale secondaria di una
matrice quadrata. La funzione deve rispettare il seguente prototipo:

```c
void diagonals(int *rdp, int *rds, unsigned cols, const int m[][cols]);
```

dove:

* **rdp** è il puntatore in cui viene memorizzata la diagonale principale;
* **rds** è il puntatore in cui viene memorizzata la diagonale secondaria;
* **m** è la matrice di input di dimensione **size** righe e **size** colonne;
* assumere che sia rdp sia rds siano puntatori ad aree di memoria già allocate correttamente.

---

Esercizio 3. Implementare una funzione *tabula_recta* che crei una matrice contenente la [tabula recta](https://en.wikipedia.org/wiki/Tabula_recta) dell’alfabeto inglese. Rispettare il seguente prototipo:

```c
void tabula_recta(char t[][26]);
```

dove:

* **t** è la matrice in cui viene salvato la matrice generata.

---

Esercizio 4. Implementatre una funzione *array_stats* per l’individuazione del valore minimo, del valore massimo, della
media e della varianza dei valori di un array. La funzione deve rispettare il seguente prototipo:

```c
struct array_info {
    int max;
    int min;
    float mean;
    float variance;
};

struct array_info array_stats(const int *values, unsigned size);
```

dove:

* **array_info_t** è la struct che gestisce la informazioni dell’array;
* **values** è il puntatore all’array;
* **size** è la dimensione dell’array.

---

Esercizio 5. Implementare una variante dell’esercizio precedente che implementi le stesse funzionalità con lo stesso
tipo di struct, ma che supporti un prototipo diverso.

```c
void array_stats(struct array_info *r, const int *values, unsigned size);
```

dove:

* **r** è il puntatore alla struttura dati in cui memorizzare i valori calcolati dalla funzione;
* **values** è il puntatore all’array;
* **size** è la dimensione dell’array.

---

Esercizio 6. Implementare una funzione *complex_product* per calcolare il prodotto di due numeri complessi che rispetti
il seguente prototipo:

```c
struct complex {
    double real;
    double imaginary;
};

void complex_product(struct complex *r, const struct complex *c1, const struct complex *c2);
```

dove:

* **r** è il puntatore alla struttura dati in cui memorizzare i valori calcolati dalla funzione;
* **c1** rapresenta il primo numero da moltiplicare;
* **c2** rapresenta il secondo numero da moltiplicare.

---

Esercizio 7. Implementare una funzione *compute_length* per il calcolo della lunghezza di una linea spezzata. La
funzione supporti il seguente prototipo:

```c
typedef struct point {
   float x;
   float y;
} point_t;
   
float compute_length(const point_t *p, unsigned n);
```

dove:

* **point_t** rappresenta un punto sul piano con coordinate x e y;
* **compute_length** è la funzione per il calcolo della lunghezza:
    * accetta il puntatore ad un vettore di point_t;
    * accetta il numero di point_t contenuti nel vettore;
    * restituisce la lunghezza della linea spezzata.

---

Esercizio 8. Implementare una funzione *compute_area* per il calcolo dell’area di un poligono irregolare date le
coordinate dei suoi vertici (https://arachnoid.com/area_irregular_polygon/index.html). La funzione supporti il seguente
prototipo:

```c
typedef struct point {
   float x;
   float y;
} point_t;

typedef struct polygon {
    unsigned n;
    point_t *vertices;
} polygon_t;
   
float compute_area(const polygon_t *p);
```

dove:

* **point_t** rappresenta un punto sul piano con coordinate x e y;
* **polygon_t** rappresenta il poligono con n vertici, ognuno identificato come un punto sul piano;
* **compute_area** è la funzione per il calcolo dell’area:
    * accetta il puntatore alla struttura che rappresenta il poligono;
    * restituisce l’area del poligono.

---

Esercizio 9. Implementare una funzione *isinside* per che verifichi se un punto 2D si trova all'interno di un cerchio.
La funzione supporti il seguente prototipo:

```c
typedef struct point {
   float x;
   float y;
} point_t;

typedef struct circle {
    point_t center;
    float radius;
} circle_t;
   
int isinside(const point_t *p, const circle_t *c);
```

dove:

* **point_t** rappresenta un punto sul piano con coordinate x e y;
* **circle_t** rappresenta il poligono con n vertici, ognuno identificato come un punto sul piano;
* **isinside** è la funzione che verifica se il punto è contenuto oppure no all'interno del cerchio:
    * accetta il puntatore alla struttura che rappresenta il punto;
    * accetta il puntatore alla struttura che rappresenta il cerchio;
    * ritorna 0 (falso) oppure 1 (vero).

---

Esercizio 10. Implementare una funzione *show_addresses* che mostri all'utente che le celle di una matrice sono
memorizzate in modo contiguo, riga dopo riga.

```c
void show_addresses(int rows, int cols, int m[][cols]);
```

dove:

* **m** è la matrice di input, con **rows** righe e **cols** colonne.

---

Esercizio 11. Data la seguente definizione:

```
#define FIELD_LEN 30
struct person {
    char name[FIELD_LEN];
    char lastname[FIELD_LEN];
    double age;
};
```

Implementare una coppia di funzioni *init_person*, *show_person* per inizializzare e visualizzare una struct person, rispettivamente. 
Le due funzioni devono aderire ai seguenti prototipi:

```c
void init_person(struct person *person, char *name, char *lastname, double age);
void show_person(struct person *person);
```

dove:

* **person** è il puntatore alla struct person da manipolare;
* **name** è il puntatore all'array di caratteri che contiene il nome della persona;
* **lastname** è il puntatore all'array di caratteri che contiene il cognome della persona;
* **age** è un valore double che rappresenta l'età della persona.

