# Operating System Course - DIEF UNIMORE #
Ripasso fondamenti linguaggio C. Funzioni read(), write(), open() e differenze rispetto a fread(), fwrite(), fopen(). Il parsing degli argomenti a linea di comando (variabili argc, argv) con e senza la funzione getopt(). 
Introduzione alla compilazione con gcc e make.

Note: per utilizzare questa guida con vim utilizzare i seguenti due comandi 
```
:set wrap 
:set linebreak
```

## Introduzione ##
Le funzioni read(), write(), open() sono rappresentative di una famiglia di funzioni per la manipolazione dei file descriptors. E' necessario ricordare che i dati memorizzati all'interno di un file system possono essere manipolati attraverso una molteplicita' di metafore. Ad esempio, i file descriptors associano ad ogni file aperto un numero intero. Al contrario, le funzioni fread(), fwrite(), foopen(), ecc.. manipolano i file utilizzando *FILE (puntatori al tipo FILE). E' anche importante ricordare che mescolare i due approcci puo' causare problemi in fase di esecuzione. Di conseguenza, una volta scelto l'approccio desiderato e' preferibile mantenerlo. Nei nostri esempi, utilizzeremo funzioni che utilizzano file descriptors.

Ogni processo Unix, all'avvio, ha disponibili tre file descriptors: 0, 1, 2. Questi rappresentano tre flussi di dati che partono o arrivano al processo in questione. In particolare, il flusso 0 rappresenta i dati in input, mentre 1 e 2 rappresentano flussi in output. Tutti e tre i flussi, nella maggior parte dei casi, sono collegati ad un terminale (testuale oppure grafico). Per questo motivo, scrivendo caratteri sia su 1 che su 2, non noteremo differenze. L'output appare sempre sul terminale, ma arriva attraverso un percorso differente.

Questi tre flussi standard non vanno aperti in modo esplicito (sono sempre aperti) e corrispondono, nella metafora che utilizza *FILE, a stdin, stdout e stderr.

```
              ------------> 1/stdout (Term)
     0/stdin  |
(Term) -----> P 
              | 
              ------------> 2/stderr (Term)
```

## Esercizi ##
01. (es11.c) Utilizzare l'editor vim per realizzare un sorgente C il cui obiettivo sia quello di emettere su stdout il messaggio "Hello World!" utilizzando (a) la primitiva fprintf(), (2) la primitiva write(), (3) la funzione zprintf (vedi utils). Utilizzare gcc per compilare es11.c. Cosa viene prodotto? Invocare gcc in modo che venga generato un file eseguibile di nome es11 invece di a.out. Come reagisce gcc al parametro -Wall? Mettere in esecuzione es61 visualizzandone l'exit value. In caso non abbiate utilizzato return() o exit(), modificate il sorgente di conseguenza. Mettere in esecuzione es61 verificando che i caratteri emessi siano realmente diretti su stdout provando a ridirigere alternativamente stdout e stderr su /dev/null.

02. (es12.c) Stampare il valore di una variabile intera, di un singolo carattere, di un array di caratteri, di un array di caratteri (come puntatore) utilizzando fprintf().

03. (es13.c) Scrivere un programma che visualizzi tutti gli argomenti presenti nella propria command line (uno per linea) utilizzando fprintf().

04. (es14.c) Scrivere un sorgente C che stampi la stringa "Hello World [%d]!" su stdout(fdescriptor=1) o stderr(fdescriptor=2) in base al numero passato come primo parametro. In caso il parametro sia assente o non corretto, il programma utilizzi stdout. Si popoli la variabile "%d" della stringa da stampare con il valore del file descriptor utilizzato per l'output.

05. (es15.c) Scrivere un sorgente C che apra il file indicato dal primo argomento, sovrascriva i primi 5 caratteri con la stringa "Hello", e tronchi la dimensione del file a 16 caratteri (vedi ftruncate).

06. (es16.c) Scrivere un sorgente C che legga i primi N caratteri (N minore di 100) dal file F e li copi alla posizione K di F. N, F e K rispettivamente primo, secondo e terzo argomento a linea di comando.

07. (es17.c) Implementare una versione del comando head di Unix. Il comando head riporta su stdout le prime linee di un file. In assenza di opzioni sulla command line, le linee stampate sono 10 e il file di input e' stdin. Il comando accetta due parametri, il primo per impostare un numero di linee diverso da 10 e il secondo per aprire un file diverso da stdin.

08. (es18.c) Si progetti un filtro che accetta N parametri che rappresentano nomi di file F1, . . . , FN e riportare su stdout un carattere di ogni file indicato, il primo carattere del primo file F1, l’ultimo carattere dell’ultimo file FN, il secondo carattere del secondo file F2, il penultimo carattere del penultimo file FN-1 e cosi' di seguito. Nel caso in cui un file non abbia numero di caratteri sufficienti a consentire l’estrazione, il filtro deve terminare immediatamente con exit value pari a 1, mentre deve restituire 0 in caso contrario.

09. (es19.c) Si progetti un filtro che accetta un singolo parametro (R). Il filtro deve riportare sullo standard output una selezione dei caratteri dello standard input: in particolare, si deve riportare in uscita un carattere se e solo se non compare nella stringa R oppure compare un numero di volte maggiore di 1.


