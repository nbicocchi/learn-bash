# Operating System Course - DIEF UNIMORE #
Sincronizzazione fra processi utilizzando i segnali. System call signal(), sleep(), utilizzo avanzato di wait(). Utilizzo di puntatori a funzione.

Note: per utilizzare questa guida con vim utilizzare i seguenti due comandi 
```
:set wrap 
:set linebreak
```

## Introduzione ##
La comunicazione (e sincronizzazione) fra processi può essere effettuata attraverso le system call read() e write() utilizzate per leggere e scrivere su una pipe, un file, una socket, etc. Un processo può rimanere bloccato su una chiamata read() in attesa di dati. Non appena i dati sono disponibili, il processo viene sbloccato e riceve i dati di cui era in attesa.

Una seconda forma di comunicazione fra processi (IPC) è basata sull'utilizzo di segnali. Un segnale è una notifica asincrona inviata da un processo (o dal kernel stesso) ad un altro processo. Quando un segnale viene inviato, il processo viene interrotto (durante una qualunque istruzione non atomica). Se il processo ricevente ha resistrato un handler per il segnale ricevuto, l'handler viene eseguito. In caso contrario, viene eseguito l'handler di default.

I segnali sono simili agli interrupt. La differenza principale consiste nel fatto che gli interrupt sono organizzati dalla CPU per gestire il kernel, i segnali sono organizzati dal kernel per gestire i processi.

Per inviare un segnale ad un processo è possibile utilizzare la system call kill(pid_t pid, int sig). Il primo parametro è il pid del processo ricevente, mentre il secondo parametro è il segnale da inviare. Nella tabella sotto sono elencati i segnali disponibili su un sistema OSX Sierra. L'elenco varia leggermente da sistema a sistema.

```
     No    Name         Default Action       Description
     1     SIGHUP       terminate process    terminal line hangup
     2     SIGINT       terminate process    interrupt program
     3     SIGQUIT      create core image    quit program
     4     SIGILL       create core image    illegal instruction
     5     SIGTRAP      create core image    trace trap
     6     SIGABRT      create core image    abort program (formerly SIGIOT)
     7     SIGEMT       create core image    emulate instruction executed
     8     SIGFPE       create core image    floating-point exception
     9     SIGKILL      terminate process    kill program
     10    SIGBUS       create core image    bus error
     11    SIGSEGV      create core image    segmentation violation
     12    SIGSYS       create core image    non-existent system call invoked
     13    SIGPIPE      terminate process    write on a pipe with no reader
     14    SIGALRM      terminate process    real-time timer expired
     15    SIGTERM      terminate process    software termination signal
     16    SIGURG       discard signal       urgent condition present on socket
     17    SIGSTOP      stop process         stop (cannot be caught or ignored)
     18    SIGTSTP      stop process         stop signal generated from keyboard
     19    SIGCONT      discard signal       continue after stop
     20    SIGCHLD      discard signal       child status has changed
     21    SIGTTIN      stop process         background read attempted from control terminal
     22    SIGTTOU      stop process         background write attempted to control terminal
     23    SIGIO        discard signal       I/O is possible on a descriptor (see fcntl(2))
     24    SIGXCPU      terminate process    cpu time limit exceeded (see setrlimit(2))
     25    SIGXFSZ      terminate process    file size limit exceeded (see setrlimit(2))
     26    SIGVTALRM    terminate process    virtual time alarm (see setitimer(2))
     27    SIGPROF      terminate process    profiling timer alarm (see setitimer(2))
     28    SIGWINCH     discard signal       Window size change
     29    SIGINFO      discard signal       status request from keyboard
     30    SIGUSR1      terminate process    User defined signal 1
     31    SIGUSR2      terminate process    User defined signal 2
```

Un'altra modalità (molto semplice) per inviare segnali ad un processo consiste nella pressione di determinate combinazioni di tasti su un terminale. Ad esempio:

```
CTRL-C -> SIGINT(2)
CTRL-Z -> SIGSTOP(18)
CTRL-T -> SIGINFO(29)
```

