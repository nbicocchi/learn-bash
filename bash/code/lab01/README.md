# Esercitazione Bash #1 
Per utilizzare questa guida con vim utilizzare i seguenti due comandi 

>:set wrap 
>
>:set linebreak
>
>:set number

## Esercizi 
1. Elencare i file nella directory corrente
2. Elencare i file nella directory corrente visualizzando i permessi associati, comprendendo anche i file nascosti (che iniziano con punto)
3. Visualizzare il percorso assoluto della directory corrente
4. Spostarsi alla radice del filesystem
5. Ritornare alla propria home indicandone il nome in modo assoluto
6. Spostarsi alla radice del filesystem
7. Ritornare alla propria home utilizzando il comando cd senza argomenti
8. Copiare il file /etc/passwd nella directory corrente
9. Copiare il file /etc/passwd nella directory corrente attribuendo al nuovo file il nome passwd.alt
10. Verificare che i file passwd e passwd.alt siano identici utilizzando il comando diff
11. Cancellare i file passwd e passwd.alt con un'unica istruzione
12. Utilizzare cat e la ridirezione in input per visualizzare il contenuto di /etc/passwd
13. Utilizzare echo e la ridirezione della shell per creare un file test contenente la linea "GNU is Not Unix" 
14. Invocare cat per visualizzare il contenuto del file test
15. Rendere il file test leggibile da tutti gli utenti
16. Rendere il file test leggibile e scrivibile dal solo proprietario
17. Costruire un link hard da test a test2
18. Costruire un link soft (simbolico) da test a test3. Qual'e' la differenza fra la copia di un file e la creazione di link hard e link soft?
19. Creare una directory nella propria home di nome testdir
20. Invocare ls per visualizzare il contenuto di testdir
21. Creare un file vuoto all'interno di testdir senza cambiare directory
22. Eliminare la directory testdir
23. Combinare il comando ps aux con il comando grep usando un file temporaneo per individuare i processi che eseguono una shell (e.g., bash, mosh, dash, sh)
24. Combinare il comando ps aux con il comando grep usando una pipe per individuare i processi che eseguono una shell (e.g., bash, mosh, dash, sh)
25. Cosa e' cambiato? Il sistema operativo ha creato un file temporaneo oppure no?
26. Utilizzare i comandi ps, grep e wc per contare i processi che eseguono con i diritti del nostro utente e salvare risultato all'interno di un file di log
27. Invocare i comandi true e false e visualizzarne il valore di uscita
28. Utilizzare il comando expr per sommare e moltiplicare 3 e 7
29. Creare la variabile d'ambiente LOGFILE ed assegnarle il valore "service.log"
30. Visualizzare il contenuto della variabile LOGFILE
31. Verificare che LOGFILE sia una variabile d'ambiente
32. Visualizzare PID della shell correntemente in esecuzione
33. Visualizzare il nome del proprio utente
34. Creare lo script test.sh contenente la sola linea #!/bin/bash. A cosa serve questa linea?
35. Aggiungere a test.sh la linee "echo Hello World!" e "exit 0"
36. Rendere eseguibile test.sh
37. Eseguire test.sh
38. Spostare test.sh all'interno della cartella /tmp
39. Eseguire test.sh rimanendo nella propria home directory
40. Aprire la pagina di manuale del comando apropos. Successivamente, utilizzare apropos per cercare le pagine di manuale del comando basename

## Soluzioni 
1. Elencare i file nella directory corrente
>$ ls

2. Elencare i file nella directory corrente visualizzando i permessi associati, comprendendo anche i file nascosti (che iniziano con punto)
>$ ls -al

3. Visualizzare il percorso assoluto della directory corrente
>$ pwd

4. Spostarsi alla radice del filesystem
>$ cd /

5. Ritornare alla propria home indicandone il nome in modo assoluto
>$ cd /home/nicola # oppure
>
>$ cd "$HOME"

6. Spostarsi alla radice del filesystem
>$ cd /

7. Ritornare alla propria home utilizzando il comando cd senza argomenti
> $ cd

8. Copiare il file /etc/passwd nella directory corrente
> $ cp /etc/passwd .

9. Copiare il file /etc/passwd nella directory corrente attribuendo al nuovo file il nome passwd.alt
> $ cp /etc/passwd passwd.alt

