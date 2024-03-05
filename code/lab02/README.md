# Esercitazione Bash #2
Per utilizzare questa guida con vim utilizzare i seguenti due comandi 

>:set wrap 
>
>:set linebreak
>
>:set number

## Esercizi
01. Creare una directory con nome "esercizi" e spostarsi al suo interno (*mkdir* e *cd*).
02. Copiare il file /etc/passwd nella directory corrente (*cp*).
03. Visualizzare le prime 10 righe del file /etc/passwd (*head*).
04. Visualizzare le ultime 5 righe del file /etc/passwd (*tail*).
05. Contare il numero di utenti nel sistema (*wc*).
06. Visualizzare l'elenco degli utenti con shell bash.
07. Creare un *alias* per il comando "ls -l".
08. Visualizzare l'elenco dei file nella directory corrente ordinati per dimensione.
09. Visualizzare l'elenco dei file nella directory corrente ordinati per data di modifica.
10. Creare un file con nome "esempio.txt" e scrivere al suo interno una riga di testo.
11. Appendere una seconda riga di testo al file "esempio.txt".
12. Visualizzare il contenuto del file "esempio.txt".
13. Visualizzare l'elenco dei file nella directory corrente con estensione .txt. (*ls*)
14. Visualizzare l'elenco dei file nella directory /etc con dimensione superiore a 100 KB. (*find*)
15. Eliminare il file "esempio.txt".
16. Cambiare la directory corrente in /tmp.
17. Visualizzare la directory corrente.
18. Uscire dalla shell.
19. Definire una variabile con nome "nome", assegnarle il tuo nome e stamparla.
20. Definire una variabile con nome "cognome", assegnarle il tuo cognome e stamparla.
21. Concatenare le variabili "nome" e "cognome" in un'unica stringa.
22. Creare una variabile numero con il valore 42, incrementarla di 10 e stamparla.
23. Creare una variabile lista contenente tutti i file nella directory corrente e stamparla
24. Stampare il nome del file più recentemente modificato nella directory corrente dopo averlo assegnato ad una variabile.
25. Creare una variabile comando contenente il comando date e eseguirlo per ottenere la data corrente.
26. Calcola la somma dei numeri da 1 a 5 utilizzando l'espansione aritmetica.
27. Visualizzare l'elenco dei file nella directory corrente che iniziano per la lettera "a".
28. Visualizzare l'elenco dei file nella directory /etc che contengono la parola "config".
29. Ordinare i file nella directory corrente per dimensione in ordine decrescente.
30. Visualizzare le prime 10 righe del file /etc/passwd ordinati per nome utente (*sort*).
31. Trovare tutte le directory all'interno di /etc che non sono accessibili e mostra solo i messaggi di errore.
32. Creare un file di 10 KB con caratteri casuali usando /dev/urandom
33. Eseguire il comando ls solo se il comando true ha successo.
34. Contare il numero di utenti unici nel file /etc/passwd
35. Eseguire un comando che stampi il risultato dell'operazione aritmetica 3 * (2 + 5).
36. Contare il numero di directory nella directory corrente.
37. Mostrare il valore della variabile PWD all'interno di una stringa.
38. Invocare i comandi *true* e *false* e visualizzarne il valore di uscita
39. Mostrare il testo "Directory non trovata" se il comando *ls* fallisce su una directory non esistente
40. Se la copia del file "file1.txt" in "file2.txt" fallisce, mostrare un messaggio di errore.
41. Utilizzare *cat* e la ridirezione in input per visualizzare il contenuto di /etc/passwd
42. Utilizzare *echo* e la ridirezione della shell per creare un file test contenente la linea "GNU is Not Unix" 
43. Combinare il comando *ps aux* con il comando *grep* usando un file temporaneo per individuare i processi che eseguono una shell (e.g., bash, mosh, dash, sh)
44. Combinare il comando *ps aux* con il comando *grep* usando una pipe per individuare i processi che eseguono una shell (e.g., bash, mosh, dash, sh)
45. Cosa e' cambiato? Il sistema operativo ha creato un file temporaneo oppure no?
46. Utilizzare i comandi *ps*, *grep* e *wc* per contare i processi che eseguono con i diritti del nostro utente e salvare risultato all'interno di un file di log
47. Creare la variabile d'ambiente LOGFILE ed assegnarle il valore "service.log"
48. Visualizzare il contenuto della variabile LOGFILE
49. Verificare che LOGFILE sia una variabile d'ambiente
50. Elencare tutti i file nella directory corrente che hanno nomi composti solo da caratteri numerici.

## Soluzioni
01. Creare una directory con nome "esercizi" e spostarsi al suo interno (*mkdir* e *cd*).
> mkdir esercizi; cd esercizi

02. Copiare il file /etc/passwd nella directory corrente (*cp*).
> cp /etc/passwd ./

03. Visualizzare le prime 10 righe del file /etc/passwd (*head*).
> head -n 10 /etc/passwd

04. Visualizzare le ultime 5 righe del file /etc/passwd (*tail*).
> tail -n 5 /etc/passwd

05. Contare il numero di utenti nel sistema (*wc*).
> wc -l /etc/passwd

06. Visualizzare l'elenco degli utenti con shell bash.
> cat /etc/passwd | cut -d ":" -f 7 | grep -E "^/bin/bash$"

07. Creare un alias per il comando "ls -l".
> alias ll='ls -l'

