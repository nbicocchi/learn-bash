---
date: Aprile 2023
author: Dr. Nicola Bicocchi
institute: DIEF/UNIMORE
title: Introduzione al C
subtitle: Corso di Programmazione di Sistema
section-titles: true
theme: Madrid
colortheme: crane
fontsize: 10pt
aspectratio: 1610
lang: it
---

# Il linguaggio C
* È un linguaggio di programmazione general-purpose progettato inizialmente da Dennis Ritchie dei Bell Laboratories e implementato nel 1972. Inventato per sopperire ai limiti del linguaggio B e BCPL
* I linguaggi sono creature vive e vengono migliorati periodicamente:
  * 1973: invenzione del linguaggio C da parte di Rennis Ritchie
  * 1983: National Standard Institute (ANSI) inizia la definizione di ANSI C o C standard
  * 1989: definizione dello standard [C89](https://en.wikipedia.org/wiki/ANSI_C#C89) 
  * 1999: definizione dello standard [C99](https://en.wikipedia.org/wiki/C99) 
  * 2011: definizione dello standard [C11](https://en.wikipedia.org/wiki/C11_(C_standard_revision))
  * 2018: definizione dello standard [C17](https://en.wikipedia.org/wiki/C17_(C_standard_revision))
* La possibilità di utilizzare certe funzionalità del C dipende strettamente dal supporto del compilatore.


# Caratteristiche del C
E' la lingua franca per gli sviluppatori. Implementazioni di nuovi algoritmi, ad esempio, sono spesso divulgate inizialmente solo in C. E' anche il linguaggio in cui si descrive spesso il comportamento della macchina. **Evita superstizione!**

* Linguaggi di programmazione di **alto livello**: gestione automatica della memoria, oggetti, stream, stringhe, collections...). Esempi: Python, Java, Javascript, C#, Dart, Kotlin
* Linguaggi di programmazione di **basso livello**: gestione manuale della memoria e astrazioni semplici (tipi di dati, funzioni,
strutture dati), parziale visibilità architetturale. Esempi: C, Rust
* Linguaggi di programmazione di **bassissimo livello**: programmi scritti specificamente per un tipo di architettura hardware. Esempi: assembly, VHDL

# Caratteristiche del C
* **Procedurale**: il programma è un insieme di *procedure* (funzioni). Non esiste supporto a strutture modulari più complesse come classi ed oggetti.
* **Compilato**: il codice sorgente deve essere trasformato in linguaggio macchina da un compilatore (e.g., gcc) *prima di essere eseguito*.
* **Tipizzato**: ogni variabile ha un tipo associato, lo sviluppatore deve sempre dichiarare il tipo prima di usare la variabile. E' però possibile utilizzare tipi alternativi per accedere al dato (i.e., lascamente tipizzato).

Il linguaggio è pensato per essere **efficiente**: lo sviluppatore ha il controllo completo su quello che succede. Tuttavia: commettere errori è facile e subdolo: il compilatore non rileva gli errori con la completezza delle alternative più recenti (Java o Python). Inoltre, gli errori possono produrre conseguenze gravi in termini di sicurezza e integrità del sistema non esistendo una virtual machine (*sandbox*).


# Ambito di utilizzo del C

* Sistemi Operativi (e.g., kernel Windows/Linux/Mac/IoS/Android)
* Sistemi embedded (e.g., Arduino)
* Database (e.g., MySQL, MS SQL Server, and PostgreSQL)
* Linguaggi di programmazione (e.g., Python)
* Librerie e routine ad alte performance (e.g., numpy, webassembly)
* Motori grafici 3D (e.g., Unreal Engine C++)
* Software per telecomunicazioni (e.g., openWrt)
* Software di controllo per processi industriali (e.g., PLC)


# Ambienti di sviluppo
*Gli ambienti di sviluppo integrato – o IDE, Integrated Development Environment – sono strumenti fondamentali per il lavoro di un programmatore. Esistono una varietà di ambienti di sviluppo, dai più complessi ed articolati, fino a semplici editor di testo affiancati ad un compilatore.*

* CLion
* Eclipse
* Code::Blocks
* Visual Studio Code
* Sublime text
* Vim


# Hello World! Funzione main()
L'esecuzione di un programma C inizia sempre dalla prima istruzione della funzione *main*. La funzione *main* accetta argomenti (per ora ignorati) e ritorna un numero intero. Il programma termina quando la funzione *main* termina.

Linea 3: **int** tipo del valore di ritorno della funzione, **main** nome della funzione, **{** inizio del corpo della funzione. La funzione termina a linea 6 **}**.

Linea 4: **printf** invocazione della funzione di libreria printf(), che riceve come argomento la stringa costante *Hello, World!* terminata con carattere a capo **\\n**.

Linea 5: **return** istruzione che termina la funzione e ritorna **0** (successo in Unix). 

```c
#include <stdio.h>

int main(){
  printf("Hello, World!\n");
  return 0;
}
```

# Processo di compilazione
![Processo di compilazione](images/compilazione.avif)

# Keywords
* **Codice sorgente**: file di testo che contiene il software scritto dallo sviluppatore
* **File oggetto**: file binario che contiene codice macchina corrispondente al programma C originale più informazioni simboliche
* **File eseguibile**: file binario che contiene il codice macchina pronto per l'esecuzione su una specifica architettura
* **Linker**: programma per unire più file oggetto con eventuali librerie esterne per ottenere il file eseguibile


# Compilazione ed esecuzione
```shell
$ gcc -Wall -o helloworld helloworld.c
$ ./helloworld
```

* Il comando compila il codice sorgente *helloworld.c* in un programma eseguibile di nome *helloworld*
  * -Wall attiva tutti i warnings (Warnings All)
  * -o specifica il nome del file compilato (default=a.out)
* E' possibile eseguire il programma invocandolo dalla shell utilizzando il nome specificato con l'opzione -o
  

# Messaggi di errore
* Gli *errori* causano il fallimento della compilazione del programma
* I *warnings*, invece, sono segnalazioni di possibili problemi ma non causano il fallimento della fase di compilazione. In linea generale, è bene risolverli tutti prima di procedere con lo sviluppo.

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
  printf("Hello, World!\n");
  return 0
}
```

```
helloworld.c:6:1: error: expected ';' after return statement
helloworld.c:2:1: warning: Unused "#include <stdlib.h>"
```

# makefile
* Per gestire la compilazione di un progetto C complesso si fa uso di tool ausiliari (e.g., make).
* Il comando make cerca all'intero della directory corrente un file di nome *makefile* o *Makefile*.
* make evita di eseguire operazioni inutili: il codice viene compilato solo se vengono rilevate modifiche ai sorgenti.

```make
helloworld: helloworld.c
    gcc -Wall -o helloworld helloworld.c
```

# makefile
* make supporta l'utilizzo di variabili e simboli speciali.
* $(CC) : variabile che contiene il comando di compilazione (default: cc)
* $(CFLAGS): variabile che contiene le opzioni di invocazione del compilatore
* $@ : metacarattere che viene sostituito con il target (helloworld)
* $^ : metacarattere che viene sostituito con le dipendenze (helloworld.c)

```make
CC=gcc
CFLAGS=-Wall -g

clean:
    rm -rf helloworld

helloworld: helloworld.c
    $(CC) $(CFALGS) -o $@ $^
```

# CMake
* CLion utilizza un sistema chiamato CMake (https://cmake.org/)
* Il file che gestisce i processi di compilazione è CmakeLists.txt
* Si tratta di un sistema per generare il Makefile molto utile per aumentare la portabilità e la robustezza del processo di compilazione
* Anche se possibile, *nel corso non utilizzeremo CMake in modo esplicito, ma lo utilizzeremo attraverso la GUI di CLion*

# CMakeLists.txt
```cmake
cmake_minimum_required(VERSION 3.15)
project(hello C)
set(CMAKE_C_FLAGS "-Wall -Wconversion -Wformat")
set(CMAKE_C_STANDARD 99)

add_executable(hello main.c)
target_link_libraries(hello m)
```
**project(hello C)**: nome del progetto, linguaggio

**set(CMAKE_C_FLAGS "-Wall -Wconversion -Wformat")**: opzioni di compilazione

**set(CMAKE_C_STANDARD 99)**: standard C99

**target_link_libraries(hello m)**: configura il linker per collegare libreria matematica (m)

# Commenti
* I commenti sono porzioni di testo che non vengono considerate dal compilatore (i.e., vengono eliminati dal preprocessore)
* I commenti sono fondamentali per rendere leggibile il codice e promuovere la collaborazione fra più sviluppatori
* Come regola generale, è preferibile un commento descrittivo all'inizio di ogni funzione piuttosto che commenti brevi e sparsi

```c
/*
 * Questo è un commento multi-linea
 */

/* Questo è un commento multi-linea */

// Questo è un commento singola-linea
// Si tratta di una forma ereditata dal C++ 
// Non molto apprezzata dai puristi C
```

# Parole chiave
| **Parole chiave** | **Utilizzo** |
| ----------------- | ------------ |
| break case continue default do else for goto if return switch while | costrutti di controllo |
| char double enum float int long short signed struct union unsigned void | tipi di dato semplice |
| auto const extern register static volatile | modificatori di volatività e persistenza |
| sizeof | operatore che ritorna la dimensione di una varibile |
| typedef | definizione di tipi definiti dall'utente |


# Identificatori
* In C un identificatore è un nome che si riferisce a funzioni, variabili, ed oggetti in genere definiti nel codice
* Non può cominciare con un numero ma può contenere qualsiasi combinazione di:
  * lettere maiuscole e minuscole
  * numeri
  * il carattere underscore (_)
* Non può essere una parola chive del linguaggio
* Esempi **validi**: Prova_1, prova_1, media_pasata, _tot
* Esempi **invalidi**: 1_prova, totale_%, somma_{


# Variabili
* Una variabile è una porzione di memoria che contiene dei dati che possono essere modificati durante l'esecuzione. Ogni variabile deve essere dichiarata, ovvero associata ad un identificatore ed a un tipo.

```c
#include <stdio.h>

int main() {
    int a, b, somma;
    
    a = 10;
    b = 12;
    somma = a + b;
    printf("somma=%d\n", somma);
    return 0;
}
```

# Variabili
![Variabili](images/variabili.avif)

# Espressioni
* *Un programma C e' una sequenza di espressioni. Le espressioni sono combinazioni di variabili, costanti, chiamate a funzione, e operatori*
* Non esiste in C una reale delimitazione fra espressioni logiche e aritmetiche in quanto *0* è considerato equivalente al valore logico *falso*, mentre *1* è considerato equivalente al valore logico *vero*

```c
45 * (a + b)
delta * sqrt(abs(x1 * x2))
sqrt(a * b - c) <= 10
(c1 || c2) && c3
max = a > b ? a : b
a % b
```
