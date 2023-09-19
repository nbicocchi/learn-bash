# Programmazione di Sistema - DIEF/UNIMORE
Comunicazione fra processi utilizzando la system call pipe(). Costruzione di diverse topologie di comunicazione e di gerarchie di processi, attraverso la configurazione dei lati di una pipe. Introduzione ad una scrittura sintetica del makefile.

Note: per utilizzare questa guida con vim utilizzare i seguenti due comandi 
```
:set wrap 
:set linebreak
```
## Introduzione ##
La system call pipe() genera una coppia di file descriptors (memorizzati all'interno di una coppia di interi int[2]) che possono essere utilizzati per far comunicare una coppia di processi. In particolare facendo seguire una chiamata fork() ad una chiamata pipe(), i file descriptors generati sono condivisi fra i due processi. In questo modo un processo può scrivere su un lato della pipe, mentre l'altro può leggere sull'altro lato.

Ad esempio:
```
int p[2];
pipe(p);
pid = fork();
if (pid == 0) [
	/* processo figlio */
	read(p[0]...)
else if (pid > 0) {
	/* process padre */
	write(p[1]...)
```

E' molto importante ricordare che TUTTE le pipe generate PRIMA di una chiamata fork() sono condivise da tutti i processi creati in modo indiscriminato (sia lettura che scrittura). Ad esempio, in caso abbia creato tre processi (un padre e due figli) e due pipe (una per figlio) otterrò inizialmente una situazione di questo genere:

```
          PIPE1 PIPE2
PADRE       RW    RW
FIGLIO1     RW    RW
FIGLIO2     RW    RW
```

In questa situazione, dal punto di vista del kernel, ognuno dei tre processi può sia leggere che scrivere su entrambe le pipe. Questo fatto, che può sembrare una sottigliezza, è in realtà molto rilevante. Infatti, il comportamento di read() e write() chiamate su una pipe dipende proprio dal numero di lettori e scrittori collegati alla pipe in ogni dato istante. Ad esempio, la write() fallirà se invocata su una pipe senza lettori mentre sarà bloccante in caso esistano lettori. Viceversa, una read() può fallire o essere bloccante in caso esistano oppure no degli scrittori.

Di conseguenza, lo schema che abbiamo ottenuto può condurre ad una grande varietà di errori. Ad esempio uno dei figli potrebbe terminare senza che nè il padre nè l'altro figlio vengano notificati dal kernel. Questo avviene perchè sulle pipe esistono comunque sa lettori che scrittori (i.e., sia il padre che il figlio superstite hanno aperto la pipe sia in lettura che scrittura).

Per ovviare al problema è necessario chiudere TUTTI i lati delle pipe che non vengono utilizzati al fine di ottenere la topologia di comunicazione desiderata. Ad esempio, se volessimo scrivere un sorgente in cui il padre scrive ad entrambi i figli e termina, dovremmo ottenere una situazione come la seguente:

```
          PIPE1 PIPE2
PADRE       W     W
FIGLIO1     R     
FIGLIO2           R
```

In questo modo, informiamo il kernel riguardo l'utilizzo delle varie pipe e verremo notificati di tutte le situazioni che impediranno il comportamento previsto! Per quando detto fino ad ora, è quindi necessario prestare molta attenzione al punto nel codice in cui costruiamo la topologia di comunicazione chiudendo i lati delle pipe non necessari!

## Esercizi ##
01. 1 pipe per N processi figli. Far creare al padre N processi (con N valore del primo argomento) ed utilizzare una singola pipe per passare una struttura di dati test_pipe da ogni figlio al padre.

02. N pipe per N processi figli. Far creare al padre N processi (con N valore del primo argomento) ed utilizzare una pipe per ogni processo figlio. Dal padre, leggere le strutture in modo ordinato, prima dall’ultimo figlio poi dal penultimo e cosi' via fino al primo. 
Nota: Questa modalità è la più frequentemente utilizzata in contesti reali. Un problema viene risolto in modo parallelo utilizzando più processi figli, ognuno dei quali ritorna il proprio risultato al padre.

03. N pipe per N processi figli. Far creare al padre N processi (con N valore del primo argomento) ed utilizzare una pipe per ogni processo figlio ma diretta dal padre verso il figlio. Ogni figlio attende un carattere poi stampa il proprio pid su stdout. Il padre manda un carattere ad ogni figlio. 
Nota: In questo caso la pipe non viene utilizzata per scambiare dati ma come segnale di controllo.

04. N+1 pipe per N processi figli (pipeline chiusa). Far creare al padre N processi (con N valore del primo argomento) ed utilizzare una pipe per collegare ogni processo figlio al successivo (il padre va collegato sia al primo che all'ultimo figlio). Il padre invia un carattere al primo figlio, il quale stampa il proprio pid poi invia un carattere al secondo che, dopo aver stampato il proprio pid, attiva il successivo...
Nota: In questo caso la pipe non viene propriamente utilizzata per scambiare dati ma come segnale di controllo.

05. N pipe per N processi figli (pipeline aperta). Far creare al padre N processi (con N valore del primo argomento) ed utilizzare una pipe per collegare ogni processo figlio al successivo (il padre va collegato solo all'ultimo figlio). Il primo figlio stampa il proprio pid ed invia un carattere al secondo figlio, il quale stampa il proprio pid ed invia un carattere al terzo che, dopo aver stampato il proprio pid, attiva il successivo...
Nota: In questo caso la pipe non viene propriamente utilizzata per scambiare dati ma come segnale di controllo.

06. N pipe per N processi figli (pipeline aperta all'indietro). Far creare al padre N processi (con N valore del primo argomento) ed utilizzare una pipe per collegare ogni processo figlio al precedente (il padre va collegato solo all'ultimo figlio). Il padre invia un carattere all'ultimo figlio, il quale stampa il proprio pid poi invia un carattere al penultimo che, dopo aver stampato il proprio pid, attiva il precedente...
Nota: In questo caso la pipe non viene propriamente utilizzata per scambiare dati ma come segnale di controllo.

07. Gerarchia multi-livello. Far creare al padre N processi (con N valore del primo argomento) ed utilizzare una pipe per ogni processo figlio. Ogni processo figlio generi M pipe (con M valore del secondo argomento) per comunicare con M nipoti. Il padre attiva tutti i figli inviando un carattere. I figli, dopo averlo ricevuto, sbloccano tutti i nipoti inviando a loro volta lo stesso carattere. Ogni processo stampa il proprio pid, il pid del genitore ed esce dopo aver atteso tutti i suoi eventuali figli. Il padre, di conseguenza, dovrà essere l'ultimo a terminare.

08. Gerarchia multi-livello con utilizzo di exec(). Far creare al padre N processi (con N pari al numero dei parametri ognuno dei quali corrisponde ad un file di testo) ed utilizzare una pipe per ogni processo figlio. Ogni processo figlio generi 1 pipe per comunicare con 1 nipote. I nipoti utilizzino exec() per eseguire il comando wc al fine di contare il numero di linee del file associato. Il padre deve ricevere da tutti figli (i quali lo hanno ricevuto dai nipoti) il numero di linee di ogni file passato come parametro.

09. 2N pipe per N processi figli (full-duplex). Far creare al padre N processi figli ed utilizzare 2 pipe per ogni processo figlio. Il padre scrive al figlio (utilizzando una delle due pipe) una struttura test_primes (vedi utils.h) che contiene "int numbers[NPRIMES]" e "char is_prime[NPRIMES]". Il figlio riceve la struttura e verifica quali degli NPRIMES interi sono numeri primi. Se numbers[i] è primo, allora is_prime[i] = 1, altrimenti is_prime[i] = 0. Dopo l'analisi il figlio invia la struttura compilata con i risultati al padre utilizzando la seconda pipe. Il padre visualizza i risultati.
