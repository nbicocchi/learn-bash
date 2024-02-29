# Esercitazione Bash #1 
Per utilizzare questa guida con vim utilizzare i seguenti due comandi 

>:set wrap 
>
>:set linebreak
>
>:set number

## Esercizi 
01. Posizionarsi all'interno della propria home directory (*cd*)
02. Elencare i file nella directory corrente (*ls*)
03. Elencare i file nella directory corrente visualizzandone i permessi associati ed includendo anche i file nascosti (i.e., file che iniziano con il carattere .) (*ls*)
04. Visualizzare il percorso assoluto della directory corrente (*pwd*)
05. Spostarsi alla radice del filesystem (*cd*)
06. Spostarsi nella propria home directory utilizzando percorso assoluto (*cd*)
07. Spostarsi nella radice del filesystem utilizzando un percorso relativo (*cd*)
08. Ritornare alla propria home utilizzando il comando cd senza argomenti (*cd*)
09. Copiare il file /etc/passwd nella directory corrente (*cp*)
10. Copiare il file /etc/passwd nella directory corrente attribuendo al nuovo file il nome passwd.alt (*cp*)
11. Rinominare il file passwd.alt in passwd.alt.bak e verificare che passwd e passwd.alt.bak siano identici (*mv, diff*)
12. Verificare che il file passwd contenga la stringa root (*grep*)
13. Contare il numero di caratteri di cui è composto il file passwd (*wc*)
14. Contare il numero di linee di cui è composto il file passwd (*wc*)
15. Cancellare i file passwd e passwd.alt.bak con un'unica istruzione (*rm*)
16. Creare un file vuoto di nome test (*touch*)
17. Utilizzando un editor di testo, scrivere all'interno del file test la stringa 'Hello World!' (*nano/micro/vim*)
18. Visualizzare il contenuto del file test (*cat*)
19. Rendere il file test leggibile da tutti gli utenti (*chmod*)
20. Rendere il file test leggibile e scrivibile dal solo proprietario (*chmod*)
21. Costruire un link hard da test a test2 (*ln*)
22. Costruire un link soft (simbolico) da test a test3 (*ln*)
23. Rendere il link test3 *stale* (*rm*)
24. Creare una directory di nome testdir nella propria home directory (*mkdir*)
25. Verificare che testdir sia vuota (*ls*)
26. Creare un file vuoto di nome empty all'interno di testdir senza cambiare directory (*touch*)
27. Eliminare la directory testdir (*rm/rmdir*)
28. Visualizzare PID della shell correntemente in esecuzione (*ps*)
29. Visualizzare il nome del processo con PID = 1 (*ps*)
30. Visualizzare il nome del proprio utente (*whoami*)
31. Visualizzare il nome dei gruppi a cui appartiene il proprio utente (*id*)
32. Utilizzando un editor di testo, creare un file test.sh contenente le seguenti linee:

```
#!/bin/bash
echo "Hello World!"
exit 0
```

34. Rendere eseguibile test.sh (*chmod*)
35. Eseguire test.sh
36. Spostare test.sh all'interno della cartella /tmp (*mv*)
37. Eseguire test.sh rimanendo nella propria home directory
38. Mostrare il numero di inode del file test.sh (*stat*)
39. Acquisire i diritti di amministrazione (*sudo*)
40. Creare l'utente giuda (*adduser*)
41. Cambiare la password dell'utente giuda (*passwd*)
42. Eliminare l'utente giuda (*deluser*)
43. Abbandonare i diritti di amministrazione (*exit*)
44. Cambiare la password del proprio utente (*passwd*)
45. Visualizzare il percorso completo del comando ls (*which*)
46. Visualizzare il contenuto html della pagina https://www.gnome.org (*curl*)
47. Visualizzare la data corrente nel formato gg-mm-aaaa (*date*)
48. Utilizzare il comando expr per sommare e moltiplicare 3 e 7 (*expr*)
49. Utilizzare il comando expr per sottrarre e dividere 9 e 3 (*expr*)
50. Avviare il comando mc su un terminale e chiuderlo utilizzando un secondo terminale (*kill/killall*)

## Soluzioni 
1. Posizionarsi all'interno della propria home directory (*cd*)
> cd

2. Elencare i file nella directory corrente (*ls*)
> ls

3. Elencare i file nella directory corrente visualizzandone i permessi associati ed includendo anche i file nascosti (i.e., file che iniziano con il carattere .) (*ls*)
> ls -al

4. Visualizzare il percorso assoluto della directory corrente (*pwd*)
> pwd

5. Spostarsi alla radice del filesystem (*cd*)
> cd /

