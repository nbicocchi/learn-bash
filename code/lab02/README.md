# Esercitazione Bash #2
Per utilizzare questa guida con vim utilizzare i seguenti due comandi 

>:set wrap 
>
>:set linebreak
>
>:set number

## Esercizi
01. Creare una directory con nome `esercizi` e spostarsi al suo interno con un solo comando concatenato (*mkdir, cd*).
02. Copiare il file `/etc/passwd` nella directory corrente (*cp*).
03. Visualizzare le prime 10 righe del file `/etc/passwd` (*head*).
04. Visualizzare le penultime 5 righe del file `/etc/passwd` (*head, tail*).
05. Contare il numero di utenti nel sistema (*wc*).
06. Visualizzare l'elenco degli utenti con shell bash (*cat*, *cut*, *grep*).
07. Creare un *alias* per il comando `ls -al` (*alias*).
08. Visualizzare l'elenco dei file nella directory corrente ordinati per dimensione (*ls*).
09. Visualizzare l'elenco dei file nella directory corrente ordinati per data di modifica (*ls*).
10. Creare un file con nome `esempio.txt` e scrivere al suo interno `Questa è una riga di testo` (*echo*).
11. Appendere `Questa è la seconda riga di testo` al file `esempio.txt` (*echo*).
12. Visualizzare il contenuto del file `esempio.txt` (*cat*).
13. Visualizzare l'elenco dei file nella directory corrente con estensione `.txt` (*ls*).
14. Visualizzare l'elenco dei file nella directory `/etc` con dimensione superiore a 100 KB (*find*).
15. Eliminare il file `esempio.txt` (*rm*).
16. Cambiare la directory corrente in `/tmp` (*cd*).
17. Visualizzare la directory corrente (*pwd*).
18. Uscire dalla shell (*exit*).
19. Definire una variabile `nome`, assegnarle il proprio nome, e stamparla (*echo*).
20. Definire una variabile `cognome`, assegnarle il proprio cognome, e stamparla (*echo*).
21. Concatenare le variabili `nome` e `cognome` in un'unica stringa (*echo*).
22. Creare una variabile `numero` con il valore 42, incrementarla di 10 e stamparla.
23. Creare una variabile `lista` contenente tutti i file nella directory corrente e stamparla (*ls*).
24. Stampare il nome del file più recentemente modificato nella directory corrente dopo averlo assegnato ad una variabile (*ls, head*).
25. Creare una variabile `comando` contenente il comando *date* ed eseguire `comando` per ottenere la data corrente.
26. Calcolare la somma dei numeri da 1 a 5 utilizzando l'espansione aritmetica.
27. Visualizzare l'elenco dei file nella directory corrente che iniziano per la lettera `a` (*ls*).
28. Visualizzare l'elenco dei file nella directory `/etc` che contengono la parola `config` (*grep*).
29. Ordinare i file nella directory corrente per dimensione in ordine decrescente (*ls*).
30. Visualizzare le prime 10 righe del file `/etc/passwd` ordinati per nome utente (*sort, head*).
31. Trovare tutte le directory all'interno di `/etc` che non sono accessibili e mostrare solo i messaggi di errore (*find*).
32. Creare un file di 10 KB con caratteri casuali usando il file `/dev/urandom` (*dd*).
33. Eseguire il comando *ls* solo se il comando *true* ha successo (*true, ls*).
34. Contare il numero di utenti unici nel file `/etc/passwd` (*sort, uniq, wc*).
35. Eseguire un comando che stampi il risultato dell'operazione aritmetica 3 * (2 + 5).
36. Contare il numero di directory nella directory corrente (*ls, grep, wc*).
37. Stampare la stringa `La directory corrente è -- nome directory corrente --` (*pwd*).
38. Invocare i comandi *true* e *false* e visualizzarne il valore di uscita (*true, false*).
39. Mostrare il testo `Directory non trovata` se il comando *ls* fallisce su una directory non esistente (*ls*).
40. Se la copia del file `file1.txt` in `file2.txt` fallisce, mostrare un messaggio di errore (*cp, echo*).
41. Utilizzare la ridirezione in input per visualizzare il contenuto di `/etc/passwd` (*cat*).
42. Utilizzare la ridirezione in output per creare un file `test` contenente la linea `GNU is Not Unix` (*echo*).
43. Individuare tutti i processi che eseguono una shell (e.g., bash, zsh, ...) utilizzando un file temporaneo (*ps aux, grep*).
44. Individuare tutti i processi che eseguono una shell (e.g., bash, zsh, ...) utilizzando una pipe (*ps aux, grep*).
45. Cosa e' cambiato? Il sistema operativo ha creato in modo automatico un file temporaneo oppure no?
46. Contare tutti i processi che eseguono con i diritti del nostro utente e salvare risultato all'interno di un file di log (*ps, grep, wc*).
47. Creare la variabile d'ambiente `LOGFILE` ed assegnarle il valore `service.log` (*export*).
48. Visualizzare il contenuto della variabile `LOGFILE` (*echo*).
49. Verificare che `LOGFILE` sia una variabile d'ambiente.
50. Elencare tutti i nomi di file della directory corrente che iniziano con un carattere numerico (*echo*).

