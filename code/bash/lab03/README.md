# Operating System Course - DIEF UNIMORE #
Esercizi avanzati (ricerche ricorsive) risolti mediante l'utilizzo di due script. Il primo per controllare i parametri, il secondo per effetuare la ricerca ricorsiva. Variabile d'ambiente PATH.

Note: per utilizzare questa guida con vim utilizzare i seguenti due comandi 
```
:set wrap 
:set linebreak
:set number
```

## Riferimenti ##
http://tldp.org/HOWTO/Bash-Prog-Intro-HOWTO.html

## Esercizi ##
01. (es31.sh) La parte in Shell prevede un parametro che deve essere il nome assoluto di un direttorio che identifica una gerarchia (G) all'interno del file system. Il programma deve determinare il livello corrente di profondita' raggiunto in ogni invocazione ricorsiva e riportare sullo standard output il massimo livello della gerarchia compresa la radice della gerarchia G. Per conservare, il massivo livello di profondita' raggiunto utilizzare un file temporaneo.

02. (es32.sh) La parte in Shell deve prevedere due parametri: il primo parametro deve essere il nome assoluto di un direttorio che identifica una gerarchia (G) all'interno del file system e il secondo parametro deve essere una stringa (F). Il programma deve cercare nella gerarchia G specificata tutti i direttori (compresa la radice) che contengono, fra gli altri, 2 file i cui nomi sono uguali a F.1 e F.2 e la cui lunghezza in linee e in caratteri deve essere la stessa: si riporti il nome assoluto di tali direttori sullo standard output. 

03. (es33.sh) La parte in Shell deve prevedere tre parametri: il primo deve essere il nome assoluto di un direttorio che identifica una gerarchia (G) all'interno del file system, mentre il secondo parametro e il terzo parametro devono essere considerati singoli caratteri numerici Cx e Cy. Il programma deve cercare nella gerarchia G specificata (compresa la radice) tutti i direttori che contengono almeno un file che contiene sia nel nome che nel contenuto entrambi i caratteri Cx e Cy. Si riporti il nome assoluto di tali direttori sullo standard output. 

04. (es34.sh) La parte in Shell deve prevedere un numero variabile N + 1 di parametri: il primo deve essere il nome assoluto di un direttorio che identifica una gerarchia (G) all'interno del file system; mentre gli altri N parametri devono essere considerati singoli caratteri C1, C2, . . . CN. Il programma deve cercare nella gerarchia G specificata tutti i file che siano di dimensione pari e che contengono (nel contenuto) tutti i caratteri Ci. Si riporti il nome assoluto di tali file sullo standard output. 

05. (es35.sh) La parte in Shell deve prevedere due parametri: il primo parametro deve essere il nome assoluto di un direttorio che identifica una gerarchia (G) all'interno del file system, mentre il secondo parametro deve essere considerato un numero intero strettamente positivo (K). Il programma deve cercare nella gerarchia G specificata tutti i direttori (compresa la radice) che contengono un numero di file (solo file e non direttori) compreso fra 1 e K (estremi inclusi). Si riporti su standard output il nome assoluto del direttorio trovato e dell'ultimo file (Fi) trovato al suo interno. 

06. (es36.sh) La parte in Shell deve prevedere due parametri: il primo deve essere il nome assoluto di un direttorio che identifica una gerarchia (G) all'interno del file system, mentre il secondo parametro deve essere considerato un numero intero strettamente positivo (K). Il programma deve cercare nella gerarchia G specificata tutti i direttori che contengono file che abbiano numero di linee uguale a K. Si riporti il nome assoluto di tali direttori sullo standard output. In ognuno di tali direttori trovati, per ogni file Fi trovato (F1, F2, . . . FN) che soddisfa la condizione precedente si deve produrre un ordinamento delle linee secondo il normale ordine alfabetico ridirigendo il risultato su un file di nome Fi.sort. 





