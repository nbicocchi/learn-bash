# Esercitazione Bash #2
Per utilizzare questa guida con vim utilizzare i seguenti due comandi 

>:set wrap 
>
>:set linebreak
>
>:set number

## Esercizi
01. (es21.sh) Scrivere uno script che accetta 2 argomenti. Lo script crea un file regolare vuoto il cui nome è specificato dal primo argomento ed i cui permessi (notazione ottale) sono specificati dal secondo parametro.

02. (es22.sh) Scrivere uno script che accetta 1 argomento. Lo script crea un file regolare il cui nome è specificato dal primo argomento. Il file creato deve a sua volta essere uno script che, quando eseguito, stampa la stringa "Hello World!".

03. (es23.sh) Scrivere uno script che controlla di essere invocato con 1 argomento che rappresenta un nome di directory esistente e leggibile nel filesystem.

04. (es24.sh) Scrivere uno script che controlla di essere invocato con 2 argomenti. Il primo argomento deve rappresentare una directory esistente e scrivibile (D), il secondo un nome di file (F). Lo script crea all'interno della directory D un file di nome F contenente il suo percorso assoluto.

05. (es25.sh) Scrivere uno script che riporta su stdout il primo e l'ultimo argomento con cui è stato invocato.

06. (es26.sh) Scrivere uno script che accetta 1 argomento e che verifica se tale argomento rappresenta un nome assoluto, relativo, o relativo semplice.

07. (es27.sh) Scrivere uno script che visualizza tutti i file della directory corrente. Tutti i file con estensione .sh devono essere stampati su stderr invece che stdout. 

08. (es28.sh) Scrivere uno script che visualizza tutti i file della directory corrente che contengono la stringa #!/bin/sh

09. (es29.sh) Scrivere uno script che controlla di essere invocato con 1 argomento e che tale argomento rappresenta un nome di directory esistente. Lo script scorre il contenuto della directory e stampa una F prima di ogni file regolare ed una D prima di ogni directory. Lo script infine riporta su stdout il numero totale di file e di directory stampate.

10. (es210.sh) Scrivere una script che controlla di essere invocato con 2 argomenti che rappresentano una directory (D) e un numero positivo (N). Lo script, 1 volta ogni N secondi (vedi sleep), conta i file e le directory presenti in D. Se il numero cambia rispetto al controllo precedente, stampa un messaggio di avviso.




