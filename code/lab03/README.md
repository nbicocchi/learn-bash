# Esercitazione Bash #3
Per utilizzare questa guida con vim utilizzare i seguenti due comandi 

>:set wrap 
>
>:set linebreak
>
>:set number

## Esercizi
**(es21.sh)** Scrivere uno script che accetta 2 argomenti. Lo script crea un file regolare vuoto il cui nome è specificato dal primo argomento ed i cui permessi (notazione ottale) sono specificati dal secondo parametro.

**(es22.sh)** Scrivere uno script che accetta 1 argomento. Lo script crea un file regolare il cui nome è specificato dal primo argomento. Il file creato deve a sua volta essere uno script che, quando eseguito, stampa la stringa "Hello World!".

**(es23.sh)** Scrivere uno script che controlla di essere invocato con 1 argomento che rappresenta un nome di directory esistente e leggibile nel filesystem.

**(es24.sh)** Scrivere uno script che controlla di essere invocato con 2 argomenti. Il primo argomento deve rappresentare una directory esistente e scrivibile (D), il secondo un nome di file (F). Lo script crea all'interno della directory D un file di nome F contenente il suo percorso assoluto.

**(es25.sh)** Scrivere uno script che riporta su stdout il primo e l'ultimo argomento con cui è stato invocato.

**(es26.sh)** Scrivere uno script che accetta 1 argomento e che verifica se tale argomento rappresenta un nome assoluto, relativo, o relativo semplice.

**(es27.sh)** Scrivere uno script che visualizza tutti i file della directory corrente. Tutti i file con estensione .sh devono essere stampati su stderr invece che stdout. 

**(es28.sh)** Scrivere uno script che visualizza tutti i file della directory corrente che contengono la stringa #!/bin/sh

**(es29.sh)** Scrivere uno script che controlla di essere invocato con 1 argomento e che tale argomento rappresenta un nome di directory esistente. Lo script scorre il contenuto della directory e stampa una F prima di ogni file regolare ed una D prima di ogni directory. Lo script infine riporta su stdout il numero totale di file e di directory stampate.

**(es210.sh)** Scrivere una script che controlla di essere invocato con 2 argomenti che rappresentano una directory (D) e un numero positivo (N). Lo script, 1 volta ogni N secondi (vedi sleep), conta i file e le directory presenti in D. Se il numero cambia rispetto al controllo precedente, stampa un messaggio di avviso.

---

**(es31.sh)** Scrivere uno script che prevede 1 parametro che deve essere il nome assoluto di una directory (D). Lo script deve esplorare ricorsivamente D e stampare, per ogni sotto cartella, il livello di profondità raggiunto. D avrà livello 0, le sottocartelle di D avranno livello 1, e così via. Da risolvere sia utilizzando una funzione ricorsiva, che utilizzando il comando find. Nel caso di find, l'opzione -printf può essere utile (vedi manuale).

**(es32.sh)** Scrivere uno script che prevede 4 parametri. Il primo parametro deve essere il nome assoluto di una directory (D), il secondo deve essere una stringa (F), il terzo (N1) ed il quarto (N2) vanno trattati come numeri interi positivi. Lo script cerca ricorsivamente in D tutti i file di nome F la cui lunghezza in linee è compresa fra N1 e N2. 

**(es33.sh)** Scrivere uno script che prevede 2 parametri. Il primo parametro deve essere il nome assoluto di una directory (D), mentre il secondo è un singolo carattere numerico (N). Lo script cerca ricorsivamente in D tutti i file che contengono sia nel nome che nel contenuto N.  

**(es34.sh)** Scrivere uno script che prevede 2 parametri. Il primo parametro deve essere il nome assoluto di una directory (D), mentre il secondo va trattato come un numero intero positivo (N). Lo script cerca ricorsivamente in D tutte le directory che contengono un numero di file (solo file non directory) compreso fra 1 e N. 

**(es35.sh)** Scrivere uno script che prevede 2 parametri. Il primo parametro deve essere il nome assoluto di una directory (D), mentre il secondo va trattato come un numero intero positivo (N). Lo script cerca ricorsivamente in D tutte le directory che contengono almeno un file (solo file non directory) con dimensione in byte maggiore di N. Ordinare (in modo decrescente) le directory trovate in base numero di file (che contengono) che rispettano il criterio specificato sopra.

**(es36.sh)** Scrivere uno script che prevede 2 parametri. Il primo parametro deve essere il nome assoluto di una directory (D), mentre il secondo va trattato come un nome semplice di file (F). Lo script cerca ricorsivamente in D tutti i file di nome F, ne stampa il percorso completo su standard output, e mostra anche le prima e le ultime due linee del suo contenuto.

**(es37.sh)** Scrivere uno script che prevede 2 parametri. Il primo parametro deve essere il nome assoluto di una directory (D), mentre il secondo va trattato come un nome semplice di file (F). Lo script cerca ricorsivamente in D tutti i file di nome F, e crea un link simbolico ad ognuno di essi all'interno della cartella /tmp. I link simbolici creati devono avere un nome nella forma /tmp/link_1 .. /tmp/link_n.

