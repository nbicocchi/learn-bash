# Operating System Course - DIEF UNIMORE #
Guida all'installazione di Ubuntu Linux. Introduzione a vim (vimtutor). Uso della shell: console grafica e testuale. Comandi cd, pwd, ls, ln, cp, mv, rm, mkdir, rmdir, echo, cat, grep, true, false, expr; variabili d'ambiente; permessi di accesso ai file usando chmod e chown; man e la documentazione in linea.

Note: per utilizzare questa guida con vim utilizzare i seguenti due comandi 
```
:set wrap 
:set linebreak
:set number
```

## Riferimenti ##
http://tldp.org/HOWTO/Bash-Prog-Intro-HOWTO.html

## Esercizi ##
01. Elencare i file nella directory corrente

02. Elencare i file nella directory corrente visualizzando i permessi associati, comprendendo anche i file che iniziano con il punto

03. Visualizzare il nome assoluto della directory corrente

04. Spostarsi alla radice del filesystem

05. Ritornare alla propria home indicandone il nome in modo assoluto

06. Spostarsi alla radice del filesystem

07. Ritornare alla propria home utilizzando il comando cd senza argomenti

08. Copiare il file "/etc/passwd" nella directory corrente

09. Copiare il file "/etc/passwd" nella directory corrente attribuendo al nuovo file il nome "passwd.bak"

10. Cancellare i file "passwd" e "passwd.bak" dalla propria home con un'unica istruzione

11. Utilizzare echo e la ridirezione della shell per creare un file "prova" contenente la linea "GNU is Not Unix" 

12. Cosa avviene se si esegue la ridirezione con due maggiori affiancati?

13. Invocare cat per visualizzare il contenuto del file

14. Rendere il file "prova" leggibile da tutti

15. Rendere il file "prova" leggibile dal solo proprietario

16. Costruire un link hard da prova a prova2

17. Costruire un link soft (simbolico) da prova a prova3. Qual'e' la differenza fra link hard, soft, e copia di un file?

18. Creare una directory nella propria home di nome "miadir"

19. Invocare ls per visualizzare il contenuto di miadir

20. Invocare ls per visualizzare il nome e gli attributi della directory miadir

21. Eliminare la directory miadir

22. Combinare il comando "ps -efl" con il comando "grep" usando un file temporaneo per individuare i processi che eseguono una shell (e.g., bash, mosh, dash, sh)

23. Combinare il comando "ps -efl" con il comando "grep" usando una pipe per individuare i processi che eseguono una shell (e.g., bash, mosh, dash, sh)

24. Cosa e' cambiato? Il sistema operativo ha creato un file temporaneo oppure no?

25. Invocare i comandi true e false e visualizzarne l'exit value

26. Utilizzare il comando expr per sommare e moltiplicare i numeri 10 e 12

27. Creare la variabile d'ambiente NOMEFILE ed assegnarle il valore "data.csv"

28. Visualizzare il contenuto di NOMEFILE utilizzando il comando echo

29. Creare lo script test.sh contenente la sola linea #!/bin/bash. A cosa serve questa linea?

## Soluzioni ##
01. Elencare i file nella directory corrente

	```
	$ ls
	```

02. Elencare i file nella directory corrente visualizzando i permessi associati, comprendendo anche i file che iniziano con il punto
	
	```
	$ ls -al
	```

03. Visualizzare il nome assoluto della directory corrente

	```
	$ pwd
	```

04. Spostarsi alla radice del filesystem

	```
	$ cd /
	```

05. Ritornare alla propria home indicandone il nome in modo assoluto

	```
	$ cd /home/...
	```

06. Spostarsi alla radice del filesystem

	```
	$ cd /
	```

07. Ritornare alla propria home utilizzando il comando cd senza argomenti

	```
	$ cd
	```

08. Copiare il file "/etc/passwd" nella directory corrente

	```
	$ cp /etc/passwd .
	```

09. Copiare il file "/etc/passwd" nella directory corrente attribuendo al nuovo file il nome "passwd.bak"

	```
	$ cp /etc/passwd passwd.bak
	```

10. Cancellare i file "passwd" e "passwd.bak" dalla propria home con un'unica istruzione
	
	```
	$ rm passwd*
	```

11. Utilizzare echo e la ridirezione della shell per creare un file "prova" contenente la linea "GNU is Not Unix" 
	
	```
	$ echo "GNU is Not Unix" > prova
	```

12. Cosa avviene se si esegue la ridirezione con due maggiori affiancati?

	Approfondimento: I nuovi contenuti vengono aggiungi agli esistenti (scrittura in append)

13. Invocare cat per visualizzare il contenuto del file

	```
	$ cat prova
	```

14. Rendere il file "prova" leggibile da tutti

	```
	$ chmod 444 prova ($ chmod a+r prova)
	```

15. Rendere il file "prova" leggibile dal solo proprietario

	```
	$ chmod 400 
	```

16. Costruire un link hard da prova a prova2

	```
	ln prova prova2
	```

17. Costruire un link soft (simbolico) da prova a prova3. Qual'e' la differenza fra copia di un file, link hard, e link soft?
	
	```
	$ ln -s prova prova3
	```
	
	Approfondimento: la differenza sostanziale fra copia, link hard e link soft consiste nel modo 
	in cui viene utilizzato lo spazio fisico sul disco. In particolare: (a) cp duplica i dati, (b) 
	ln crea un riferimento a dati esistenti, (c) ln -s crea un piccolo file che contiene il percorso 
	di un secondo file (e.g., collegamenti di windows)

18. Creare una directory nella propria home di nome "miadir"

	```
	$ mkdir miadir
	```

19. Invocare ls per visualizzare il contenuto di miadir

	```
	$ ls miadir
	```

20. Invocare ls per visualizzare il nome e gli attributi della directory miadir

	```
	$ ls -ld miadir
	```

21. Eliminare la directory miadir

	```
	$ rmdir miadir (oppure rm -rf miadir)
	```

22. Combinare il comando "ps -efl" con il comando "grep" usando un file temporaneo per individuare i processi che eseguono una shell (e.g., bash, mosh, dash, sh)

	```
	$ ps -efl > temp; grep bash temp 
	```

23. Combinare il comando "ps -efl" con il comando "grep" usando una pipe per individuare i processi che eseguono una shell (e.g., bash, mosh, dash, sh)

	```
	ps -efl | grep bash
	```

24. Cosa e' cambiato? Il sistema operativo ha creato un file temporaneo oppure no?

	Approfondimento: La pipe e' utile proprio per consentire a processi differenti di 
	comunicare SENZA utilizzare il filesystem, ma collegando lo stdout del primo processo 

25. Invocare i comandi true e false e visualizzarne l'exit value
	
	```
	$ true; echo $?; false; echo $?
	```

26. Utilizzare il comando expr per sommare e moltiplicare i numeri 10 e 12
	
	```
	$ expr 10 + 12; expr 10 '*' 12 (in alternativa expr 10 \* 12)
	```

27. Creare la variabile d'ambiente NOMEFILE ed assegnarle il valore "data.csv"
	
	```
	$ export NOMEFILE="data.csv"
	```

28. Visualizzare il contenuto di NOMEFILE utilizzando il comando echo

	```
	$ echo $NOMEFILE
	```

29. Creare lo script test.sh contenente la sola linea #!/bin/bash. A cosa serve questa linea?

	```
	$ echo "#!/bin/sh" > script.sh
	```

	Approfondimento: La linea #!/bin/sh definisce il percorso dell'interprete dei comandi 
	da utilizzare per eseguire cio' che segue. Ad esempio, per uno script python, posso 
	usare #!/usr/bin/python