08. Visualizzare l'elenco dei file nella directory corrente ordinati per dimensione.
> ls -lS

09. Visualizzare l'elenco dei file nella directory corrente ordinati per data di modifica.
> ls -lt

10. Creare un file con nome "esempio.txt" e scrivere al suo interno una riga di testo.
> echo "Questa è una riga di testo" > esempio.txt

11. Appendere una seconda riga di testo al file "esempio.txt".
> echo "Questa è la seconda riga di testo" >> esempio.txt

12. Visualizzare il contenuto del file "esempio.txt".
> cat esempio.txt

13. Visualizzare l'elenco dei file nella directory corrente con estensione .txt. (*ls*)
> ls \*.txt

14. Visualizzare l'elenco dei file nella directory /etc con dimensione superiore a 100 KB. (*find*)
> find /etc -size +100k

15. Eliminare il file "esempio.txt".
> rm esempio.txt

16. Cambiare la directory corrente in /tmp.
> cd /tmp

17. Visualizzare la directory corrente.
> pwd

18. Uscire dalla shell.
> exit

19. Definire una variabile con nome "nome", assegnarle il tuo nome e stamparla.
> nome="Vittorio"; echo $nome

20. Definire una variabile con nome "cognome", assegnarle il tuo cognome e stamparla.
> cognome="Cuculo"; echo $conome

21. Concatenare le variabili "nome" e "cognome" in un'unica stringa.
> echo "$nome $cognome"

22. Creare una variabile numero con il valore 42, incrementarla di 10 e stamparla.
> numero=42; ((numero+=10)); echo $numero

23. Creare una variabile lista contenente tutti i file nella directory corrente e stamparla
> lista=$(ls); echo $lista

24. Stampare il nome del file più recentemente modificato nella directory corrente dopo averlo assegnato ad una variabile.
> file=$(ls -t | head -n 1); echo $file

25. Creare una variabile comando contenente il comando date e eseguirlo per ottenere la data corrente.
> comando="date"; $comando

26. Calcola la somma dei numeri da 1 a 5 utilizzando l'espansione aritmetica.
> echo $((1 + 2 + 3 + 4 + 5))

27. Visualizzare l'elenco dei file nella directory corrente che iniziano per la lettera "a".
> ls a*

28. Visualizzare l'elenco dei file nella directory /etc che contengono la parola "config".
> grep -r config /etc

29. Ordinare i file nella directory corrente per dimensione in ordine decrescente.
> ls -lSr

30. Visualizzare le prime 10 righe del file /etc/passwd ordinati per nome utente (*sort*).
> sort /etc/passwd | head -n 10

31. Trova tutte le directory all'interno di /etc che non sono accessibili e mostra solo i messaggi di errore.
> find /etc -type d 2>/dev/null

32. Crea un file di 10 KB con caratteri casuali usando /dev/urandom
> dd if=/dev/urandom bs=1K count=10 of=fout

33. Esegui il comando ls solo se il comando true ha successo.
> if true; then ls; fi

34. Conta il numero di utenti unici nel file /etc/passwd
> sort /etc/passwd | uniq -u | wc -l

35. Esegui un comando che stampi il risultato dell'operazione aritmetica 3 * (2 + 5).
> echo $((3 * (2 + 5)))

36. Contare il numero di directory nella directory corrente.
> ls -l | grep ^d | wc -l

37. Mostrare il valore della variabile PWD all'interno di una stringa.
> echo "La directory corrente è $(pwd)"

38. Invocare i comandi *true* e *false* e visualizzarne il valore di uscita
> true; echo $?; false; echo $?

39. Mostra il testo "Directory non trovata" se il comando *ls* fallisce su una directory non esistente
> ls directory_inesistente || echo 'Directory non trovata'

40. Se la copia del file "file1.txt" in "file2.txt" fallisce, mostra un messaggio di errore.
> cp file1.txt file2.txt || echo 'Errore durante la copia dei file'

41. Utilizzare *cat* e la ridirezione in input per visualizzare il contenuto di /etc/passwd
> cat < /etc/passwd

42. Utilizzare *echo* e la ridirezione della shell per creare un file test contenente la linea "GNU is Not Unix" 
> echo "GNU is Not Unix" > test

43. Combinare il comando *ps aux* con il comando *grep* usando un file temporaneo per individuare i processi che eseguono una shell (e.g., bash, mosh, dash, sh)
> ps aux > tmpfile; grep bash tmpfile

44. Combinare il comando *ps aux* con il comando *grep* usando una pipe per individuare i processi che eseguono una shell (e.g., bash, mosh, dash, sh)
> ps aux | grep bash

45. Cosa e' cambiato? Il sistema operativo ha creato un file temporaneo oppure no?
> No

46. Utilizzare i comandi *ps*, *grep* e *wc* per contare i processi che eseguono con i diritti del nostro utente e salvare risultato all'interno di un file di log
> ps -u $(whoami) | grep -v "grep" | wc -l > processo_count.log

47. Creare la variabile d'ambiente LOGFILE ed assegnarle il valore "service.log"
> export LOGFILE="service.log"

48. Visualizzare il contenuto della variabile LOGFILE
> echo $LOGFILE

49. Verificare che LOGFILE sia una variabile d'ambiente
> env | grep LOGFILE

50. Elenca tutti i file nella directory corrente che hanno nomi composti solo da caratteri numerici.
> echo [0-9]*