# Programmazione di Sistema (DIEF, UNIMORE)

## Software Bash
* [VirtualBox](https://www.virtualbox.org/wiki/Downloads)
* [EndeavourOS](https://endeavouros.com/) 

[Guida installazione EndeavourOS](EndeavourOS%20Installation/README.md)

## Libri Bash
* Garrels - Bash Guide for Beginners
* Ramey, Fox - Bash reference manual

## Video Bash
* [YouTube Bash](https://www.youtube.com/watch?v=62-hJarauK4&list=PLhlcRDRHVUzR-5TKDC1VPMtyhEyyQ5uwy)

## Tutorial, Esercizi Online Bash
* https://www.tutorialspoint.com/unix/
* https://explainshell.com/

## Software C
* [CLion](https://www.jetbrains.com/clion/)

## Libri C
* Facchinetti, Larizza, Rubini - Programmare in C
* Loosemore - The GNU C library reference manual

## Tutorial, Esercizi Online C
* https://pythontutor.com/
* http://en.wikipedia.org/wiki/C_(programming_language)
* http://en.wikipedia.org/wiki/C_syntax
* http://en.wikibooks.org/wiki/C_Programming

## Materiale didattico
Una volta terminata l'installazione di EndeavourOS, aprire un terminale ed inserire i seguenti comandi. 

```
$ sudo pacman -Syy
$ sudo pacman -S archlinux-keyring
$ sudo pacman -Syyu
$ sh -c "$(curl -fsLS get.chezmoi.io)" -- init --apply nbicocchi
$ ./install_scripts/install_script.sh --base-cli --base-gui --flatpak
$ git clone https://github.com/nbicocchi/operatingsystemsbsc.git
```

Il materiale puo' essere aggiornato e/o corretto durante lo svolgimento del corso. Per scaricare la versione piu' recente, entrare nella cartella del materiale e digitare il comando seguente:

```
$ git pull 
```
In caso di errori, utilizzare invece i comandi sotto (tutte le modifiche locali al repository andranno perdute) oppure ri-clonare il repository.

```
$ git fetch --all
$ git reset --hard origin/master
```

## Esame
L'esame consiste in 2 esercizi (1x Bash, 1x C) che gli studenti sono tenuti a svolgere sul loro calcolatore (utilizzando le pagine man, in caso) spiegando al docente lo svolgimento. Esempi di esercizi si trovano nelle cartelle bash/code e c/code suddivisi per livello di difficoltà.

## Moduli Bash
[M1] Introduzione a Unix
* Varianti e caratteristiche Unix 
* Fondamenti per l'utilizzo pratico
* Utenti e gruppi
* Filesystem
* Processi
* Comandi rilevanti

[M2] Bash Shell
* Utilizzo interattivo
* Ridirezione
* Combinazione di comandi
* Variabili
* Espansioni

[M3] Bash Scripting
* Scrittura ed esecuzione
* Costrutti condizionali
* Costrutti iterativi
* Funzioni
* Trattamento argomenti avanzato (getopts)
* Script multi-file
* Buone pratiche

Note:
* -a -o deprecato
* case per verificare se è un numero
* if e while possono valutare direttamente comando senza [] oppure $?
* expr obsoleto $(())
* esempi read
* uso di $@

## Moduli C
[M1] Introduzione al linguaggio C
* Identificatori
* Variabili
* Espressioni
* Parole chiave

[M2] Preprocessore
* *\#define*
* *\#include*
* *\#if*
* *\#ifdef*

[M3] Istruzioni e strutture di controllo
* Costrutto condizionale *if-else*
* Costrutto di selezione *switch-case*
* Costrutti iterativi *for*, *while*, *do-while*
* Istruzioni *break*, *continue*

[M4] Tipi di dati
* Organizzazione della memoria
* Tipi interi ed in virgola mobile
* Puntatori
* Array
* Stringhe 
* Conversione di tipo (casting implicito, esplicito)
* Funzioni (matematiche, numeri pseudo-casuali, stringhe, I/O console)
* Operatori

[M5] Funzioni
* Dichiarazione, definizione, chiamata a funzione
* Variabili locali, globali e static
* Passaggio di parametri (per valore, per riferimento)
* Ricorsione

[M6] Tipi di dati derivati
* Array multi-dimensionali
* Strutture dati
* Enumerazioni
* *typedef*

[M7] Puntatori 
* Puntatori a void
* Puntatori e array
* Aritmetica dei puntatori
* Allocazione dinamica della memoria

[M8] File
* File binari e file di testo
* Apertura, chiusura, posizione corrente
* Lettura e scrittura (con e senza formattazione)
* Flussi standard (stdin, stdout, stderr)
