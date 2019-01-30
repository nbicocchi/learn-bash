# Operating System Course - DIEF UNIMORE #
Le system call fork(), exec(), e wait() per generare e sincronizzare processi paralleli. Utilizzo esclusivo e condiviso di file descriptors.

Note: per utilizzare questa guida con vim utilizzare i seguenti due comandi 
```
:set wrap 
:set linebreak
```

## Introduzione ##
La chiamata fork() viene utilizzata per consentire ad un processo (padre) di generare un nuovo processo (figlio). Tutti i processi all'interno dei sistemi Unix (ad eccezione del primo processo che viene generato dal kernel) vengono generati attraverso questa modalità. Ad esempio, ogni volta che lanciamo un comando sul prompt di una shell, la shell chiama al suo interno fork(). Dopo la chiamata fork(), esistono due processi identici, con lo stesso codice interno, ma residenti su spazi di indirizzamento diversi. A causa di ciò, le modifiche nella memoria di uno dei due processi (e.g., una modifica ad una variabile) non si propagano nell'altro. Per la comunicazione fra processi si utilizzano infatti direttive apposite (vedi moduli successivi). La chiamata fork() ritorna un valore intero che può assumere tre valori. -1 in caso di errore, 0 nel caso del processo figlio, un numero qualunque positivo nel caso del padre. Il numero intero rappresenta, in questo caso, il PID del processo figlio generato. Da un punto di vista simbolico, la chiamata fork() va intesa come il processo di mitosi che una cellula compie per duplicarsi.

Esempio:
```
pid = fork();
switch (pid) {
		case -1: /* error */
			zprintf(2, "error: fork()\n");
			exit(1);
		case 0: /* child */
			zprintf(1, "[Child] [fork() %d]\n", pid);
			exit(0);
		default: /* father */
			zprintf(1, "[Father] [fork() %d]\n", pid);
			wait(&status);
			exit(0);
}
```

La chiamata wait() viene utilizzata per consentire al processo padre di aspettare il termine dell'esecuzione dei processi figli. Riceve come parametro l'indirizzo di un valore intero che utilizzerà per registrare le condizioni di uscita del processo figlio. Per decifrare i dati memorizzati all'interno di questa variabile di stato è possibile utilizzare delle macro apposite che verificano diverse condizioni di uscita. L'elenco delle macro disponibili è reperibile alla pagina di manuale di wait (man wait) e riportato nelle sue componenti più utilizzate di seguito.

```
WIFEXITED(status)
True if the process terminated normally by a call to _exit(2) or exit(3).

WEXITSTATUS(status)
If WIFEXITED(status) is true, evaluates to the low-order 8 bits of the argument passed to _exit(2) or exit(3) by the child.

WIFSIGNALED(status)
True if the process terminated due to receipt of a signal.

WTERMSIG(status)
If WIFSIGNALED(status) is true, evaluates to the number of the signal that caused the termination of the process.
```

La chiamata exec() viene utilizzata per sostituire il codice di un processo con altro codice binario preso da un file. Esiste in diverse varianti che utilizzano parametri diversi (vedi man exec) ma ha in tutti i casi lo stesso scopo. Ad esempio, ogni volta che lanciamo un comando sul prompt di una shell, la shell chiama al suo interno fork() per duplicarsi e chiama exec() nell'istanza figlio per eseguire il codice contenuto nel file binario da eseguire. Da un punto di vista simbolico, exec() può essere considerato come la sostituzione del dna di una cellula con nuovo dna arbitrario. Ovviamente, esistono implicazioni legate all'utilizzo sicuro di questa chiamata.

## Esercizi ##
01. (es21.c) Scrivere un sorgente C che stampi la stringa "Hello, I'm the father" e crei un processo figlio che stampi la stringa "Hello, I'm the child". Entrambi i processi, inoltre, stampano a video il valore ritornato da fork(). Per quale motivo troviamo su stdout due messaggi (con valori differenti)?

02. (es22.c) La funzione fork() restituisce -1 in caso di errore (in questo caso non genera il nuovo processo). Aggiungere questa verifica associandola ad un opportuno messaggio d’errore. Inoltre, sia il processo padre che il processo figlio hanno un proprio exit value. Utilizzare la funzione wait() per recuperare l’exit value del processo figlio. La wait svolge anche un ruolo di sincronizzazione fra processo padre e processo figlio?

03. (es23.c) Creare un sorgente che generi un numero di figli uguale al numero passato come argomento (usare -n e getopt). Ogni figlio stampi su stdout il proprio indice. Il processo padre attenda la terminazione di tutti i processi figli riportando su stdout le exit value di ogni processo accanto al pid del processo terminato. Per questioni legate alla manutenibilita' del codice, il codice eseguito dai processi figli deve essere contenuto all'interno di una funzione.

04. (es24.c) La funzione waitpid()
	```
	pid_t waitpid(pid_t pid, int *status, int options); 
	```

consente al padre di attendere la terminazione di un processo figlio specifico specificato dal parametro pid. Creare un sorgente che generi un numero di figli uguale al numero passato come argomento (usare -n e getopt). Ogni figlio stampi su stdout il proprio indice. Il processo padre attenda la terminazione di tutti i processi figli in ordine inverso rispetto all'ordine di creazione riportando su stdout le exit value di ogni processo accanto al pid del processo terminato. 

05. (es25.c) Utilizzo di exec(). Creare un sorgente che generi un numero di figli uguale al numero passato come argomento (usare -n e getopt). Ogni figlio esegua al suo interno il comando "echo Hello!"

06. (es26.c) Scrivere un programma che manda in esecuzione un eseguibile il cui nome e' inserito come argomento sulla linea comando e ne aspetta la terminazione.

07. (es27.c) Scrivere un programma che manda in esecuzione un eseguibile il cui nome, compresi eventuali parametri!, sia inserito come argomento sulla linea comando.

08. (es28.c) Si progetti una applicazione concorrente composta da due processi, padre e figlio, tali che il file rappresentato dal primo argomento sia aperto da entrambi per contare i caratteri contenuti leggendoli ad uno ad uno. 

09. (es29.c) Si progetti una applicazione concorrente composta da due processi, padre e figlio, tali che il file rappresentato dal primo argomento sia aperto prima della fork() ed utilizzato in lettura in modo condiviso! per contare i caratteri contenuti leggendoli ad uno ad uno. Cambia qualcosa in caso di file grandi o di file piccoli?

## Soluzioni ##
01. (es21.c) Approfondimento: La funzione fork() ritorna in modo diverso nel caso si tratti del processo padre o del processo figlio. In particolare, ritorna il PID del figlio nel caso del padre, e 0 nel caso del figlio.

02. (es22.c) Approfondimento: Si! La wait viene utilizzata dal padre per attendere la terminazione di tutti i processi figli prima di terminare. Si tratta di un caso di sincronizzazione.

09. (es29.c) Approfondimento: Nel caso di file piccoli, il tempo assegnato ad ogni processo dallo scheduler dei processi e' sufficiente a leggerlo per intero. Al contrario, in caso di file grandi, i due processi si alternano. La somma delle due misure e' pari alla dimensione del file. E' importante ricordare che questo esercizio ha finalità puramente didattiche. Nella pratica dello sviluppo di sistemi industriali, l'utilizzo di file descriptors condivisi fra piu' processi e' sconsigliabile. 

