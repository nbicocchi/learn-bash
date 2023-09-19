# Esercitazione Bash #4
Per utilizzare questa guida con vim utilizzare i seguenti due comandi 

>:set wrap 
>
>:set linebreak
>
>:set number

## Esercizi
01. (es41.sh) Lo script prevede 2 parametri. Il parametro -d specifica il nome assoluto di una directory. Il parametro -m può assumere due valori EQ|NE. Lo script cerca ricorsivamente nella directory indicata da -d, tutte le directory in cui il numero di file contenuti e il numero di sotto directory contenute sia uguale (se -m=EQ) o diverso (se -m=NE). 

**usage: $0 [-h] -d dirname -m EQ|NE**

02. (es42.sh) Lo script prevede un numero variabile di parametri. Il parametro -f indica un nome semplice di file, mentre gli altri devono essere nomi assoluti di directory (d1, ..., dn). Per ognuna delle n directory, lo script cerca al suo interno tutti i file leggibili di nome indicato da -f. Lo script stampa su stdout la somma delle dimensioni dei file trovati sia per ogni directory d1, ..., dn che globalmente.

**usage: $0 [-h] -f filename d1 .. dn**

03. (es43.sh) Lo script prevede un numero variabile di parametri. Il parametro -f indica un nome semplice di file. Il parametro -l indica un numero positivo. Se -l non viene utilizzato il valore di default è 10. Gli altri devono essere nomi assoluti di directory (d1, ..., dn). Per ognuna delle n directory, lo script cerca al suo interno tutti i file leggibili di nome indicato da -f la cui dimensione in linee sia maggiore o uguale al valore indicato da -l. Per ogni file trovato, lo script ne riporta la penultima linea all'interno del file /tmp/script.log.

**usage: $0 [-h] [-l lines] -f filename d1 .. dn**

04. (es44.sh) Lo script prevede un numero variabile di parametri. Il parametro -f indica un nome semplice di file, mentre gli altri devono essere nomi assoluti di directory (d1, ..., dn). Per ognuna delle n directory, lo script cerca al suo interno tutti i file leggibili di nome indicato da -f. Per ogni file trovato, lo script ne riporta il nome e la dimensione (in bytes e in linee) all'interno del file /tmp/script.log con il seguente formalismo: nomefile:bytes:linee.

**usage: $0 [-h] -f filename d1 .. dn**

05. (es45.sh) Lo script prevede un numero variabile di parametri che rappresentano nomi assoluti di directory (d1, ..., dn). Per ognuna delle n directory, lo script cerca al suo interno tutti i file leggibili modificati nelle ultime 24h (vedi opzioni del comando find). Per ogni file trovato, lo script ne riporta il nome su stdout e ne crea un link simbolico all'interno della cartella /tmp/links. Per evitare omonimie i link terminano con un intero crescente. Ad esempio, fa.1, fb.2, .. , fxyz.n

**usage: $0 [-h] d1 .. dn**

06. (es46.sh) Lo script prevede 3 parametri. Il parametro -d specifica il nome assoluto di una directory. I parametri -a, -b rappresentano numeri positivi (A),(B). Lo script cerca ricorsivamente nella directory indicata da -d, tutte le directory in cui la somma delle dimensioni dei file leggibili presenti è compresa fra A e B. Tutte le directory trovate, vengono inoltre salvate all'interno del file /tmp/script.log e ordinate in base alla somma delle dimensioni dei file contenuti.

**usage: $0 [-h] -a A -b B -d dirname**

07. (es47.sh) Lo script prevede un numero variabile di parametri che rappresentano nomi semplici di file (f1, ..., fn). Lo script cerca ricorsivamente nella directory indicata da -d, tutte le directory che contengono almeno un file fra quelli indicati. Tutte le directory trovate, vengono salvate all'interno del file /tmp/script.log e ordinate per il numero di file trovati fra quelli indicati.

**usage: $0 [-h] -d dirname f1 .. fn**

08. (es48.sh) Lo script prevede un numero variabile di parametri che rappresentano nomi semplici di file (f1, ..., fn). Lo script verifica che *globalmente* nella directory indicata da -d, esistano i files f1 .. fn. In caso non siano tutti presenti, lo script mostra i nomi dei files non trovati.

**usage: $0 [-h] -d dirname f1 .. fn**

09. (es49.sh) Lo script prevede un numero variabile di parametri che rappresentano nomi assoluti di directory (d1, ..., dn). Lo script prevede inoltre l'utilizzo del parametro -t per specificare un'estensione di file. Lo script calcola la dimensione media (in bytes) dei file che terminano con l'estensione indicata per ogni directory indicata e mostra il risultato ordinato in modo decrescente.

**usage: $0 [-h] -t extension d1 .. dn**