# Operating System Course - DIEF UNIMORE #
Struttura shell script, variabili, parametri a linea di comando, costrutti for, test, [, e case. 

Note: per utilizzare questa guida con vim utilizzare i seguenti due comandi 
```
:set wrap 
:set linebreak
:set number
```

## Riferimenti ##
http://tldp.org/HOWTO/Bash-Prog-Intro-HOWTO.html

## Esercizi ##
01. (es21.sh) Creare uno script che crei un file regolare vuoto il cui nome risulta specificato dal primo argomento della linea di comando ed i cui permessi siano impostati con il valore espresso dal secondo argomento

02. (es22.sh) Creare uno script che crei un file regolare il cui nome risulta specificato dal primo argomento della linea di comando ed i cui permessi siano impostati con il valore espresso dal secondo argomento. In particolare, il file creato dovrà a sua volta essere uno script e stampare la linea “GNU is not Unix”

03. (es23.sh) Creare uno script che controlli di essere invocato con esattamente 1 argomento e che tale argomento rappresenti un nome di directory esistente e leggibile nel filesystem

04. (es24.sh) Creare uno script che controlli di essere invocato con esattamente 2 argomenti e, se il primo argomento rappresenta una directory esistente e scrivibile, allora creare al suo interno un file con il nome passato come secondo argomento e contenente il nome assoluto della directory indicata come primo argomento. La directory deve anche essere esplorabile (i.e., eseguibile) ?

05. (es25.sh) Creare uno script che riporti su stdout l'ultimo argomento della linea di comando

06. (es26.sh) Creare uno script che accetti un solo argomento e che verifichi se tale argomento rappresenta un nome assoluto, relativo, o relativo semplice

07. (es27.sh) Creare uno script che visualizzi tutti i file della directory corrente. Tutti i file con estensione .sh devono essere stampati su stderr invece che stdout. 

08. (es28.sh) Creare uno script che visualizzi tutti i file della directory corrente che contengono la stringa #!/bin/sh

09. (es29.sh) Creare uno script che controlli di essere invocato con esattamente 1 argomento e che tale argomento rappresenti un nome di directory esistente. Lo script deve scorrere l'intero contenuto della directory e stampare una F prima di ogni file regolare ed una D prima di ogni directory. Lo script deve anche riportare su stdout il numero totale di file e directory stampate.