Ogni processo può definire funzioni handler (callback) per gestire i segnali in arrivo. Utilizzando la system call signal(int sig, sig_t func) è infatti possibile associare il segnale sig alla funzione func. E' interessante notare come la system call signal() ritorni inoltre un tipo sig_t (puntatore a funzione) all'handler associato in precedenza. Questa caratteristica può essere utilizzata, ad esempio, per sostituire temporaneamente l'handler di default per poi riassociarlo al segnale.

Si ricordi che non è possibile definire un handler per tutti i segnali. In particolare per i segnali SIGKILL e SIGSTOP non è possibile definire alcun handler alternativo. SIGKILL determina la terminazione immediata del processo. SIGSTOP sospende il processo. L'esecuzione riprende ricevendo il segnale SIGCONT.

Interessante notare come la procedura di shutdown dei sistemi Unix sia basata sui segnali. In particolare, a tutti i processi viene inviato il segnale SIGTERM per consentire loro di intercettarlo e terminare in modo "graceful". Dopo un'attesa predefinita, il kernel invia a tutti i processi restanti il segnale SIGKILL (non intercettabile) per chiuderli forzatamente.

## Esercizi ##
01. (es41.c) Progettare un applicativo che stampi la stringa "Hello ", si sospenda per 3 secondi, e stampi la stringa "World!\n". Si veda la system call sleep().

02. (es42.c) Determinare, con un programma c, il segnale che causa la terminazione di un processo figlio quando tenta di scrivere su una pipe con lato di lettura chiuso. Si vedano le opportune macro per trattare la variabile status scritta da wait(). Che differenze emergono in caso la pipe abbia il lato scrittura chiuso invece di quello lettura?

03. (es43.c) Modificare il precedente sorgente in modo che il segnale di broken pipe (man signal (SIGPIPE)) venga intercettato da un opportuno handler. Si veda la system call signal().

04. (es44.c) Progettare un applicativo (singolo processo) che registri un handler per il segnale SIGINT. L'handler stampa la stringa "CTRL-C Pressed!" e conta il numero di volte in cui è stato richiamato. Dopo la terza volta, reinstalla l'handler di default.

05. (es45.c) Progettare un applicativo concorrente con un padre ed n figli (n da leggere a linea di comando). Il padre utilizza SIGUSR1 e SIGUSR2 per comunicare con i figli. Nel primo caso, i figli stampano una stringa di conferma su stdout, mentre nel secondo terminano.

06.	(es46.c) Progettare un applicativo concorrente che accetta N parametri (N >= 2) che rappresentano N nomi di file (F1...FN) con uguale lunghezza in byte (da verificare). Il processo padre è associato al file FN e deve generare N-1 processi figli (P1...PN-1) associati ai file (F1...FN-1). Ogni processo figlio può ricevere dal padre due signali differenti (S1 o S2): S1 autorizza il processo a leggere un carattere dal file associato e a comunicarlo al padre, mentre S2 determina la terminazione del processo figlio. Il padre, per ogni carattere c_n del file FN, utilizza S1 per sbloccare i figli e ricevere il carattere c_i corrispondente ed S2 per terminare i figli che hanno inviato un carattere c_i != c_n. Il padre stampa su standard output il PID di ogni figlio con l’indicazione di terminazione anormale o normale. Nel secondo caso, riporta anche il nome del file Fi associato (il cui contenuto è uguale a FN).

07.	(es47.c) Progettare un applicativo concorrente che accetta un numero variabile N+1 di parametri. I primi N rappresentano nomi di file (F1...FN), mentre l’ultimo rappresenta un numero intero H. Il processo padre deve generare N processi figli (P1...PN) associati ai file (F1...FN). La topologia di comunicazione è ad anello: il padre comunica con P1, che comunica con P2, fino a PN che comunica con il padre. Per ogni linea, P1 genera una struttura dati S (due interi che rappresentano l'id del figlio e la lunghezza della linea letta), la compila con i propri dati, e la comunica ai figli successivi. Questi ultimi, in caso abbiano letto una linea più lunga di quella di quella annotata in S, modificano la struttura compilandola con i propri dati. Il padre, per ogni linea, riceve quindi l’informazione di quale figlio ha letto la linea di maggiore lunghezza e chiede a tale figlio, utilizzando un segnale, di stamparla su standard output.