## Soluzioni
01. Creare una directory con nome `esercizi` e spostarsi al suo interno con un solo comando concatenato (*mkdir, cd*).
> mkdir esercizi; cd esercizi

02. Copiare il file `/etc/passwd` nella directory corrente (*cp*).
> cp /etc/passwd ./

03. Visualizzare le prime 10 righe del file `/etc/passwd` (*head*).
> head -n 10 /etc/passwd

04. Visualizzare le penultime 5 righe del file `/etc/passwd` (*head, tail*).
> tail -n 10 /etc/passwd | head -n 5

05. Contare il numero di utenti nel sistema (*wc*).
> wc -l /etc/passwd

06. Visualizzare l'elenco degli utenti con shell bash (*cat*, *cut*, *grep*).
> cat /etc/passwd | cut -d ":" -f 7 | grep -E "^/bin/bash$"

07. Creare un *alias* per il comando `ls -al` (*alias*).
> alias ll='ls -al'

08. Visualizzare l'elenco dei file nella directory corrente ordinati per dimensione (*ls*).
> ls -lS

09. Visualizzare l'elenco dei file nella directory corrente ordinati per data di modifica (*ls*).
> ls -lt

10. Creare un file con nome `esempio.txt` e scrivere al suo interno `Questa è una riga di testo` (*echo*).
> echo "Questa è una riga di testo" > esempio.txt

11. Appendere `Questa è la seconda riga di testo` al file `esempio.txt` (*echo*).
> echo "Questa è la seconda riga di testo" >> esempio.txt

12. Visualizzare il contenuto del file `esempio.txt` (*cat*).
> cat esempio.txt

13. Visualizzare l'elenco dei file nella directory corrente con estensione `.txt` (*ls*).
> ls \*.txt

14. Visualizzare l'elenco dei file nella directory `/etc` con dimensione superiore a 100 KB (*find*).
> find /etc -size +100k

15. Eliminare il file `esempio.txt` (*rm*).
> rm esempio.txt

16. Cambiare la directory corrente in `/tmp` (*cd*).
> cd /tmp

17. Visualizzare la directory corrente (*pwd*).
> pwd

18. Uscire dalla shell (*exit*).
> exit

19. Definire una variabile `nome`, assegnarle il proprio nome, e stamparla (*echo*).
> nome=John

20. Definire una variabile `cognome`, assegnarle il proprio cognome, e stamparla (*echo*).
> cognome=Doe

21. Concatenare le variabili `nome` e `cognome` in un'unica stringa (*echo*).
> echo "$nome $cognome"

22. Creare una variabile `numero` con il valore 42, incrementarla di 10 e stamparla.
> numero=42; ((numero+=10)); echo $numero

23. Creare una variabile `lista` contenente tutti i file nella directory corrente e stamparla (*ls*).
> lista=$(ls); echo $lista

