# Bash Scripting

## Scrittura ed esecuzione
Bash è un linguaggio interpretato (non compilato). La prima riga di uno script può specificare l'interprete da utilizzare mediante lo *shebang* (**#!/bin/bash**). Le altre righe che iniziano con **#** sono commenti nel codice. Per ottenere uno script eseguibile direttamente è necessario seguire i seguenti passaggi:

### Scrittura di uno script
```shell
$ vim script.sh

#!/bin/bash  
echo Total number of inputs: $#  
echo First input: "$1"  
echo Second input: "$2"  
exit 0
```

### Rendere lo script eseguibile
```shell
$ chmod a+x script.sh # oppure  
$ chmod 755 script.sh
```

### Invocazione di uno script
```shell
$ ./script.sh AAPL GOOGL MSFT  
Total number of inputs: 3  
First input: AAPL  
Second input: GOOGL
```

Perché abbiamo invocato lo script con **./script.sh** piuttosto che **script.sh**? Se il nome del comando non contiene **/** e non identifica una funzione o un builtin, Bash cerca un programma eseguibile nell'elenco di directory rappresentato dalla variabile **PATH**.

Se PATH non contiene la directory **.** (che indica la directory corrente), i programmi non vengono trovati anche se si trovano nella directory corrente. Per introdurre **.** all'interno di **PATH**:

```shell
# Modifica alla variabile PATH (sconsigliato)  
$ export PATH=$PATH:. 
$ script.sh
```

### Variabili speciali
All'interno di uno script Bash è possibile accedere a un gruppo di [parametri speciali](https://www.gnu.org/software/bash/manual/html_node/Special-Parameters.html) utili per gestire gli argomenti e lo stato dell'esecuzione:

* **$0** Il nome dello script in esecuzione  
* **$1, $2, …, ${n}** n-esimo parametro passato da linea di comando (le parentesi graffe sono necessarie da ${10} in poi)
* **$\*** tutti i parametri; **"$\*"** li espande come un'unica parola, separati dal primo carattere di IFS
* **$@** tutti i parametri; **"$@"** li espande come parole separate, preservando ciascun argomento
* **$#** numero di parametri da linea di comando  
* **$$** PID della shell che esegue lo script
* **$?** valore di ritorno dell'ultimo comando eseguito  

**shift** elimina il primo parametro dalla lista $1...$n, tutti gli altri scorrono indietro di una posizione. Può essere invocato senza parametri oppure specificando il numero di shift da eseguire.

```shell 
$ vim test.sh

#!/bin/bash
echo "[$#]" "$@" # mostra [numero dei parametri] tutti i parametri
shift         # elimina il primo parametro
echo "[$#]" "$@" # mostra [numero dei parametri] tutti i parametri
shift 3       # elimina i primi tre parametri
echo "[$#]" "$@" # mostra [numero dei parametri] tutti i parametri

```

```shell
./test.sh -a -b -c -d -e -f -g -h
[8] -a -b -c -d -e -f -g -h
[7] -b -c -d -e -f -g -h
[4] -e -f -g -h
```

### Commenti
È possibile inserire commenti nel codice utilizzando il carattere #.

```shell
#!/bin/bash

# Questo è un commento

exit 0
```

### ShellCheck (static analysis)
[ShellCheck](https://github.com/koalaman/shellcheck) è uno strumento GPLv3 che fornisce avvisi e suggerimenti per gli script di shell bash:

Gli obiettivi di ShellCheck sono:

* Evidenziare e chiarire i tipici problemi di sintassi dei principianti che fanno sì che una shell fornisca messaggi di errore criptici.
* Evidenziare e chiarire i tipici problemi semantici di livello intermedio che causano un comportamento strano e controintuitivo.
* Evidenziare sottili difetti, casi limite, e insidie ​​che potrebbero causare il fallimento dello script in circostanze future.


## Costrutti condizionali

### test
**test** è un comando per eseguire verifiche di varia natura sulle stringhe (interpretandole in base ai casi come stringhe, numeri o file). Un controllo avvenuto con successo ritorna 0, altrimenti 1.

```shell
$ test 5 -gt 3; echo $?               # 0  
$ test 3 -gt 5; echo $?               # 1  
$ test "nicola" == "nicola"; echo $?  # 0  
$ test "nicola" == "mario"; echo $?   # 1  
$ test -f /etc/passwd; echo $?        # 0  
$ test -d /etc/passwd; echo $?        # 1
```

### test (strings)
```
-n STRING           the length of STRING is nonzero
-z STRING           the length of STRING is zero
STRING1 = STRING2   the strings are equal
STRING1 != STRING2  the strings are not equal
```

### test (numbers)
```
INTEGER1 -eq INTEGER2   INTEGER1 is equal to INTEGER2
INTEGER1 -ge INTEGER2   INTEGER1 is greater than or equal to INTEGER2
INTEGER1 -gt INTEGER2   INTEGER1 is greater than INTEGER2
INTEGER1 -le INTEGER2   INTEGER1 is less than or equal to INTEGER2
INTEGER1 -lt INTEGER2   INTEGER1 is less than INTEGER2
INTEGER1 -ne INTEGER2   INTEGER1 is not equal to INTEGER2
```

### test (files)
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

### test (logic)
```
! EXPRESSION                  EXPRESSION is false
EXPRESSION1 -a EXPRESSION2    both EXPRESSION1 and EXPRESSION2 are true
EXPRESSION1 -o EXPRESSION2    either EXPRESSION1 or EXPRESSION2 is true
```

Ad esempio:

```shell
$ test -f /etc/passwd -a -r /etc/passwd; echo $?
0

$ test ! -d /etc/passwd -o ! -w /etc/passwd; echo $?
0
```

Nonostante sia ancora supportata, questa sintassi è sconsigliata e va sostituita con **&&** e **||**.


```shell
$ test -f /etc/passwd && test -r /etc/passwd; echo $?
0

$ test ! -d /etc/passwd || test ! -w /etc/passwd; echo $?
0
```

### [ ]
Il comando test ha un alter ego che si comporta nello stesso modo ma ha nome diverso ([). Il comando è stato introdotto principalmente per aumentare la leggibilità degli script in particolare per l'utilizzo congiunto con la direttiva **if**.

Gli spazi che vedete nell'esempio sotto, dopo [ e prima di ] sono obbligatori! La loro assenza produce errori!

```shell
$ type test
test is a shell builtin
$ type [
[ is a shell builtin
```

```shell
$ [ -f /etc/passwd ] && [ -r /etc/passwd ]; echo $?
0

$ [ ! -d /etc/passwd ] || [ ! -w /etc/passwd ]; echo $?
0
```

### if
**if** consente di verificare il valore di ritorno di un comando e eseguire istruzioni differenziate in caso la condizione risulti vera o falsa.

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
if [ -f "$1" ] && [ -r "$1" ]; then
  echo "$1" è un file leggibile!
fi
```

```shell
if [ ! -d "$1" ] || [ ! -x "$1" ]; then
  echo "$1" non è una directory eseguibile!
fi
```

```shell
if [ $# -ne 3 ]; then
  echo "params != 3"
else
  echo "params == 3"
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

In caso una condizione determini l'esecuzione di poche istruzioni e non sia necessario differenziare il caso di successo da quello di fallimento (ma eseguirne uno solo) è possibile utilizzare una forma sintetica (&&,||) che non prevede l'utilizzo di **if**

```shell
$ [ 1 -eq 0 ] && echo "pass"           #
$ [ 1 -eq 1 ] && echo "pass"           # pass
$ [ 1 -eq 0 ] || echo "fail"           # fail
$ [ 1 -eq 1 ] || echo "fail"           #
$ [ 1 -eq 1 ] && (echo "pass"; pwd)    # stampa pass e poi la directory corrente
```

**if** può essere utilizzato per valutare l'esito di comandi arbitrari, non solo di **test**. Nell'esempio sotto, **grep** ritorna 0 in caso la stringa *nicola* sia trovata all'interno di */etc/passwd*

