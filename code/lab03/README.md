# Esercitazione Bash #3
Per utilizzare questa guida con vim utilizzare i seguenti due comandi 

>:set wrap 
>
>:set linebreak
>
>:set number

## Esercizi
01. (es31.sh) Scrivere uno script che prevede 1 parametro che deve essere il nome assoluto di una directory (D). Lo script deve esplorare ricorsivamente D e stampare, per ogni sottocartella, il livello di profondità raggiunto. D avrà livello 0, le sottocartelle di D avranno livello 1, e così via. Da risolvere sia utilizzando una funzione ricorsiva, che utilizzando il comando find. Nel caso di find, l'opzione -printf può essere utile (vedi manuale).

02. (es32.sh) Scrivere uno script che prevede 4 parametri. Il primo parametro deve essere il nome assoluto di una directory (D), il secondo deve essere una stringa (F), il terzo (N1) ed il quarto (N2) vanno trattati come numeri interi positivi. Lo script cerca ricorsivamente in D tutti i file di nome F la cui lunghezza in linee è compresa fra N1 e N2. 

03. (es33.sh) Scrivere uno script che prevede 2 parametri. Il primo parametro deve essere il nome assoluto di una directory (D), mentre il secondo è un singolo carattere numerico (N). Lo script cerca ricorsivamente in D tutti i file che contengono sia nel nome che nel contenuto N.  

04. (es34.sh) Scrivere uno script che prevede 2 parametri. Il primo parametro deve essere il nome assoluto di una directory (D), mentre il secondo va trattato come un numero intero positivo (N). Lo script cerca ricorsivamente in D tutte le directory che contengono un numero di file (solo file non directory) compreso fra 1 e N. 

05. (es35.sh) Scrivere uno script che prevede 2 parametri. Il primo parametro deve essere il nome assoluto di una directory (D), mentre il secondo va trattato come un numero intero positivo (N). Lo script cerca ricorsivamente in D tutte le directory che contengono almeno un file (solo file non directory) con dimensione in byte maggiore di N. Ordinare (in modo decrescente) le directory trovate in base numero di file (che contengono) che rispettano il criterio specificato sopra.

06. (es36.sh) Scrivere uno script che prevede 2 parametri. Il primo parametro deve essere il nome assoluto di una directory (D), mentre il secondo va trattato come un nome semplice di file (F). Lo script cerca ricorsivamente in D tutti i file di nome F, ne stampa il percorso completo su stardard output, e mostra anche le prima e le ultime due linee del suo contenuto.

07. (es37.sh) Scrivere uno script che prevede 2 parametri. Il primo parametro deve essere il nome assoluto di una directory (D), mentre il secondo va trattato come un nome semplice di file (F). Lo script cerca ricorsivamente in D tutti i file di nome F, e crea un link simbolico ad ognuno di essi all'interno della cartella /tmp. I link simbolici creati devono avere un nome nella forma /tmp/link_1 .. /tmp/link_n.

08. (es38.sh) Scrivere uno script che prevede 3 parametri. Il primo parametro deve essere il nome assoluto di una directory (D), mentre il secondo ed il terzo vanno trattati come nomi semplici di file (F1), (F2). Lo script cerca ricorsivamente in D tutte le directory che contengono entrambi i file F1 ed F2, ne stampa il percorso completo, e mostra anche la somma della dimensione in byte di F1 ed F2.

09. (es39.sh) Scrivere uno script che prevede 2 parametri. Il primo parametro deve essere il nome assoluto di una directory (D), mentre il secondo ed il terzo vanno trattati come nomi semplici di file (F1), (F2). Lo script cerca ricorsivamente in D per verificare che esistano (anche in directory diverse) almeno 1 file di nome F1 ed almeno 1 file di nome F2. Stampare il numero di occorrenze di F1 ed F2.