24. Stampare il nome del file più recentemente modificato nella directory corrente dopo averlo assegnato ad una variabile (*ls, head*).
> file=$(ls -t | head -n 1); echo $file

25. Creare una variabile `comando` contenente il comando *date* ed eseguire `comando` per ottenere la data corrente.
> comando="date"; $comando

26. Calcolare la somma dei numeri da 1 a 5 utilizzando l'espansione aritmetica.
> echo $((1 + 2 + 3 + 4 + 5))

27. Visualizzare l'elenco dei file nella directory corrente che iniziano per la lettera `a` (*ls*).
> ls a*

28. Visualizzare l'elenco dei file nella directory `/etc` che contengono la parola `config` (*grep*).
> grep -r config /etc

29. Ordinare i file nella directory corrente per dimensione in ordine decrescente (*ls*).
> ls -lSr

30. Visualizzare le prime 10 righe del file `/etc/passwd` ordinati per nome utente (*sort, head*).
> sort /etc/passwd | head -n 10

31. Trovare tutte le directory all'interno di `/etc` che non sono accessibili e mostrare solo i messaggi di errore (*find*).
> find /etc -type d 2>/dev/null

32. Creare un file di 10 KB con caratteri casuali usando il file `/dev/urandom` (*dd*).
> dd if=/dev/urandom of=fout bs=1K count=10 

33. Eseguire il comando *ls* solo se il comando *true* ha successo (*true, ls*).
> true && ls

34. Contare il numero di utenti unici nel file `/etc/passwd` (*sort, uniq, wc*).
> sort /etc/passwd | uniq -u | wc -l

35. Eseguire un comando che stampi il risultato dell'operazione aritmetica 3 * (2 + 5).
> echo $((3 * (2 + 5)))

36. Contare il numero di directory nella directory corrente (*ls, grep, wc*).
> ls -l | grep ^d | wc -l

37. Stampare la stringa `La directory corrente è -- nome directory corrente --` (*pwd*).
> echo "La directory corrente è $(pwd)"

38. Invocare i comandi *true* e *false* e visualizzarne il valore di uscita (*true, false*).
> true; echo $?; false; echo $?

39. Mostrare il testo `Directory non trovata` se il comando *ls* fallisce su una directory non esistente (*ls*).
> ls directory_inesistente || echo "Directory non trovata"

40. Se la copia del file `file1.txt` in `file2.txt` fallisce, mostrare un messaggio di errore (*cp, echo*).
> cp file1.txt file2.txt || echo "Errore durante la copia dei file"

41. Utilizzare la ridirezione in input per visualizzare il contenuto di `/etc/passwd` (*cat*).
> cat < /etc/passwd

42. Utilizzare la ridirezione in output per creare un file `test` contenente la linea `GNU is Not Unix` (*echo*).
> echo "GNU is Not Unix" > test

43. Individuare tutti i processi che eseguono una shell (e.g., bash, zsh, ...) utilizzando un file temporaneo (*ps aux, grep*).
> ps aux > tmpfile; grep bash tmpfile

44. Individuare tutti i processi che eseguono una shell (e.g., bash, zsh, ...) utilizzando una pipe (*ps aux, grep*).
> ps aux | grep bash

45. Cosa e' cambiato? Il sistema operativo ha creato in modo automatico un file temporaneo oppure no?
> No, la comunicazione fra i due processi è mediata dal kernel. Non avvengono scritture su disco.

46. Contare tutti i processi che eseguono con i diritti del nostro utente e salvare risultato all'interno di un file di log (*ps, grep, wc*).
> ps -u $(whoami) | grep -v "grep" | wc -l > log

47. Creare la variabile d'ambiente `LOGFILE` ed assegnarle il valore `service.log` (*export*).
> export LOGFILE="service.log"

48. Visualizzare il contenuto della variabile `LOGFILE` (*echo*).
> echo $LOGFILE

49. Verificare che `LOGFILE` sia una variabile d'ambiente.
> env | grep LOGFILE

50. Elencare tutti i nomi di file della directory corrente che iniziano con un carattere numerico (*echo*).
> echo [0-9]*

