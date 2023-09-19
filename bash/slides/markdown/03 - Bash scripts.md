---
date: Marzo 2024
author: Dr. Nicola Bicocchi
institute: DIEF/UNIMORE
title: Introduzione a UNIX ed allo scripting Bash
subtitle: Corso di Programmazione di Sistema
section-titles: true
theme: Madrid
colortheme: crane
fontsize: 10pt
aspectratio: 1610
lang: it
---

# Scrittura ed esecuzione
Bash è un linguaggio interpretato (non compilato)! La prima linea di ogni script specifica l'interprete da utilizzare per i comandi successivi (**#!/bin/bash**). Tutte le altre linee che iniziano con **#** sono commenti nel codice.Per ottenere uno script funzionante è necessario seguire i seguenti passaggi:

## Scrittura di uno script
```shell
$ vim script.sh

#!/bin/bash  
echo Total number of inputs: $#  
echo First input: "$1"  
echo Second input: "$2"  
exit 0
```

## Rendere lo script eseguibile
```shell
$ chmod a+x script.sh # oppure  
$ chmod 755 script.sh
```

## Invocazione di uno script
```shell
$ ./script.sh AAPL GOOGL MSFT  
Total number of inputs: 3  
First input: AAPL  
Second input: GOOGL
```

Perchè abbiamo invocato lo script con **./script.sh** piuttosto che **script.sh**? Se specifichiamo un percorso che rappresenta **un nome semplice di file**, Bash cerca un programma eseguibile nell'elenco di directory rappresentato dalla variabile **PATH**.

Se PATH non contiene la directory **.** (che indica la directory corrente), i programmi non vengono trovati anche se si trovano nella directory corrente. Per introdurre **.** all'interno di **PATH**:

```shell
# Modifica alla variabile PATH (sconsigliato)  
$ export PATH=$PATH:. 
$ script.sh
```

## Variabili speciali
All'interno di uno script Bash è possibile accedere ad un gruppo di variabili speciali che rendono possibile lo sviluppo

* **$0** Il nome dello script in esecuzione  
* **$1, $2,...., $n** n-esimo parametro passato da linea di comando  
* **$*** tutti i parametri passati a linea di comando
* **$#** numero di parametri da linea di comando  
* **$$** PID della shell che esegue lo script
* **$?** valore di ritorno dell'ultimo comando eseguito  

**shift** elimina il primo parametro dalla lista $1...$n, tutti gli altri scorrono indietro di una posizione. Può essere invocato senza parametri oppure specificando il numero di shift da eseguire.

```shell 
$ vim test.sh

#!/bin/bash
echo [$#] $*  # mostra [numero dei parametri] tutti i parametri
shift         # elimina il primo parametro
echo [$#] $*  # mostra [numero dei parametri] tutti i parametri
shift 3       # elimina i primi tre parametri
echo [$#] $*  # mostra [numero dei parametri] tutti i parametri

```

```shell
./test.sh -a -b -c -d -e -f -g -h
[8] -a -b -c -d -e -f -g -h
[7] -b -c -d -e -f -g -h
[4] -e -f -g -h
```

# Costrutti condizionali

## test
**test** è un comando per eseguire verifiche di varia natura sulle stringhe (interpretandole in base ai casi come stringhe, numeri o file). Un controllo avvenuto con successo ritorna 0, altrimenti 1.

```shell
$ test 5 -gt 3; echo $?               # 0  
$ test 5 -gt 3; echo $?               # 1  
$ test "nicola" == "nicola"; echo $?  # 0  
$ test "nicola" == "mario"; echo $?   # 1  
$ test -f /etc/passwd; echo $?        # 0  
$ test -d /etc/passwd; echo $?        # 1
```

## test (strings)
```
-n STRING           the length of STRING is nonzero
-z STRING           the length of STRING is zero
STRING1 = STRING2   the strings are equal
STRING1 != STRING2  the strings are not equal
```