6. Spostarsi nella propria home directory utilizzando percorso assoluto (*cd*)
> cd /home/nome_utente

7. Spostarsi nella radice del filesystem utilizzando un percorso relativo (*cd*)
> cd ../..

8. Ritornare alla propria home (*cd*)
> cd

9. Copiare il file /etc/passwd nella directory corrente (*cp*)
> cp /etc/passwd .

10. Copiare il file /etc/passwd nella directory corrente attribuendo al nuovo file il nome passwd.alt (*cp*)
> cp /etc/passwd passwd.alt

11. Rinominare il file passwd.alt in passwd.alt.bak e verificare che passwd e passwd.alt.bak siano identici (*mv, diff*)
> mv passwd.alt passwd.alt.bak

> diff passwd passwd.alt.bak

12. Verificare che il file passwd contenga la stringa root (*grep*)
> grep root /etc/passwd

13. Contare il numero di caratteri di cui è composto il file passwd (*wc*)
> wc -c passwd

14. Contare il numero di linee di cui è composto il file passwd (*wc*)
> wc -l passwd

15. Cancellare i file passwd e passwd.alt.bak con un'unica istruzione (*rm*)
> rm passwd*

16. Creare un file vuoto di nome test (*touch*)
> touch test

17. Utilizzando un editor di testo, scrivere all'interno del file test la stringa 'Hello World!' (*nano/micro/vim*)
> nano test

18. Visualizzare il contenuto del file test (*cat*)
> cat test

19. Rendere il file test leggibile da tutti gli utenti (*chmod*)
> chmod 444 test

20. Rendere il file test leggibile e scrivibile dal solo proprietario (*chmod*)
> chmod 600 test

21. Costruire un link hard da test a test2 (*ln*)
> ln test test2

22. Costruire un link soft (simbolico) da test a test3 (*ln*)
> ln -s test test3

23. Rendere il link test3 *stale* (*rm*)
> rm test

24. Creare una directory di nome testdir nella propria home directory (*mkdir*)
> mkdir testdir

25. Verificare che testdir sia vuota (*ls*)
> ls -al testdir

26. Creare un file vuoto di nome empty all'interno di testdir senza cambiare directory (*touch*)
> touch testdir/empty

27. Eliminare la directory testdir (*rm/rmdir*)
> rm -rf testdir

28. Visualizzare PID della shell correntemente in esecuzione (*ps*)
> ps

29. Visualizzare il nome del processo con PID = 1 (*ps*)
> ps fax

30. Visualizzare il nome del proprio utente (*whoami*)
> whoami

31. Visualizzare il nome dei gruppi a cui appartiene il proprio utente (*id*)
> id

32. Utilizzando un editor di testo, creare un file test.sh contenente le seguenti linee:

```
#!/bin/bash
echo "Hello World!"
exit 0
```

> nano test.sh

34. Rendere eseguibile test.sh (*chmod*)
> chmod 755 test.sh

35. Eseguire test.sh
> ./test.sh

36. Spostare test.sh all'interno della cartella /tmp (*mv*)
> mv test.sh /tmp

37. Eseguire test.sh rimanendo nella propria home directory
> /tmp/test.sh

38. Mostrare il numero di inode del file test.sh (*stat*)
> stat /tmp/test.sh

39. Acquisire i diritti di amministrazione (*sudo*)
> sudo -i

40. Creare l'utente giuda (*adduser*)
> adduser giuda

41. Cambiare la password dell'utente giuda (*passwd*)
> passwd giuda

42. Eliminare l'utente giuda (*deluser*)
> deluser giuda

43. Abbandonare i diritti di amministrazione (*exit*)
> exit

44. Cambiare la password del proprio utente (*passwd*)
> passwd

45. Visualizzare il percorso completo del comando ls (*which*)
> which ls

46. Visualizzare il contenuto html della pagina https://www.gnome.org (*curl*)
> curl https://www.gnome.org

47. Visualizzare la data corrente nel formato gg-mm-aaaa (*date*)
> date +%d-%m-%Y

48. Utilizzare il comando expr per sommare e moltiplicare 3 e 7 (*expr*)
> expr 3 + 7

> expr 3 \\* 7

49. Utilizzare il comando expr per sottrarre e dividere 9 e 3 (*expr*)
> expr 9 - 3

> expr 9 / 3

50. Avviare il comando mc su un terminale e chiuderlo utilizzando un secondo terminale (*kill/killall*)
> mc (primo terminale)

> ps fax (secondo terminale, guardare PID)

> kill -9 PID (secondo terminale)