**(es38.sh)** Scrivere uno script che prevede 3 parametri. Il primo parametro deve essere il nome assoluto di una directory (D), mentre il secondo ed il terzo vanno trattati come nomi semplici di file (F1), (F2). Lo script cerca ricorsivamente in D tutte le directory che contengono entrambi i file F1 ed F2, ne stampa il percorso completo, e mostra anche la somma della dimensione in byte di F1 ed F2.

**(es39.sh)** Scrivere uno script che prevede 3 parametri. Il primo parametro deve essere il nome assoluto di una directory (D), mentre il secondo ed il terzo vanno trattati come nomi semplici di file (F1), (F2). Lo script cerca ricorsivamente in D per verificare che esistano (anche in directory diverse) almeno 1 file di nome F1 ed almeno 1 file di nome F2. Stampare il numero di occorrenze di F1 ed F2.

---

**(es41.sh)** Lo script prevede 2 parametri. Il parametro -d specifica il nome assoluto di una directory. Il parametro -m può assumere due valori EQ|NE. Lo script cerca ricorsivamente nella directory indicata da -d, tutte le directory in cui il numero di file contenuti e il numero di sotto directory contenute sia uguale (se -m=EQ) o diverso (se -m=NE). 

```
usage: $0 [-h] -d dirname -m EQ|NE
```

**(es42.sh)** Lo script prevede un numero variabile di parametri. Il parametro -f indica un nome semplice di file, mentre gli altri devono essere nomi assoluti di directory (d1, ..., dn). Per ognuna delle n directory, lo script cerca al suo interno tutti i file leggibili di nome indicato da -f. Lo script stampa su stdout la somma delle dimensioni dei file trovati sia per ogni directory d1, ..., dn che globalmente.

```
usage: $0 [-h] -f filename d1 .. dn
```

**(es43.sh)** Lo script prevede un numero variabile di parametri. Il parametro -f indica un nome semplice di file. Il parametro -l indica un numero positivo. Se -l non viene utilizzato il valore di default è 10. Gli altri devono essere nomi assoluti di directory (d1, ..., dn). Per ognuna delle n directory, lo script cerca al suo interno tutti i file leggibili di nome indicato da -f la cui dimensione in linee sia maggiore o uguale al valore indicato da -l. Per ogni file trovato, lo script ne riporta la penultima linea all'interno del file /tmp/script.log.

```
usage: $0 [-h] [-l lines] -f filename d1 .. dn
```

**(es44.sh)** Lo script prevede un numero variabile di parametri. Il parametro -f indica un nome semplice di file, mentre gli altri devono essere nomi assoluti di directory (d1, ..., dn). Per ognuna delle n directory, lo script cerca al suo interno tutti i file leggibili di nome indicato da -f. Per ogni file trovato, lo script ne riporta il nome e la dimensione (in bytes e in linee) all'interno del file /tmp/script.log con il seguente formalismo: nomefile:bytes:linee.

```
usage: $0 [-h] -f filename d1 .. dn
```

**(es45.sh)** Lo script prevede un numero variabile di parametri che rappresentano nomi assoluti di directory (d1, ..., dn). Per ognuna delle n directory, lo script cerca al suo interno tutti i file leggibili modificati nelle ultime 24h (vedi opzioni del comando find). Per ogni file trovato, lo script ne riporta il nome su stdout e ne crea un link simbolico all'interno della cartella /tmp/links. Per evitare omonimie i link terminano con un intero crescente. Ad esempio, fa.1, fb.2, .. , fxyz.n

```
usage: $0 [-h] d1 .. dn
```

**(es46.sh)** Lo script prevede 3 parametri. Il parametro -d specifica il nome assoluto di una directory. I parametri -a, -b rappresentano numeri positivi (A),(B). Lo script cerca ricorsivamente nella directory indicata da -d, tutte le directory in cui la somma delle dimensioni dei file leggibili presenti è compresa fra A e B. Tutte le directory trovate, vengono inoltre salvate all'interno del file /tmp/script.log e ordinate in base alla somma delle dimensioni dei file contenuti.

```
usage: $0 [-h] -a A -b B -d dirname
```

**(es47.sh)** Lo script prevede un numero variabile di parametri che rappresentano nomi semplici di file (f1, ..., fn). Lo script cerca ricorsivamente nella directory indicata da -d, tutte le directory che contengono almeno un file fra quelli indicati. Tutte le directory trovate, vengono salvate all'interno del file /tmp/script.log e ordinate per il numero di file trovati fra quelli indicati.

```
usage: $0 [-h] -d dirname f1 .. fn
```

**(es48.sh)** Lo script prevede un numero variabile di parametri che rappresentano nomi semplici di file (f1, ..., fn). Lo script verifica che *globalmente* nella directory indicata da -d, esistano i files f1 .. fn. In caso non siano tutti presenti, lo script mostra i nomi dei files non trovati.

```
usage: $0 [-h] -d dirname f1 .. fn
```

**(es49.sh)** Lo script prevede un numero variabile di parametri che rappresentano nomi assoluti di directory (d1, ..., dn). Lo script prevede inoltre l'utilizzo del parametro -t per specificare un'estensione di file. Lo script calcola la dimensione media (in bytes) dei file che terminano con l'estensione indicata per ogni directory indicata.

```
usage: $0 [-h] -t extension d1 .. dn
```