## test (numbers)
```
INTEGER1 -eq INTEGER2   INTEGER1 is equal to INTEGER2
INTEGER1 -ge INTEGER2   INTEGER1 is greater than or equal to INTEGER2
INTEGER1 -gt INTEGER2   INTEGER1 is greater than INTEGER2
INTEGER1 -le INTEGER2   INTEGER1 is less than or equal to INTEGER2
INTEGER1 -lt INTEGER2   INTEGER1 is less than INTEGER2
INTEGER1 -ne INTEGER2   INTEGER1 is not equal to INTEGER2
```

## test (files)
```
-d FILE   FILE exists and is a directory
-e FILE   FILE exists
-f FILE   FILE exists and is a regular file
-h FILE   FILE exists and is a symbolic link (same as -L)
-O FILE   FILE exists and is owned by the effective user ID
-r FILE   FILE exists and the user has read access
-s FILE   FILE exists and has a size greater than zero
-w FILE   FILE exists and the user has write access
-x FILE   FILE exists and the user has execute (or search) access
```

## test (logic)
```
! EXPRESSION                  EXPRESSION is false
EXPRESSION1 -a EXPRESSION2    both EXPRESSION1 and EXPRESSION2 are true
EXPRESSION1 -o EXPRESSION2    either EXPRESSION1 or EXPRESSION2 is true
```

Ad esempio:

verifica che /etc/passwd sia un file e leggibile  

```shell
$ test -f /etc/passwd -a -r /etc/passwd; echo $?
0
```

verifica che /etc/passwd sia un file oppure una directory  

```shell
$ test -f /etc/passwd -o -d /etc/passwd; echo $?
0
```

verifica che /etc/passwd non sia una directory e non sia scrivibile  

```shell
$ test ! -d /etc/passwd -o ! -w /etc/passwd; echo $?
0
```