10. Verificare che i file passwd e passwd.alt siano identici utilizzando il comando diff
>$ diff passwd passwd.alt; echo $?

11. Cancellare i file passwd e passwd.alt con un'unica istruzione
> $ rm passwd*

12. Utilizzare cat e la ridirezione in input per visualizzare il contenuto di /etc/passwd
> cat < /etc/passwd 

13. Utilizzare echo e la ridirezione della shell per creare un file test contenente la linea "GNU is Not Unix" 
>$ echo "GNU is Not Unix" > test

14. Invocare cat per visualizzare il contenuto del file test
> $ cat test

15. Rendere il file test leggibile da tutti gli utenti
> $ chmod a+r test

16. Rendere il file test leggibile e scrivibile dal solo proprietario
> $ chmod 600 test

17. Costruire un link hard da test a test2
> ln test test2

18. Costruire un link soft (simbolico) da test a test3. Qual'e' la differenza fra la copia di un file e la creazione di link hard e link soft?
> $ ln -s test test3
>
> La differenza sostanziale fra copia, link hard e link soft consiste nel modo 
in cui viene utilizzato lo spazio fisico sul disco. In particolare: (a) cp duplica i dati, (b) ln crea un riferimento a dati esistenti, (c) ln -s crea un piccolo file che contiene il percorso di un secondo file (e.g., collegamenti di windows)

19. Creare una directory nella propria home di nome testdir
>$ mkdir testdir

20. Invocare ls per visualizzare il contenuto di testdir
>$ ls testdir

21. Creare un file vuoto all'interno di testdir senza cambiare directory
>$ touch testdir/empty

22. Eliminare la directory testdir
>$ rm -r testdir # oppure
>
> $ rm -rf testdir

23. Combinare il comando ps aux con il comando grep usando un file temporaneo per individuare i processi che eseguono una shell (e.g., bash, mosh, dash, sh)
>$ ps aux > tempfile; grep bash tempfile 

24. Combinare il comando ps aux con il comando grep usando una pipe per individuare i processi che eseguono una shell (e.g., bash, mosh, dash, sh)
>ps aux | grep bash

25. Cosa e' cambiato? Il sistema operativo ha creato un file temporaneo oppure no?
>La pipe e' utile proprio per consentire a processi differenti di comunicare SENZA utilizzare il filesystem, ma collegando lo stdout del primo processo 

26. Utilizzare i comandi ps, grep e wc per contare i processi che eseguono con i diritti del nostro utente e salvare risultato all'interno di un file di log
>ps aux | grep nicola | wc -l > log

27. Invocare i comandi true e false e visualizzarne il valore di uscita
>$ true; echo $?
>
>$ false; echo $?

28. Utilizzare il comando expr per sommare e moltiplicare 3 e 7
>$ expr 3 + 7; expr 3 \* 7

29. Creare la variabile d'ambiente LOGFILE ed assegnarle il valore "service.log"
>$ export LOGFILE="service.log"

30. Visualizzare il contenuto della variabile LOGFILE
>$ echo "$LOGFILE"

31. Verificare che LOGFILE sia una variabile d'ambiente
>$ bash # apertura di una sotto shell
>
>$ echo "$LOGFILE"

32. Visualizzare PID della shell correntemente in esecuzione
>$ ps # leggere il pid associato al processo bash

33. Visualizzare il nome del proprio utente
>$ whoami

34. Creare lo script test.sh contenente la sola linea #!/bin/bash. A cosa serve questa linea?
>$ echo '#!/bin/sh' > test.sh
>
>La linea #!/bin/sh definisce il percorso dell'interprete dei comandi da utilizzare per eseguire cio' che segue. Ad esempio, per uno script python, si può usare #!/usr/bin/python3

35. Aggiungere a test.sh la linee "echo Hello World!" e "exit 0"
>$ echo "echo \"Hello World!\"" >> test.sh
>
>$ echo "exit 0" >> test.sh

36. Rendere eseguibile test.sh
>$ chmod 755 test.sh

37. Eseguire test.sh
>$ ./test.sh

38. Spostare test.sh all'interno della cartella /tmp
>$ mv test.sh /tmp/

39. Eseguire test.sh rimanendo nella propria home directory
>$ /tmp/test.sh

40. Aprire la pagina di manuale del comando apropos. Successivamente, utilizzare apropos per cercare le pagine di manuale del comando basename
>$ man apropos
>
>$ apropos basename