```shell
if grep nicola /etc/passwd; then
  echo "nicola è un utente del sistema"
else
  echo "nicola NON è un utente del sistema"
fi
```

### Pattern matching
Il pattern matching consiste nel confrontare un valore con un determinato pattern
frequentemente specificato utilizzando wildcards.

```
Stringa     Pattern     Match?
------------------------------
ABCDEF      A*          Si

ABCDEF      AB??EF      Si

ABCDEF      ABCNN*      No
```

Il costrutto test / [ ] non supporta pattern matching!

### [[ ]]
Il costrutto [[ ]] offre controlli simili a [ ], aggiungendo, fra le altre cose, il [pattern matching](https://www.gnu.org/software/bash/manual/html_node/Pattern-Matching.html). Per approfondire, leggi [qui](https://mywiki.wooledge.org/BashFAQ/031).

```shell
# [ ] fallisce
if [ "$1" == n?co* ]; then
  echo "success"
fi

if [ "$1" != [0-9]* ]; then
  echo "success"
fi
```

```shell
# [[ ]] supporta pattern matching
if [[ "$1" == n?co* ]]; then
  echo "success"
fi

if [[ "$1" != [0-9]* ]]; then
  echo "success"
fi
```

### case
Il costrutto **case** abbina il [pattern matching](https://www.gnu.org/software/bash/manual/html_node/Pattern-Matching.html) alla possibilità di eseguire più confronti in modo sintetico (evitando catene di elif).

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

In questo esempio, **case** viene utilizzato per determinare il tipo di percorso rappresentato dalla variabile **$1**

```shell
case "$1" in
  /*) 
    echo "Percorso assoluto"
    ;;
  */*) 
    echo "Percorso relativo"
    ;;
  *) 
    echo "Nome semplice di file"
    ;;
esac
```

In questo esempio, **case** viene utilizzato per determinare se **$1** contiene un intero non negativo, espresso con sole cifre decimali.

```shell
case "$1" in
  ''|*[!0-9]*)
    echo "Il parametro non è numerico"
    ;;
  *) 
    echo "Il parametro è numerico"
    ;;
esac
```

---

## Costrutti iterativi

### for
```shell
for argomento in lista; do  
   comando/i  
   ...  
done
```

```shell
# Esempio: tabellina del 5  
for i in 1 2 3 4 5; do  
  echo "5 * $i = $(( 5 * i ))"  
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
  echo "5 * $i = $(( 5 * i ))"  
done

5 * 1 = 5
5 * 2 = 10
5 * 3 = 15
5 * 4 = 20
5 * 5 = 25
```

### while

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
  i=$(( i - 1 ))
done
```

### Espansione nomi di file
I filesystem Unix supportano nomi di file contenenti spazi e metacaratteri. Di conseguenza, per evitare suddivisioni in parole ed espansioni indesiderate, le variabili usate come singoli argomenti (ad es. nomi di file) vanno espanse fra doppie virgolette " ".

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

## Argomenti avanzati

### Funzioni

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
  [ -d "$1" ] && [ -x "$1" ] && return 0
  return 1
}

for f in "$@"; do
  printf '%s' "$f"
  if process "$f"; then
    echo " [pass]"
  else
    echo " [fail]"
  fi
done

exit 0
```


### Script multi-file 
```shell
$ vim lib.sh

#!/bin/bash 
process() {  
  [ -d "$1" ] && [ -x "$1" ] && return 0  
  return 1  
}
```

``` shell 
$ vim script.sh  

 #!/bin/bash
 
 source lib.sh  
 # oppure  
 # . lib.sh
 
for f in "$@"; do
  printf '%s' "$f"
  if process "$f"; then
    echo " [pass]"
  else
    echo " [fail]"
  fi
done

exit 0
```

### Arrays
Un array indicizzato raccoglie più valori in un'unica variabile. Gli elementi sono identificati da indici interi; nella sintassi seguente vengono assegnati a partire da **0**.

```bash
nomi=()                              # array vuoto
nomi=("Anna" "Mario Rossi" "Luca")    # tre elementi

echo "${nomi[0]}"                     # Anna
echo "${nomi[1]}"                     # Mario Rossi
echo "${#nomi[@]}"                    # 3: numero di elementi
```

Le parentesi tonde definiscono l'array; le parentesi graffe delimitano l'espansione di un elemento. Le virgolette permettono di inserire spazi all'interno di un singolo valore.

### Arrays: iterazione e quoting

**"${nomi[@]}"** espande ogni elemento come un argomento distinto, preservando spazi ed eventuali metacaratteri.

```bash
nomi=("Anna" "Mario Rossi" "Luca")

for nome in "${nomi[@]}"; do
  printf '%s\n' "$nome"
done
```

Output:

```text
Anna
Mario Rossi
Luca
```

Senza virgolette, **${nomi[@]}** è soggetto a suddivisione in parole ed espansione dei nomi di file: nell'esempio, **Mario Rossi** verrebbe trattato come due parole.

### Arrays: @ e *

La differenza è analoga a quella tra **"$@"** e **"$\*"** per i parametri di uno script:

* **"${nomi[@]}"** produce un argomento per elemento;
* **"${nomi[*]}"** produce un unico argomento, unendo gli elementi con il primo carattere di **IFS** (uno spazio con il valore predefinito).

```bash
nomi=("Anna" "Mario Rossi" "Luca")

printf '<%s>\n' "${nomi[@]}"
# <Anna>
# <Mario Rossi>
# <Luca>

printf '<%s>\n' "${nomi[*]}"
# <Anna Mario Rossi Luca>
```

Per iterare sugli elementi, usare normalmente **"${nomi[@]}"**. Se l'array è vuoto, questa espansione non produce argomenti e il ciclo non esegue iterazioni.

### Arrays: modifica e indici

È possibile aggiungere, sostituire e rimuovere elementi. **La rimozione non rinumera gli elementi successivi**: un array può avere indici non consecutivi.

```bash
nomi=("Anna" "Mario Rossi" "Luca")
nomi+=("Sara")                       # aggiunge un elemento in fondo
nomi[0]="Anna Maria"                 # sostituisce l'elemento di indice 0
unset 'nomi[1]'                      # rimuove l'elemento di indice 1

for i in "${!nomi[@]}"; do           # espande gli indici presenti
  printf '%s: %s\n' "$i" "${nomi[i]}"
done
```

Output:

```text
0: Anna Maria
2: Luca
3: Sara
```

**${#nomi[@]}** vale ora **3**, non 4: conta gli elementi presenti, non l'indice massimo più uno. Le virgolette nell'argomento di **unset** impediscono che le parentesi quadre siano interpretate come metacaratteri dalla shell.

### Arrays: sottoinsiemi e lunghezze

La sintassi **"${array[@]:s:n}"** seleziona fino a **n** elementi a partire dall'indice **s**, per un array indicizzato con offset non negativo.

```bash
numeri=(10 20 30 40 50)
selezionati=("${numeri[@]:1:3}")

printf '%s\n' "${selezionati[@]}"     # stampa 20, 30 e 40 su righe separate
```

Il numero di elementi dell'array è distinto dalla lunghezza di un singolo elemento:

```bash
nomi=("Anna" "Mario Rossi" "Luca")

echo "${#nomi[@]}"                    # 3: numero di elementi
echo "${#nomi[0]}"                    # 4: caratteri del primo elemento
```

### Arrays associativi

Da **Bash 4.0**, un array associativo permette di usare chiavi testuali al posto degli indici interi. Deve essere dichiarato con **declare -A**.

```bash
declare -A porte=(
  [http]=80
  [https]=443
)

echo "${porte[https]}"                # 443
porte[ssh]=22                        # aggiunge una coppia chiave-valore

for servizio in "${!porte[@]}"; do
  printf '%s: %s\n' "$servizio" "${porte[$servizio]}"
done
```

**"${!porte[@]}"** espande le chiavi presenti. L'ordine di iterazione di un array associativo **non è garantito**.

### Arrays: ricerca nei log

Due array possono rappresentare i file da analizzare e le parole chiave da cercare. I cicli annidati verificano ogni parola chiave in ciascun file.

I percorsi dei log dipendono dalla distribuzione: scegliere file esistenti e leggibili sul proprio sistema.

```shell
#!/bin/bash

files=(/var/log/kern.log /var/log/auth.log /var/log/syslog)  
keyw=(nicola marzia)

echo "* searching ${#files[@]} files with ${#keyw[@]} keywords"
echo "* press enter to continue..."
read

for f in "${files[@]}"; do
  for k in "${keyw[@]}"; do
    l=$(grep -F -c -- "$k" "$f")
    echo "* ${f}: found ${l} lines containing ${k}!"
  done
done
```

**grep -F** cerca una stringa letterale; **-c** conta le righe che la contengono, non le singole occorrenze. Una riga che contiene più volte la stessa parola viene contata una sola volta.

### getopts
Comando interno (**builtin**) per gestire le opzioni a linea di comando. Altri linguaggi offrono strumenti analoghi.
* getopts viene normalmente utilizzato con un while e un case
* La stringa "m:dh" rappresenta i parametri da controllare. Le lettere singole (e.g., d e h) rappresentano parametri senza argomenti. Le lettere seguite da **:** (e.g., m) rappresentano parametri con argomenti
* getopts scansiona la linea di comando e a ogni ciclo aggiorna la variabile **o** affinché sia analizzata dal blocco case
* Il blocco case, tipicamente, assegna a delle variabili il valore degli argomenti (**OPTARG**)

```shell
while getopts "m:dh" o; do  
  case "$o" in  
    m) 
      MESSAGE="$OPTARG"  
      ;;  
    d) 
      DEBUG=TRUE  
      ;;
    h) 
      usage  
      ;;  
    *) 
      usage  
      ;;  
  esac  
done
shift "$((OPTIND - 1))"
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
    case "$o" in
        m) 
          MESSAGE="$OPTARG"
          ;;
        d) 
          DEBUG=TRUE
          ;;
        h) 
          usage
          ;;
        *) 
          usage
          ;;
    esac
done
# Shift parameters away. $1 becomes filename
shift "$((OPTIND - 1))"

# Additional checks
# Check if filename exists
[ -e "$1" ] || usage

echo m = "$MESSAGE"
echo d = "$DEBUG"
echo filename = "$1"
exit 0
```

### Buone pratiche
* L'indentazione non determina i blocchi di codice, ma è fondamentale per la leggibilità.
* Usare nomi coerenti per le variabili. I nomi MAIUSCOLI sono comunemente riservati a costanti e variabili d'ambiente; evitare conflitti con nomi di sistema come PATH.
* Il controllo dei parametri avviene in **via negativa**. Si controllano le condizioni di fallimento e, se verificate, si termina lo script ritornando un codice errore (exit 1). Questa pratica evita indentazione eccessiva  
* I valori di uscita (exit) distinguono il successo (exit 0) dal fallimento (valore diverso da 0). Per differenziare i tipi di fallimento si possono utilizzare codici diversi nell'intervallo 1–255; i codici da 126 in poi hanno significati convenzionali nella shell.
* I nomi di file possono contenere spazi e metacaratteri. Le variabili usate come singoli argomenti vanno quindi espanse fra doppie virgolette (ad es. echo "$filename").
* Aderire ad una struttura nota:
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
	
if [ ! -d "$1" ] || [ ! -x "$1" ]; then
  usage
fi
  
# Corpo principale
F=0; D=0
for fname in "$1"/*; do
	if [ -f "$fname" ]; then
	  F=$(( F + 1 ))
	fi
	
  if [ -d "$fname" ]; then
	  D=$(( D + 1 ))
	fi
done
	
echo "#files=$F, #directories=$D"

# Terminazione
exit 0
```

### Bash vs Python per la scrittura di script

**Bash**  

+ Molto diffusa nei sistemi Unix-like
+ Integrazione profonda con Unix (piping, ridirezione)  
- Non offre OOP né multithreading nativo; le strutture dati sono limitate
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
for fname in "$@"; do
   l=$(wc -l < "$fname")
   echo "$fname": "$l"
done

exit 0
```

```python
#!/usr/bin/env python3

import sys
import subprocess

if len(sys.argv) < 2:
   sys.stderr.write("usage: %s f1 .. fn\n" % (sys.argv[0]))
   sys.exit(1)
   
for fname in sys.argv[1:]:
  with open(fname, 'rb') as stream:
    out = subprocess.check_output(['wc', '-l'], stdin=stream, text=True)
  print("%s: %s" % (fname, out.strip()))
  
sys.exit(0)
```