## [ ]
Il comando test ha un alter ego che si comporta nello stesso modo ma ha nome diverso ([). Il comando è stato introdotto principalmente per aumentare la leggibilità degli script in particolare per l'utilizzo congiunto con la direttiva **if**.

Gli spazi che vedete nell'esempio sotto, dopo [ e prima di ] sono obbligatori! La loro assenza produce errori!

```shell
$ which test  
/usr/bin/test  
$ which [  
/usr/bin/[  
```

```shell
$ [ -r /etc/passwd ]; echo $?  
0
```

## if
Il costrutto if non consente solo di verificare una condizione ma anche di eseguire istruzioni in caso la condizione risulti vera o falsa.

```shell
if test condizione; then
  comando
else
  comando
fi
```

Più sinteticamente, utilizzando [ ]:

```shell 
if [ condizione ]; then
  comando
else
  comando
fi
```

Utilizzando invece la sua forma più generale:

```shell
if [ condizione ]; then
  comando
elif [ condizione ]; then
  comando
else
  comando
fi
```

Ad esempio:

```shell
if [ -f /etc/passwd -a -r /etc/passwd ]; then
  echo “/etc/passwd è un file leggibile!”
fi
```

```shell
if [ $# -ne 3 ]; then
  echo “params != 3”
else
  echo “params == 3”
fi
```

```shell
if [ $# -lt 2 ]; then
  echo "params < 2"
elif [ $# -lt 4 ]; then
  echo "2 <= params < 4"
else
  echo "params >= 4"
fi
```

## &&, ||
In caso una condizione determini l'esecuzione di poche istruzioni è possibile utilizzare una forma sintetica (&&,||). 

```shell
$ [ 1 –eq 0 ] && echo “pass”           # 
$ [ 1 –eq 1 ] && echo “pass”           # pass
$ [ 1 –eq 0 ] || echo “fail”           # fail
$ [ 1 –eq 1 ] || echo “fail”           #
$ [ 1 –eq 1 ] && (echo “pass”; pwd)    # pass /home/nicola
```

Gli operatori && e || possono anche sostituire gli operatori -a e -o per combinare logicamente condizioni di test trattandole come comandi separati

```shell
# /etc/passwd è un file E è scrivibile
$ test -f /etc/passwd && test -w /etc/passwd; echo $?
1

# /etc/passwd è un file O è scrivibile
$ test -f /etc/passwd || test -w /etc/passwd; echo $?
0

# /etc/passwd è un file E è scrivibile
$ [ -f /etc/passwd ] && [ -w /etc/passwd ]; echo $?
1

# /etc/passwd è un file O è scrivibile
$ [ -f /etc/passwd ] || [ -w /etc/passwd ]; echo $?
0
```

## Pattern matching
Il patter matching consiste nel confrontare un valore con un determinato pattern
frequentemente specificato utilizzando wildcards.

```
Stringa     Pattern     Match?
------------------------------
ABCDEF      A*          Si

ABCDEF      AB??EF      Si

ABCDEF      ABCNN*      No
```

Il costrutto test / [ ] non supporta pattern matching!

## [[ ]]
Il costrutto [[ ]] che si comporta come [ ] aggiungendo (fra altre) la funzione di pattern matching

```shell
# [ ] fallisce
if [ “$1” == n?co* ]; then
  echo “success”
fi

if [ “$1” != [0-9]* ]; then
  echo “success”
fi
```

```shell
# [[ ]] pattern matching
if [[ “$1” == n?co* ]]; then
  echo “success”
fi

if [[ “$1” != [0-9]* ]]; then
  echo “success”
fi
```

## case
Il costrutto switch-case che abbina il pattern matching alla possibilità di eseguire più confronti in modo sintetico (evitando else if)

```shell
case espressione in
  PATTERN_1)
    comando/i
    ;;

  PATTERN_2)
    comando/i
    ;;

  PATTERN_N)
    comando/i
    ;;
  *)
    comando/i
    ;;
esac
```

```shell
#!/bin/bash
if [ $# -ne 1 ]; then
  echo "usage: $0 arg"
  exit 1
fi

case "$1" in
  /*) echo "Percorso assoluto"
      ;;
  */*) echo "Percorso relativo"
       ;;
  *) echo ”Nome semplice"
     ;;
esac

exit 0
```

---

# Costrutti iterativi

## for
```shell
for argomento in lista; do  
   comando/i  
   ...  
done
```

```shell
# Esempio: tabellina del 5  
for i in 1 2 3 4 5; do  
  echo "5 * %i = $(expr 5 \* $i)"  
done
```

```shell
# Esempio: mostra i nomi file in home directory 
for fname in "$HOME"/*; do  
   echo "$fname"  
done 
```

Per iterare su indici, è possibile generare una lista di indici validi da utilizzare con **for** utilizzando il comando **seq**.

```
$ seq 1 5
1  
2  
3  
4  
5
```

```shell
# Esempio: tabellina del 5  
for i in $(seq 1 5); do
  echo "5 * $i = $(expr 5 \* $i)"
done

5 * 1 = 5
5 * 2 = 10
5 * 3 = 15
5 * 4 = 20
5 * 5 = 25
```

## while

```shell
while [ condizione ]; do
  comando/i
done
```

```shell
# Esempio: contatore da 10 a 1  
i=10 
while [ "$i" -gt 0 ]; do
  echo $i
  i=$(expr $i - 1)
done
```

## Espansione nomi di file
I moderni filesystems supportano nomi di file contenenti spazi. Di conseguenza, per evitare problemi, l'espansione di variabili fuori dal controllo dello sviluppatore (ad es. nomi di file) va effettuata fra doppie virgolette " ".  

```shell
 $ vim script.sh  

 #!/bin/bash  
 for fname in "$HOME"/*; do
   if [ -f "$fname" ]; then
     echo F "$fname"
   elif [ -d "$fname" ]; then
     echo D "$fname"
   fi
 done
```

Se non usassimo le doppie virgolette, il seguente caso produrrebbe l'errore mostrato.

```shell
$ touch "$HOME"/"Mario Rossi"
$ ./script.sh
./script.sh: line 4: [: /home/nicola/Mario: binary operator expected
```

# Argomenti avanzati

## Funzioni

Bash supporta la definizione di funzioni:
* Accedono a parametri di invocazione con sintassi \$1 . . . \$n (come gli script)
* Ritornano al chiamante con istruzione return (script usano exit)
* Valori di ritorno possono essere letti dal chiamante con sintassi $? (come gli script)
* Definite con sintassi:

```
nomefunzione() {
  .
  .
  .
}
```

L'esempio seguente definisce una funzione che ritorna 0 in caso il primo parametro sia una directory eseguibile, 1 viceversa.

```shell
#!/bin/bash  

process() {  
  echo -n "$1"
  [ -d "$1" -a -x "$1" ] && return 0  
  return 1  
}
 
for f in $*: do  
  process "$f"  
  if [ $? -eq 0 ]; then  
    echo " [pass]"  
  else  
    echo " [fail]"  
  fi  
done
 
exit 0
```


## Script multi-file 
```shell
$ vim lib.sh

#!/bin/bash 
process() {  
  echo -n "$1"  
  [ -d "$1" -a -x "$1 ] && return 0
  return 1
 }
```

``` shell 
$ vim script.sh  

 #!/bin/bash
 
 source lib.sh  
 # oppure  
 # . lib.sh
 
for f in $*; do  
  process "$f"  
  if [ $? -eq 0 ]; then  
    echo " [pass]"  
  else  
    echo " [fail]"
  fi
done
 
 exit 0
```

## Arrays
```shell
# array definito vuoto
$ arr=()

# array definito con valori all’intero
$ arr=(1 2 3)

# aggiunge valori ad array esistente
$ arr+=(4 5)

# sovrascrive valore di indice 0
$ arr[0]=3

# mostra i valori nell’array
$ echo ${arr[@]}

# mostra gli indici validi dell’array
$ echo ${!arr[@]}

# mostra il numero di valori nell’array
$ echo ${#arr[@]}

# mostra n elementi partendo da indice s
$ echo ${arr[@]:s:n}
```

Ad esempio:

```shell
#!/bin/bash

files=(/var/log/kern.log /var/log/auth.log /var/log/syslog)  
keyw=(nicola marzia)

echo "* searching ${#files[@]} files with ${#keyw[@]} keywords"
echo "* press enter to continue..."
read

for f in ${files[@]}; do
  for k in ${keyw[@]}; do
    l=$(cat ${f} | grep ${k} | wc -l)
    echo "* ${f}: found ${l} occurrences of ${k}!"
  done
done
```

## getopts
Funzione standard (**builtin**) per gestire parametri a linea di comando. Esiste in Java, C, Python, etc.
* getopts va sempre utilizzata abbinata ad un while e un case
* La stringa "m:dh" rappresenta i parametri da controllare. Le lettere singole (e.g., d e h) rappresentano parametri senza argomenti. Le lettere seguite da **:** (e.g., m) rappresentano parametri con argomenti
* getopts scansiona la linea di comando e ad ogni ciclo aggiorna la variabile **o** affinchè sia analizzata dal blocco case
* Il blocco case, tipicamente, assegna a delle variabili il valore degli argomenti (**OPTARG**)

```shell
while getopts "m:dh" o; do  
  case "$o" in  
     m) MESSAGE="$OPTARG"  
       ;;  
     d) DEBUG=TRUE  
       ;;
     h) usage  
       ;;  
     *) usage  
       ;;  
  esac  
done
shift $(expr $OPTIND - 1)
```

Ad esempio:

```shell
#!/bin/bash                                                      

# Default values                                                 
MESSAGE="Hello World!"                                           
DEBUG=FALSE                                                      
                                           
# Usage function                                                 
usage() {                                                        
    echo "Usage: $0 [-h] [-m <string>] [-d] filename" 1>&2       
    exit 1
}                                                                

# In case of optional [] parameters default values are overriden
while getopts "m:dh" o; do
    case "$0" in
          m) MESSAGE="$OPTARG"
             ;;
          d) DEBUG=TRUE
             ;;
          h) usage
             ;;
          *) usage
             ;;
    esac
done
# Shift parameters away. $1 becomes filename
shift $(expr $OPTIND - 1) 

# Additional checks
# Check if filename exists
[ -e "$1" ] || usage

echo m = "$MESSAGE"
echo d = "$DEBUG"
echo filename = "$1"
exit 0
```

## Buone pratiche
* Trattandosi di un linguaggio antico, l'indentazione è ancora facoltativa (in Python, recente, è obbligatoria!). Indentazione è comunque di fondamentale importanza!
* Variabili globali sono MAIUSCOLE (ad es. USAGE="$0 usage: ...")  
* Il controllo dei parametri avviene in **via negativa**. Si controllano le condizioni di fallimento e, se verificate, si termina lo script ritornando un codice errore (exit 1). Questa pratica evita indentazione eccessiva  
* I valori di uscita (exit) utilizzano valori diversi per distinguere successo (exit 0) da fallimento (exit 1).Per differenziare fra diversi tipi di fallimento si possono utilizzare numeri positivi > 1 (ad es. exit 2)  
* I filesystem moderni supportano la presenza di spazi. Per questo motivo, tutte le variabili fuori dal controllo del programmatore (ad es. nomi di file) vanno espanse fra doppie virgolette (ad es. echo "$filename") 
* E'  buona norma (best practice) aderire ad un canovaccio noto e consolidato:
  * Definizione interprete  
  * Definizione variabili globali
  * Definizione funzioni  
  * Controllo parametri
  * Corpo principale
  * Terminazione 

```shell 
#!/bin/bash

# Definizione variabili globali
USAGE="usage: $0 dirname"

# Definizione funzioni
usage() {
  echo "$USAGE"
  exit 1
}

# Controllo parametri
if [ $# -ne 1 ]; then
	usage
fi
	
if [ ! -d "$1" -o ! -x "$1" ]; then
  usage
fi
  
# Corpo principale
F=0; D=0
for fname in "$1"/*; do
	if [ -f "$fname" ]; then
	  F=$(expr $F + 1)
	fi
	
  if [ -d "$fname" ]; then
	  D=$(expr $D + 1)
	fi
done
	
echo "#files=$F, #directories=$D"

# Terminazione
exit 0
```

## Bash vs Python per la scrittura di script

**Bash**  

+ Notissima, installata ovunque  
+ Integrazione profonda con Unix (piping, ridirezione)  
- Manca supporto per OOP, strutture dati, multi-threading  
- Tool di debug scarsi

 
**Python**  

+ Supporto per OOP, strutture dati, multi-threading  
+ Tool di debug  
- Gestione delle dipendenze  
- Codice più prolisso per cose semplici

L'esempio che segue mostra lo stesso programma scritto nei due linguaggi. Le somiglianze sono piuttosto evidenti.

```shell
#!/bin/bash

if [ $# -lt 1 ]; then
  echo "usage: $0 f1 .. fn"
  exit 1
fi

l=0
for fname in $*; do
   l=$(wc -l "$fname" | cut -d ' ' -f 1)
   echo "$fname": "$l"
done

exit 0
```

```python
#!/usr/bin/env python

import sys
import subprocess

if len(sys.argv) < 2:
   sys.stderr.write("usage: %s f1 .. fn\n" % (sys.argv[0]))
   sys.exit(1)
   
for fname in sys.argv[1:]:
  out  = subprocess.check_output(['wc', '-l', fname])
  print("%s: %s" % (fname, out.split(' ')[0]))
  
sys.exit(0)
```

