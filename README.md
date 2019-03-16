# Operating Systems BSc (DIEF, UNIMORE) #
Il corso tratta due aspetti fondamentali della gestione dei sistemi Unix:
(a) l'utilizzo della shell e (b) la programmazione di sistema utilizzando il linguaggio C
e le principali system calls.

## Come usare il materiale ##
L'intero materiale puo' essere scaricato con il comando seguente:

* git clone https://github.com/nbicocchi/operatingsystemsbsc.git

Il materiale puo' essere aggiornato e/o corretto durante lo svolgimento del corso.
Per scaricare la versione piu' recente, entrare nella cartella del materiale e
digitare il comando seguente:

* $ git pull (in caso di errori: git reset --hard; git pull)

## Moduli (Bash) ##

[M1] Introduzione alla shell

* Guida all'installazione di Ubuntu Linux. Introduzione a vim (vimtutor). Uso della shell: console grafica e testuale. Comandi cd, pwd, ls, ln, cp, mv, rm, mkdir, rmdir, echo, cat, grep, true, false, expr; variabili d'ambiente; permessi di accesso ai file usando chmod e chown; ridirezione; piping; man e la documentazione in linea.

[M2] Script shell

* Struttura shell script, variabili, parametri a linea di comando, costrutti for, test, [, e case.

[M3] Ricerca ricorsiva I

* Esercizi avanzati (ricerche ricorsive) risolti mediante l'utilizzo di due script. Il primo per controllare i parametri, il secondo per effetuare la ricerca ricorsiva. Variabile d'ambiente PATH.

[M4] Ricerca ricorsiva II

* Esercizi avanzati (ricerche ricorsive) risolti mediante l'utilizzo di funzioni. Introduzione all'utilizzo di una semplice libreria.

## Moduli (C) ##

[M1] Linea di comando, accesso ai file, gcc e make

* Funzioni read(), write(), open() e differenze rispetto a fread(), fwrite(), fopen(). Il parsing degli argomenti a linea di comando (variabili argc, argv). Introduzione alla compilazione con gcc e make.

[M2] Gestione dei processi

* Le system call fork(), exec(), e wait() per generare e sincronizzare processi paralleli. Utilizzo esclusivo e condiviso di file descriptors.

[M3] Comunicazione fra processi

* Comunicazione fra processi utilizzando la system call pipe(). Costruzione di diverse topologie di comunicazione e di gerarchie di processi, attraverso la configurazione dei lati di una pipe.

[M4] Segnali fra processi

* Sincronizzazione fra processi utilizzando i segnali. System calls signal(), alarm(), sleep(), pause(), utilizzo avanzato di wait(). Ripasso puntatori a funzione.

