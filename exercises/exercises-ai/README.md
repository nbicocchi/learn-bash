# Esempi di esercizi — Unix e Bash

## Esercizio 1 — Riepilogo degli argomenti

**Tempo indicativo: 7–9 minuti.**

### 1. Teoria — Scelta multipla

Quale affermazione descrive correttamente il rapporto tra applicazioni e kernel in un sistema Unix?

- **A.** Ogni applicazione gestisce direttamente l'hardware, senza mediazione del kernel.
- **B.** Il kernel gestisce le risorse del sistema; le applicazioni accedono ai suoi servizi tramite chiamate di sistema.
- **C.** Il kernel è la shell che interpreta i comandi digitati nel terminale.
- **D.** Le applicazioni vengono eseguite sempre in modalità kernel, con accesso illimitato all'hardware.

### Scenario

Uno script riceve nomi di file come argomenti e conta quelli che terminano con `.log`. L'opzione `-p` permette di scegliere l'etichetta del riepilogo; se omessa, l'etichetta è `log`. Lo script analizza soltanto i nomi ricevuti: non verifica che i file esistano e distingue maiuscole e minuscole.

Si usa una nuova Bash non interattiva, senza configurazioni personalizzate. Le opzioni precedono i nomi dei file; questi ultimi non iniziano con `-` e possono contenere spazi. Senza nomi di file, il conteggio deve essere zero.

I numeri di riga non fanno parte del codice.

```text
 1  #!/bin/bash
 2  prefix="log"
 3  count=0
 4
 5  while getopts "p:" option; do
 6    case "$option" in
 7      p) prefix="$OPTARG" ;;
 8      *) exit 2 ;;
 9    esac
10  done
11  shift "$((OPTIND - 1))"
12
13  for name in "$@"; do
14    case "$name" in
15      *.log) count=$((count + 1)) ;;
16    esac
17  done
18
19  printf '%s: %s\n' "$prefix" "$count"
```

### 2. Scenario — Scelta multipla

Quale riga viene scritta su standard output con questa invocazione?

```bash
./riepilogo.sh -p produzione app.log "vecchi dati.log" note.txt
```

- **A.** `log: 2`
- **B.** `produzione: 3`
- **C.** `produzione: 1`
- **D.** `produzione: 2`

### 3. Scenario — Riprogettazione

Aggiungi l'opzione **`-a`**, senza argomento: quando presente, il conteggio deve includere tutti i nomi ricevuti, indipendentemente dall'estensione. In sua assenza deve rimanere il comportamento originale. L'opzione `-p` deve continuare a funzionare e, senza nomi, il conteggio deve restare zero. Deve essere possibile usare `-a` e `-p` in qualsiasi ordine, prima dei nomi.

Indica soltanto le righe da aggiungere o sostituire e motiva brevemente la soluzione. **Sono sufficienti poche righe di codice e 1–2 frasi.**

<details>
<summary>Mostra la soluzione dell'esercizio 1</summary>

### 1. Teoria — Scelta multipla: B

Il kernel gestisce risorse come CPU, memoria e dispositivi. Le applicazioni vengono eseguite nello spazio utente e possono richiedere servizi al kernel tramite chiamate di sistema.

- **A errata:** le normali applicazioni non hanno accesso diretto e illimitato all'hardware; il kernel media l'accesso alle risorse protette.
- **C errata:** la shell è un programma nello spazio utente, distinto dal kernel.
- **D errata:** il codice delle normali applicazioni viene eseguito in modalità utente; l'esecuzione di una chiamata di sistema comporta l'ingresso nel kernel per il servizio richiesto.

### 2. Scenario — Scelta multipla: D

`getopts` assegna `produzione` a `prefix`. Dopo lo `shift` rimangono tre argomenti: `app.log`, `vecchi dati.log` e `note.txt`. Il ciclo conserva separato ciascun argomento grazie a `"$@"`; i primi due nomi corrispondono al pattern `*.log`.

- **A errata:** l'opzione `-p` sostituisce l'etichetta predefinita `log` con `produzione`.
- **B errata:** `note.txt` non termina con `.log` e non viene contato.
- **C errata:** lo spazio in `vecchi dati.log` non divide il nome in due argomenti, né impedisce la corrispondenza con `*.log`.

### 3. Scenario — Riprogettazione

Dopo la riga 3, inizializzare la modalità di conteggio:

```bash
all=0
```

Sostituire la riga 5, aggiungendo `a` senza i due punti:

```bash
while getopts "p:a" option; do
```

Nel `case` delle opzioni, prima del ramo `*`, aggiungere:

```bash
a) all=1 ;;
```

Sostituire le righe 14–16 con:

```bash
if [ "$all" -eq 1 ] || [[ "$name" == *.log ]]; then
  count=$((count + 1))
fi
```

Il flag memorizza la presenza di `-a`, mentre `getopts` continua a gestire entrambe le opzioni prima degli argomenti residui. Il ciclo incrementa il conteggio una sola volta per ogni nome ammesso dalla modalità scelta; senza nomi non esegue iterazioni.

**Alternativa valida:** lasciare invariato il ciclo originale e, prima della stampa finale, assegnare `count=$#` quando `all` vale `1`. Anche questa soluzione richiede l'inizializzazione del flag e le modifiche a `getopts` e al relativo `case`.

</details>

## Esercizio 2 — Destinazione dei messaggi

**Tempo indicativo: 7–9 minuti.**

### 1. Teoria — Scelta multipla

Che cosa comprende normalmente una distribuzione Linux?

- **A.** Soltanto il kernel, senza programmi utilizzabili dall'utente.
- **B.** Un ambiente grafico che sostituisce il kernel.
- **C.** Kernel, utilità di sistema e pacchetti applicativi organizzati per l'installazione e l'uso.
- **D.** Soltanto una shell e il suo file di configurazione.

### Scenario

Uno script produce un risultato su stdout e una segnalazione su stderr. La funzione rappresenta una fase di elaborazione, qui ridotta a due stampe. Si vuole studiare la destinazione dei messaggi, non il loro ordine temporale tra flussi distinti. `report.txt` è scrivibile e le operazioni di I/O riescono.

I numeri di riga non fanno parte del codice.

```text
 1  #!/bin/bash
 2
 3  produce() {
 4    printf 'risultato\n'
 5    printf 'avviso\n' >&2
 6  }
 7
 8  produce 2>&1 > report.txt
 9  status=$?
10  exit "$status"
```

### 2. Scenario — Scelta multipla

Lo script è avviato da un terminale senza ridirezioni esterne. Dove finiscono i due messaggi?

- **A.** Entrambi in `report.txt`.
- **B.** `risultato` nel file e `avviso` sul terminale.
- **C.** `avviso` nel file e `risultato` sul terminale.
- **D.** Entrambi sul terminale; il file rimane vuoto.

### 3. Scenario — Riprogettazione

Si richiede ora di raccogliere entrambi i messaggi in `report.txt`, **aggiungendoli** al contenuto già presente. Sostituisci soltanto la riga 8 e spiega il ruolo dell'ordine delle ridirezioni. Sono sufficienti una riga e 1–2 frasi.

<details>
<summary>Mostra la soluzione dell'esercizio 2</summary>

### 1. Teoria — Scelta multipla: C

Una distribuzione integra il kernel con gli strumenti e i pacchetti necessari a utilizzare il sistema.

- **A errata:** descrive il solo kernel, non una distribuzione utilizzabile.
- **B errata:** un ambiente grafico non sostituisce il kernel.
- **D errata:** shell e configurazione sono soltanto una piccola parte del sistema.

### 2. Scenario — Scelta multipla: B

Le ridirezioni sono elaborate da sinistra a destra: stderr viene prima associato alla destinazione iniziale di stdout, il terminale; successivamente solo stdout viene diretto al file.

- **A errata:** stderr non segue le successive modifiche di stdout.
- **C errata:** è stdout, non stderr, a essere diretto al file con `>`.
- **D errata:** la seconda ridirezione invia effettivamente stdout al file.

### 3. Scenario — Riprogettazione

Sostituire la riga 8 con:

```bash
produce >> report.txt 2>&1
```

Prima stdout viene aperto in append sul file; poi stderr ne condivide la destinazione. `>>` preserva il contenuto precedente.

</details>

## Esercizio 3 — Configurazione di un processo figlio

**Tempo indicativo: 7–9 minuti.**

### 1. Teoria — Scelta multipla

Quale informazione è normalmente memorizzata in `/etc/shadow` per un utente con password locale impostata?

- **A.** L'hash della password e informazioni sulla sua scadenza.
- **B.** La password in chiaro.
- **C.** La lista dei processi avviati dall'utente.
- **D.** Il contenuto della directory personale.

### Scenario

Uno script prepara una configurazione e avvia una nuova istanza di Bash. Prima dell'esecuzione, `MODE` non è presente nell'ambiente. Non vengono letti file di configurazione personalizzati e nessun file di avvio modifica le variabili. Le stringhe passate a `bash -c` sono comandi eseguiti dalla nuova Bash.

I numeri di riga non fanno parte del codice.

```text
 1  #!/bin/bash
 2  MODE="locale"
 3
 4  inspect() {
 5    printf 'figlio=%s\n' "$MODE"
 6    MODE="interno"
 7  }
 8
 9  bash -c 'printf "figlio=%s\n" "$MODE"; MODE="remoto"'
10  printf 'padre=%s\n' "$MODE"
```

### 2. Scenario — Scelta multipla

Qual è l'output dello script?

- **A.** `figlio=locale`, poi `padre=remoto`.
- **B.** `figlio=locale`, poi `padre=locale`.
- **C.** `figlio=interno`, poi `padre=locale`.
- **D.** `figlio=`, poi `padre=locale`.

### 3. Scenario — Domanda aperta

Valuta questa proposta: «Aggiungere `export MODE` prima della riga 9 permette al figlio di leggere `locale` e di restituire automaticamente al padre il nuovo valore `remoto`». Quali parti sono corrette? Spiega anche se la funzione `inspect` viene eseguita. Rispondi in 2–3 frasi.

<details>
<summary>Mostra la soluzione dell'esercizio 3</summary>

### 1. Teoria — Scelta multipla: A

Il file contiene, tra gli altri campi, l'hash della password e i dati usati per gestirne la validità.

- **B errata:** la password non viene normalmente conservata in chiaro.
- **C errata:** i processi non sono registrati in questo file.
- **D errata:** il contenuto della home appartiene al filesystem, non a shadow.

### 2. Scenario — Scelta multipla: D

`MODE` non è esportata: la nuova Bash non la riceve. La modifica nel figlio non cambia la variabile del padre; la funzione è soltanto definita, non invocata.

- **A errata:** presuppone sia l'eredità della variabile non esportata sia una propagazione delle modifiche verso il padre.
- **B errata:** il figlio non riceve `locale` senza export.
- **C errata:** nessuno chiama `inspect`.

### 3. Scenario — Domanda aperta

`export MODE` permette al figlio di ricevere il valore iniziale `locale`, ma le modifiche del figlio non aggiornano l'ambiente del padre, che continua a contenere `locale`. Per trasferire un risultato occorre un meccanismo esplicito, ad esempio produrlo su stdout e acquisirlo nel padre. La funzione `inspect` non viene mai chiamata.

</details>

## Esercizio 4 — Elenco delle attività

**Tempo indicativo: 7–9 minuti.**

### 1. Teoria — Scelta multipla

Due nomi sono hard link allo stesso file. Che cosa accade rimuovendo uno dei nomi con `rm`?

- **A.** Il contenuto viene svuotato.
- **B.** Anche l'altro nome viene rimosso.
- **C.** L'altro nome diventa un link simbolico non valido.
- **D.** L'altro nome continua a riferirsi allo stesso inode e ai dati del file.

### Scenario

Uno script mantiene un elenco di attività in un array indicizzato. Una voce viene rimossa e una nuova attività viene aggiunta in fondo. Lo script non accede al filesystem; le stringhe rappresentano soltanto nomi di attività.

I numeri di riga non fanno parte del codice.

```text
 1  #!/bin/bash
 2  tasks=("copia" "verifica" "invio")
 3  unset 'tasks[1]'
 4  tasks+=("archivio")
 5
 6  for i in "${!tasks[@]}"; do
 7    printf '%s=%s\n' "$i" "${tasks[i]}"
 8  done
 9
10  printf 'totale=%s\n' "${#tasks[@]}"
```

### 2. Scenario — Scelta multipla

Quale sequenza di righe produce lo script?

- **A.** `0=copia`, `1=invio`, `2=archivio`, `totale=3`.
- **B.** `0=copia`, `2=invio`, `3=archivio`, `totale=3`.
- **C.** `0=copia`, `2=invio`, `3=archivio`, `totale=4`.
- **D.** `0=copia`, `1=verifica`, `2=invio`, `3=archivio`, `totale=4`.

### 3. Scenario — Domanda aperta

Un collega propone di sostituire il ciclo con un contatore che usa gli indici `0`, `1`, … fino a `${#tasks[@]} - 1`, sostenendo che visiterà tutte le attività presenti. La proposta è corretta per questo array? Indica quale attività verrebbe omessa e spiega perché il ciclo originale è adatto. Rispondi in 2–3 frasi.

<details>
<summary>Mostra la soluzione dell'esercizio 4</summary>

### 1. Teoria — Scelta multipla: D

Gli hard link associano nomi diversi allo stesso inode; la rimozione di uno non elimina gli altri.

- **A errata:** `rm` non svuota il contenuto del file ancora collegato.
- **B errata:** viene rimosso il nome specificato.
- **C errata:** un hard link non si trasforma in un link simbolico.

### 2. Scenario — Scelta multipla: B

`unset` rimuove l'indice 1 senza rinumerare gli altri. L'aggiunta usa l'indice successivo al massimo presente, cioè 3. Gli elementi sono tre.

- **A errata:** suppone una rinumerazione automatica.
- **C errata:** confonde il numero di elementi con l'indice massimo più uno.
- **D errata:** ignora la rimozione di `verifica`.

### 3. Scenario — Domanda aperta

Il contatore visiterebbe gli indici 0, 1 e 2: l'indice 1 è assente e `archivio`, all'indice 3, verrebbe omesso. `${#tasks[@]}` conta gli elementi, non definisce l'intervallo degli indici. `"${!tasks[@]}"` espande invece tutti e soli gli indici presenti.

</details>

## Esercizio 5 — Elaborazione di una sequenza

**Tempo indicativo: 7–9 minuti.**

### 1. Teoria — Scelta multipla

Qual è il ruolo dello scheduler del kernel?

- **A.** Stabilire quali processi possono utilizzare la CPU e per quanto tempo.
- **B.** Tradurre i nomi dei file in estensioni.
- **C.** Conservare le password degli utenti in chiaro.
- **D.** Interpretare esclusivamente gli script Bash.

### Scenario

Uno script riceve una sequenza di interi decimali positivi, senza zeri iniziali. Deve sommarli finché incontra il valore `0`, che funge da terminatore; gli argomenti successivi non devono essere elaborati. Si assume che le somme rientrino nell'intervallo degli interi gestiti da Bash.

I numeri di riga non fanno parte del codice.

```text
 1  #!/bin/bash
 2  total=0
 3
 4  while [ "$#" -gt 0 ]; do
 5    if [ "$1" -eq 0 ]; then
 6      break
 7    fi
 8    total=$((total + $1))
 9    shift
10  done
11
12  printf '%s\n' "$total"
```

`break` termina immediatamente il ciclo che lo contiene.

### 2. Scenario — Scelta multipla

Quale risultato produce `./somma.sh 4 7 0 9`?

- **A.** Stampa `20`.
- **B.** Non termina, perché il valore `0` non viene rimosso con shift.
- **C.** Stampa `11`.
- **D.** Stampa `0`, perché l'ultimo valore controllato è zero.

### 3. Scenario — Riprogettazione

Modifica lo script affinché stampi `media=VALORE`, dove VALORE è la media intera dei numeri effettivamente sommati, scartando l'eventuale parte frazionaria. Se non sono stati elaborati numeri, deve stampare `nessun dato`, senza dividere per zero. Il terminatore mantiene il suo significato.

Indica le inizializzazioni, l'aggiornamento nel ciclo e il blocco finale necessari. Sono sufficienti poche righe e una breve motivazione.

<details>
<summary>Mostra la soluzione dell'esercizio 5</summary>

### 1. Teoria — Scelta multipla: A

Lo scheduler gestisce l'assegnazione del tempo CPU ai processi.

- **B errata:** non riguarda la pianificazione dei processi.
- **C errata:** non è un compito dello scheduler e le password non vengono normalmente conservate in chiaro.
- **D errata:** l'interpretazione degli script spetta alla shell.

### 2. Scenario — Scelta multipla: C

Vengono sommati 4 e 7; al valore 0 il ciclo termina con `break`, prima di sommare o eseguire shift.

- **A errata:** include il 9 successivo al terminatore.
- **B errata:** `break` esce dal ciclo anche senza rimuovere il parametro.
- **D errata:** il controllo del terminatore non azzera `total`.

### 3. Scenario — Riprogettazione

Dopo la riga 2, aggiungere:

```bash
count=0
```

Dopo la riga 8 e prima di shift, aggiungere:

```bash
count=$((count + 1))
```

Sostituire la riga 12 con:

```bash
if [ "$count" -eq 0 ]; then
  printf 'nessun dato\n'
else
  printf 'media=%s\n' "$((total / count))"
fi
```

Il conteggio aumenta soltanto per i valori elaborati. L'aritmetica intera elimina la parte frazionaria; il controllo protegge il caso senza dati, compresa una sequenza che inizia con 0.

</details>

## Esercizio 6 — Verifica di un servizio

**Tempo indicativo: 7–9 minuti.**

### 1. Teoria — Scelta multipla

Cosa comporta normalmente l'esecuzione di `sudo -i` autorizzata dalla configurazione del sistema?

- **A.** Trasforma permanentemente l'account corrente in root.
- **B.** Rimuove la necessità di controllare i permessi dei file per tutti gli utenti.
- **C.** Apre una nuova shell con i privilegi dell'utente di destinazione, normalmente root, fino alla sua chiusura.
- **D.** Esegue tutti i futuri terminali dell'utente come root.

### Scenario

Uno script verifica se il nome di servizio ricevuto è quello previsto. La funzione esprime il risultato con un codice di ritorno; il chiamante decide quale messaggio stampare. Lo script riceve esattamente un argomento, anche eventualmente diverso da `web`.

I numeri di riga non fanno parte del codice.

```text
 1  #!/bin/bash
 2  check() {
 3    if [ "$1" = "web" ]; then
 4      return 0
 5    fi
 6    return 1
 7  }
 8  if check "$1"; then
 9    printf 'pronto\n'
10  else
11    printf 'non disponibile\n'
12  fi
13  printf 'fine\n'
```

### 2. Scenario — Scelta multipla

Che cosa stampa `./servizio.sh database`?

- **A.** `non disponibile`, poi `fine`.
- **B.** Soltanto `non disponibile`.
- **C.** `pronto`, poi `fine`.
- **D.** Soltanto `fine`, perché il codice 1 non produce messaggi.

### 3. Scenario — Domanda aperta

Un collega sostituisce entrambi i `return` della funzione con `exit`, mantenendo gli stessi codici. Il comportamento del chiamante rimane equivalente? Descrivi l'effetto per l'invocazione proposta e spiega quale istruzione è adatta al contratto della funzione. Rispondi in 2–3 frasi.

<details>
<summary>Mostra la soluzione dell'esercizio 6</summary>

### 1. Teoria — Scelta multipla: C

`sudo -i` apre una shell di login per l'utente di destinazione; non modifica permanentemente l'identità dell'account originario.

- **A errata:** l'account originale rimane invariato.
- **B errata:** non cambia i controlli applicati agli altri utenti.
- **D errata:** non eleva automaticamente i futuri terminali.

### 2. Scenario — Scelta multipla: A

`check` restituisce 1; l'if esegue il ramo else e successivamente il programma continua con la stampa finale.

- **B errata:** `return` termina la funzione, non lo script.
- **C errata:** un codice diverso da zero rende falsa la condizione dell'if.
- **D errata:** il messaggio viene prodotto dal ramo else del chiamante.

### 3. Scenario — Domanda aperta

Con `exit 1` la funzione terminerebbe l'intero script, senza stampare né `non disponibile` né `fine`. Il contratto richiede `return`, che restituisce il controllo al chiamante insieme al codice di esito. Anche il ramo di successo con `exit 0` interromperebbe prematuramente lo script.

</details>

## Esercizio 7 — Catalogo delle categorie

**Tempo indicativo: 7–9 minuti.**

### 1. Teoria — Scelta multipla

Quale approccio è coerente con la filosofia Unix presentata nel corso?

- **A.** Duplicare tutte le funzioni in ogni programma per evitare strumenti esterni.
- **B.** Comporre piccoli strumenti con compiti chiari per ottenere elaborazioni più complesse.
- **C.** Usare sempre un'interfaccia grafica al posto della shell.
- **D.** Evitare la comunicazione tra programmi.

### Scenario

Un file di testo contiene record nel formato `nome:categoria`. Ogni record ha esattamente due campi non vuoti, senza altri due punti; ogni riga termina con newline. Lo script deve produrre un elenco delle categorie in ordine alfabetico, senza ripetizioni. Si assumono comandi GNU, locale `C`, file esistente e leggibile e operazioni di I/O riuscite.

I numeri di riga non fanno parte del codice.

```text
 1  #!/bin/bash
 2  if [ "$#" -ne 1 ]; then
 3    printf 'uso: %s file\n' "$0" >&2
 4    exit 1
 5  fi
 6
 7  input="$1"
 8  cut -d ':' -f 2 "$input" |
 9    sort -u
10  exit 0
```

Il file `catalogo.txt` contiene:

```text
alfa:rete
beta:disco
gamma:rete
delta:cpu
```

### 2. Scenario — Scelta multipla

Che cosa stampa `./categorie.sh catalogo.txt`?

- **A.** `rete`, `disco`, `rete`, `cpu`, su quattro righe.
- **B.** `cpu`, `disco`, `rete`, `rete`, su quattro righe.
- **C.** `3`, su una riga.
- **D.** `cpu`, `disco`, `rete`, su tre righe.

### 3. Scenario — Riprogettazione

Il nuovo requisito è scrivere su stdout soltanto il **numero di categorie distinte**, senza creare file temporanei. Sostituisci la pipeline delle righe 8–9 e spiega perché la conta deve avvenire nel punto scelto. Non è necessario imporre una formattazione degli spazi prodotti da `wc`.

<details>
<summary>Mostra la soluzione dell'esercizio 7</summary>

### 1. Teoria — Scelta multipla: B

La composizione permette di combinare strumenti semplici invece di costruire sempre un unico programma monolitico.

- **A errata:** la duplicazione sistematica contraddice questo approccio.
- **C errata:** la filosofia non impone l'interfaccia grafica.
- **D errata:** la comunicazione tra programmi è centrale nella composizione.

### 2. Scenario — Scelta multipla: D

`cut` seleziona il secondo campo e `sort -u` ordina le categorie eliminando le ripetizioni.

- **A errata:** rappresenta soltanto l'uscita di cut.
- **B errata:** ignora l'eliminazione dei duplicati con `-u`.
- **C errata:** lo script non esegue un conteggio.

### 3. Scenario — Riprogettazione

Sostituire le righe 8–9 con:

```bash
cut -d ':' -f 2 "$input" | sort -u | wc -l
```

La conta avviene dopo l'eliminazione dei duplicati: ogni categoria distinta occupa una riga. Contare prima di `sort -u` misurerebbe i record, non le categorie.

</details>

## Esercizio 8 — Classificazione degli identificatori

**Tempo indicativo: 7–9 minuti.**

### 1. Teoria — Scelta multipla

La directory corrente è `/home/anna/progetto`. A quale percorso corrisponde `../dati/input.txt`, assumendo directory ordinarie e nessun link simbolico lungo il percorso?

- **A.** `/home/dati/input.txt`
- **B.** `/dati/input.txt`
- **C.** `/home/anna/progetto/dati/input.txt`
- **D.** `/home/anna/dati/input.txt`

### Scenario

Uno script classifica gli argomenti ricevuti. Il requisito è chiamare `intero` soltanto una stringa non vuota composta interamente da cifre decimali, e `altro` ogni altro valore. Sono ammesse stringhe vuote, lettere e combinazioni di lettere e cifre. Il confronto avviene sul testo, senza valutazione aritmetica.

I numeri di riga non fanno parte del codice.

```text
 1  #!/bin/bash
 2  classify() {
 3    case "$1" in
 4      [0-9]*) printf 'intero\n' ;;
 5      *) printf 'altro\n' ;;
 6    esac
 7  }
 8
 9  for value in "$@"; do
10    classify "$value"
11  done
```

### 2. Scenario — Scelta multipla

Che cosa stampa `./classifica.sh 23 abc ""`?

- **A.** `intero`, `altro`, `altro`, su tre righe.
- **B.** `intero`, `altro`, su due righe, perché la stringa vuota viene eliminata.
- **C.** `intero`, `intero`, `altro`, su tre righe.
- **D.** Termina con errore alla stringa vuota.

### 3. Scenario — Domanda aperta

Gli input della domanda precedente bastano a dimostrare che la classificazione rispetta il requisito per tutti gli argomenti ammessi? Fornisci un caso discriminante, indicando input, risultato richiesto, risultato effettivo e motivo della differenza. Sono sufficienti 2–3 frasi; non è richiesta una correzione del codice.

<details>
<summary>Mostra la soluzione dell'esercizio 8</summary>

### 1. Teoria — Scelta multipla: D

`..` risale da progetto ad anna; da lì si accede a dati/input.txt.

- **A errata:** risale di due livelli anziché uno.
- **B errata:** tratta il percorso relativo come riferito alla radice.
- **C errata:** ignora il componente `..`.

### 2. Scenario — Scelta multipla: A

23 inizia con una cifra; abc e la stringa vuota non corrispondono al primo pattern. `"$@"` conserva anche l'argomento vuoto.

- **B errata:** un argomento vuoto non viene perso con `"$@"`.
- **C errata:** abc non inizia con una cifra.
- **D errata:** case gestisce normalmente una stringa vuota.

### 3. Scenario — Domanda aperta

No: ad esempio `2abc` dovrebbe produrre `altro`, ma produce `intero`. Nel glob `[0-9]*`, soltanto il primo carattere deve essere una cifra; `*` accetta qualsiasi suffisso, non soltanto altre cifre. I tre casi precedenti non distinguono questo comportamento dal requisito.

**Alternativa valida:** qualsiasi stringa ammessa che inizi con una cifra e contenga poi almeno un carattere non numerico.

</details>

## Esercizio 9 — Caricamento delle impostazioni

**Tempo indicativo: 7–9 minuti.**

### 1. Teoria — Scelta multipla

Quale distinzione tra terminale e shell è corretta?

- **A.** Sono due nomi dello stesso componente del kernel.
- **B.** La shell interpreta i comandi; un emulatore di terminale fornisce un'interfaccia attraverso cui interagire con essa.
- **C.** Il terminale compila gli script, mentre la shell gestisce fisicamente il monitor.
- **D.** Una shell può funzionare soltanto all'interno di un ambiente grafico.

### Scenario

Uno script carica impostazioni da un file. Viene avviato dalla directory che contiene sia `avvio.sh` sia `config.sh`. Non ci sono variabili preesistenti che interferiscono né file di avvio personalizzati. Il file di configurazione è leggibile e tutte le stampe riescono.

I numeri di riga non fanno parte del codice. Il file `config.sh` contiene:

```text
 1  label="produzione"
 2  attempts=3
```

Lo script `avvio.sh` contiene:

```text
 1  #!/bin/bash
 2  label="test"
 3  attempts=1
 4
 5  load_config() {
 6    source ./config.sh
 7  }
 8
 9  load_config
10  printf '%s:%s\n' "$label" "$attempts"
```

### 2. Scenario — Scelta multipla

Qual è l'output di `./avvio.sh`?

- **A.** `test:1`
- **B.** `produzione:1`
- **C.** `produzione:3`
- **D.** Nessun output: source richiede un file eseguibile.

### 3. Scenario — Domanda aperta

Se la riga 6 viene sostituita con `bash ./config.sh`, cosa cambia nella stampa finale e perché? La risposta cambia rendendo eseguibile config.sh, senza altre modifiche? Rispondi in 2–3 frasi.

<details>
<summary>Mostra la soluzione dell'esercizio 9</summary>

### 1. Teoria — Scelta multipla: B

L'emulatore di terminale e l'interprete dei comandi hanno ruoli distinti.

- **A errata:** non sono componenti equivalenti né parti del kernel.
- **C errata:** nessuno dei due ruoli è descritto correttamente.
- **D errata:** le shell sono utilizzabili anche senza ambiente grafico.

### 2. Scenario — Scelta multipla: C

source esegue il file nella shell corrente. Le assegnazioni non usano local, quindi modificano le variabili lette alla riga 10.

- **A errata:** ignora l'esecuzione del file di configurazione.
- **B errata:** entrambe le variabili vengono aggiornate.
- **D errata:** per source serve leggere il file, non eseguirlo come programma separato.

### 3. Scenario — Domanda aperta

La stampa diventa `test:1`: la nuova Bash modifica soltanto le proprie variabili, senza aggiornare quelle del processo chiamante. Aggiungere il permesso di esecuzione a config.sh non cambia questo isolamento; inoltre `bash ./config.sh` richiede che il file sia leggibile, non che sia direttamente eseguibile.

</details>

## Esercizio 10 — Etichetta e destinatari

**Tempo indicativo: 7–9 minuti.**

### 1. Teoria — Scelta multipla

Un file regolare ha permessi `0640`. Quali accessi sono consentiti dai soli bit tradizionali di permesso, senza ACL né privilegi speciali?

- **A.** Proprietario: lettura e scrittura; gruppo: lettura; altri: nessuno.
- **B.** Proprietario: tutti; gruppo: lettura; altri: nessuno.
- **C.** Proprietario: lettura; gruppo: lettura e scrittura; altri: nessuno.
- **D.** Proprietario: lettura e scrittura; gruppo e altri: lettura.

### Scenario

Uno script riceve come primo argomento un'etichetta, seguita dai destinatari. Deve scrivere una riga per ogni destinatario, mantenendo gli eventuali spazi nei nomi. Tutte le stampe riescono. È ammesso non specificare destinatari, ma deve esserci almeno l'etichetta.

I numeri di riga non fanno parte del codice.

```text
 1  #!/bin/bash
 2  if [ "$#" -lt 1 ]; then
 3    printf 'manca etichetta\n' >&2
 4    exit 1
 5  fi
 6  label="$1"
 7
 8  for name in "$@"; do
 9    printf '%s -> %s\n' "$label" "$name"
10  done
11  exit 0
```

### 2. Scenario — Scelta multipla

Che cosa stampa `./inviti.sh gruppo "Anna Maria" Luca`?

- **A.** Due righe: `gruppo -> Anna Maria` e `gruppo -> Luca`.
- **B.** Quattro righe, perché Anna e Maria vengono separate.
- **C.** Nessuna riga, perché gruppo non è un'opzione valida.
- **D.** Tre righe: `gruppo -> gruppo`, `gruppo -> Anna Maria`, `gruppo -> Luca`.

### 3. Scenario — Riprogettazione

Il formato diventa `./inviti.sh etichetta limite destinatari...`, dove limite è un intero decimale non negativo senza zeri iniziali. Stampa soltanto i primi limite destinatari, o tutti quelli disponibili se sono meno. Sono ammessi zero destinatari e limite zero; non è richiesta la validazione del formato numerico, garantito dalla consegna.

Indica le modifiche al controllo iniziale, alla preparazione dei parametri e al ciclo. Sono sufficienti poche righe e una breve motivazione.

<details>
<summary>Mostra la soluzione dell'esercizio 10</summary>

### 1. Teoria — Scelta multipla: A

Le cifre 6, 4 e 0 corrispondono rispettivamente a rw-, r-- e ---.

- **B errata:** il proprietario non ha il bit di esecuzione.
- **C errata:** scambia e modifica i diritti di proprietario e gruppo.
- **D errata:** assegna agli altri un diritto non presente.

### 2. Scenario — Scelta multipla: D

Assegnare `$1` a label non lo rimuove dalla lista dei parametri. Il ciclo visita quindi anche gruppo; `"$@"` conserva Anna Maria come un singolo argomento.

- **A errata:** presuppone uno shift che non è presente.
- **B errata:** ignora il quoting dei parametri.
- **C errata:** lo script non interpreta opzioni.

### 3. Scenario — Riprogettazione

Alla riga 2 controllare `[ "$#" -lt 2 ]` e aggiornare il messaggio della riga 3, ad esempio in `mancano etichetta o limite`. Dopo l'assegnazione di label, aggiungere:

```bash
limit="$2"
shift 2
sent=0
```

Sostituire il ciclo delle righe 8–10 con:

```bash
for name in "$@"; do
  [ "$sent" -ge "$limit" ] && break
  printf '%s -> %s\n' "$label" "$name"
  sent=$((sent + 1))
done
```

Lo shift rimuove i due parametri di configurazione. Il controllo precede la stampa, quindi limite zero non produce righe e la lista vuota rimane gestita correttamente.

</details>

## Esercizio 11 — Contenuto di una directory

**Tempo indicativo: 7–9 minuti.**

### 1. Teoria — Scelta multipla

Perché è importante smontare il filesystem di una chiavetta prima di estrarla?

- **A.** Per cancellare automaticamente i file temporanei di tutti gli utenti.
- **B.** Per convertire i file binari in file di testo.
- **C.** Per completare le scritture pendenti e scollegare correttamente il filesystem, riducendo il rischio di corruzione.
- **D.** Per trasformare il mount point in un dispositivo fisico.

### Scenario

Uno script deve contare i file regolari non nascosti presenti direttamente nella directory ricevuta. Questa esiste ed è accessibile; non contiene link simbolici e non cambia durante l'esecuzione. Bash usa le opzioni predefinite: i glob senza corrispondenze rimangono letterali, mentre `*` non include i nomi che iniziano con un punto.

I numeri di riga non fanno parte del codice.

```text
 1  #!/bin/bash
 2  dir="$1"
 3  count=0
 4
 5  for entry in "$dir"/*; do
 6    count=$((count + 1))
 7  done
 8
 9  printf '%s\n' "$count"
10  exit 0
```

La directory `campione` contiene soltanto il file regolare `a.txt` e la sottodirectory `archivio`.

### 2. Scenario — Scelta multipla

Che cosa stampa `./conta.sh campione`?

- **A.** `1`
- **B.** `2`
- **C.** `0`
- **D.** `3`, includendo automaticamente la directory corrente.

### 3. Scenario — Domanda aperta

Si propone di verificare lo script soltanto su directory che contengono file regolari non nascosti e nessun altro elemento. È una verifica sufficiente rispetto al requisito? Proponi un caso ulteriore diverso da campione, indicando risultato atteso ed effettivo. Rispondi in 2–3 frasi e spiega quale proprietà del glob è rilevante.

<details>
<summary>Mostra la soluzione dell'esercizio 11</summary>

### 1. Teoria — Scelta multipla: C

Lo smontaggio coordina il completamento delle operazioni sul filesystem prima della rimozione del dispositivo.

- **A errata:** non cancella i temporanei degli utenti.
- **B errata:** non modifica il formato dei file.
- **D errata:** un mount point resta una directory, non diventa hardware.

### 2. Scenario — Scelta multipla: B

Il glob produce due percorsi e il ciclo incrementa il conteggio senza distinguere file e directory.

- **A errata:** rappresenta il requisito, ma lo script non usa test -f.
- **C errata:** ci sono due corrispondenze e il ciclo le visita.
- **D errata:** `*` non aggiunge automaticamente `.`.

### 3. Scenario — Domanda aperta

No: una directory vuota richiede il risultato 0, ma lo script stampa 1. In assenza di corrispondenze, il glob rimane come parola letterale e il ciclo esegue comunque un'iterazione. Anche una directory contenente soltanto un file nascosto costituisce un controesempio valido con gli stessi risultati.

</details>

## Esercizio 12 — Statistiche per servizio

**Tempo indicativo: 7–9 minuti.**

### 1. Teoria — Scelta multipla

Qual è l'effetto dello sticky bit su una directory condivisa scrivibile da più utenti?

- **A.** Rende automaticamente eseguibili tutti i file creati al suo interno.
- **B.** Assegna a ogni nuovo file il proprietario root.
- **C.** Consente soltanto al proprietario della directory di leggere i file.
- **D.** Limita cancellazione e rinomina dei file ai soggetti autorizzati, come il proprietario del file, quello della directory e gli utenti privilegiati.

### Scenario

Uno script riceve una sequenza di eventi, ciascuno identificato dal servizio `web` oppure `db`. Non sono ammessi altri valori. Deve contare gli eventi separatamente per servizio e produrre due righe in un ordine prestabilito. Il numero di eventi è abbastanza piccolo da non causare overflow.

I numeri di riga non fanno parte del codice.

```text
 1  #!/bin/bash
 2  declare -A counts=([web]=0 [db]=0)
 3
 4  for service in "$@"; do
 5    old="${counts[$service]}"
 6    counts[$service]=$((old + 1))
 7  done
 8
 9  for service in web db; do
10    printf '%s=%s\n' "$service" "${counts[$service]}"
11  done
```

### 2. Scenario — Scelta multipla

Qual è l'output di `./eventi.sh web db web`?

- **A.** `web=2`, poi `db=1`.
- **B.** `web=1`, poi `db=1`.
- **C.** Le due righe hanno conteggi corretti ma ordine non determinabile.
- **D.** `web=3`, poi `db=3`.

### 3. Scenario — Riprogettazione

Aggiungi in fondo una riga `totale=N`, calcolando N **dai valori presenti nell'array**, non dai parametri posizionali. Non cambiare le due righe già prodotte e non dipendere dall'ordine di iterazione delle chiavi. Senza eventi il totale deve essere zero. Sono sufficienti poche righe e una frase.

<details>
<summary>Mostra la soluzione dell'esercizio 12</summary>

### 1. Teoria — Scelta multipla: D

Lo sticky bit introduce restrizioni alla rimozione e rinomina delle voci in una directory condivisa; non sostituisce i normali permessi di accesso.

- **A errata:** non imposta il bit di esecuzione sui file.
- **B errata:** non assegna root come proprietario dei nuovi file.
- **C errata:** non stabilisce da solo i permessi di lettura dei file.

### 2. Scenario — Scelta multipla: A

Ogni evento incrementa il proprio contatore. L'ordine delle stampe è imposto esplicitamente dalla lista web db, non dall'iterazione delle chiavi associative.

- **B errata:** il secondo evento web incrementa nuovamente il relativo contatore.
- **C errata:** non viene usato un attraversamento delle chiavi dell'array.
- **D errata:** i contatori non sono condivisi tra servizi.

### 3. Scenario — Riprogettazione

Dopo il ciclo finale, aggiungere:

```bash
total=0
for value in "${counts[@]}"; do
  total=$((total + value))
done
printf 'totale=%s\n' "$total"
```

La somma di tutti i valori non dipende dall'ordine delle chiavi. Senza eventi, entrambi i contatori mantengono il valore zero.

**Alternativa valida:** sommare esplicitamente `${counts[web]}` e `${counts[db]}`, dato l'insieme fisso di servizi ammessi.

</details>

## Esercizio 13 — Acquisizione di un elenco

**Tempo indicativo: 7–9 minuti.**

### 1. Teoria — Scelta multipla

Quale associazione tra opzione di `wc` e quantità misurata è corretta?

- **A.** `-c` conta sempre i caratteri Unicode e `-m` conta i byte.
- **B.** `-l` conta tutte le parole, indipendentemente dalle righe.
- **C.** `-c` conta i byte e `-m` conta i caratteri secondo la locale.
- **D.** `-l` e `-c` producono necessariamente lo stesso numero per i file di testo.

### Scenario

Uno script acquisisce l'output di una funzione in una variabile e lo presenta tra delimitatori. Il comando printf interpreta `\n` come newline. La funzione emette due nomi su righe distinte, seguiti da una riga vuota. Non ci sono errori di I/O.

I numeri di riga non fanno parte del codice.

```text
 1  #!/bin/bash
 2  produce() {
 3    printf 'alfa\nbeta\n\n'
 4  }
 5
 6  text=$(produce)
 7  printf '[%s]\n' "$text"
 8
 9  for word in $text; do
10    printf '<%s>\n' "$word"
11  done
```

Si assume IFS predefinito. Le parole alfa e beta non contengono metacaratteri.

### 2. Scenario — Scelta multipla

Quale output produce lo script?

**A.**
```text
[alfa beta]
<alfa>
<beta>
```

**B.**
```text
[alfa
beta]
<alfa>
<beta>
```

**C.**
```text
[alfa
beta

]
<alfa>
<beta>
```

**D.**
```text
[alfa
beta]
<alfa beta>
```

### 3. Scenario — Domanda aperta

La variabile text può essere considerata una copia byte per byte dell'output della funzione? Spiega quali newline vengono conservati e quali no. Aggiungere le virgolette all'assegnazione, scrivendo `text="$(produce)"`, cambierebbe questo aspetto? Rispondi in 2–3 frasi.

<details>
<summary>Mostra la soluzione dell'esercizio 13</summary>

### 1. Teoria — Scelta multipla: C

Byte e caratteri sono misure distinte; in una codifica multibyte un carattere può occupare più byte.

- **A errata:** inverte il significato delle opzioni.
- **B errata:** `-l` conta i newline, non le parole.
- **D errata:** il numero di righe non coincide in generale con la dimensione in byte.

### 2. Scenario — Scelta multipla: B

La sostituzione di comando elimina i newline finali ma conserva quello interno tra alfa e beta. La prima stampa preserva quel newline; il ciclo non quotato suddivide il contenuto in due parole.

- **A errata:** la stampa quotata non sostituisce il newline interno con uno spazio.
- **C errata:** i newline finali vengono rimossi dalla sostituzione di comando.
- **D errata:** nel ciclo l'espansione non è quotata e viene suddivisa secondo IFS.

### 3. Scenario — Domanda aperta

No: dei tre newline prodotti, quello tra alfa e beta è conservato mentre i due finali sono rimossi. Le virgolette nell'assegnazione non impediscono questa rimozione, propria della sostituzione di comando; nell'assegnazione semplice non avviene comunque word splitting del risultato.

</details>

## Esercizio 14 — Esito di un aggiornamento

**Tempo indicativo: 7–9 minuti.**

### 1. Teoria — Scelta multipla

Quale affermazione sui segnali è corretta?

- **A.** SIGTERM non può mai essere gestito da un programma.
- **B.** SIGKILL forza la terminazione e non permette al programma di gestire il segnale per eseguire operazioni di pulizia.
- **C.** SIGINT è un comando che elimina il file eseguibile.
- **D.** kill senza opzioni invia sempre SIGKILL.

### Scenario

Uno script usa due funzioni per rappresentare validazione e salvataggio. La validazione riesce soltanto se il primo argomento è `ok`. Il salvataggio, in questo esempio, stampa un messaggio e restituisce sempre il codice 1. Si riceve esattamente un argomento e tutte le stampe riescono.

I numeri di riga non fanno parte del codice.

```text
 1  #!/bin/bash
 2  valid() {
 3    [ "$1" = "ok" ]
 4  }
 5  save() {
 6    printf 'salvataggio fallito\n'
 7    return 1
 8  }
 9
10  valid "$1" && save || printf 'input non valido\n'
```

### 2. Scenario — Scelta multipla

Che cosa stampa `./aggiorna.sh ok`?

- **A.** Soltanto `salvataggio fallito`.
- **B.** Soltanto `input non valido`.
- **C.** Non stampa nulla, perché && e || si annullano.
- **D.** `salvataggio fallito`, poi `input non valido`.

### 3. Scenario — Domanda aperta

La riga 10 è equivalente a un if che chiama save quando valid riesce e stampa `input non valido` soltanto quando valid fallisce? Motiva la risposta facendo riferimento ai codici delle funzioni, senza riscrivere lo script. Sono sufficienti 2–3 frasi.

<details>
<summary>Mostra la soluzione dell'esercizio 14</summary>

### 1. Teoria — Scelta multipla: B

SIGKILL non può essere intercettato o ignorato dal processo destinatario.

- **A errata:** SIGTERM può essere gestito, ad esempio per una chiusura ordinata.
- **C errata:** SIGINT è un segnale, non un comando di rimozione dei file.
- **D errata:** il segnale normalmente predefinito è SIGTERM.

### 2. Scenario — Scelta multipla: D

valid restituisce 0 e viene eseguita save; questa stampa il proprio messaggio e restituisce 1, attivando anche il comando dopo `||`.

- **A errata:** ignora il fallimento di save e il successivo OR.
- **B errata:** ignora l'esecuzione di save dopo la validazione riuscita.
- **C errata:** gli operatori applicano le rispettive regole di esecuzione condizionale.

### 3. Scenario — Domanda aperta

Non è equivalente: il comando dopo `||` viene eseguito anche quando valid riesce ma save fallisce. Un if basato soltanto sull'esito di valid distinguerebbe la validità dell'input dal risultato del salvataggio; la catena li confonde e può produrre un messaggio fuorviante.

</details>

## Esercizio 15 — Lettura di una lista

**Tempo indicativo: 7–9 minuti.**

### 1. Teoria — Scelta multipla

Quale comando consulta la sezione 7 del manuale alla voce signal?

- **A.** `man signal 7`
- **B.** `signal --manual=7`
- **C.** `man 7 signal`
- **D.** `man -n 7 signal`

### Scenario

Uno script legge una lista da standard input. Una riga uguale a `STOP` termina l'elaborazione; tutte le altre righe, comprese quelle vuote, vengono contate. Ogni riga del file di ingresso termina con newline e l'I/O riesce. `IFS= read -r line` legge una riga preservandone spazi e backslash, senza includere il newline nella variabile; restituisce successo quando legge la riga completa.

I numeri di riga non fanno parte del codice.

```text
 1  #!/bin/bash
 2  count=0
 3
 4  while IFS= read -r line; do
 5    if [ "$line" = "STOP" ]; then
 6      break
 7    fi
 8    count=$((count + 1))
 9  done
10
11  printf '%s\n' "$count"
```

`break` termina il ciclo. Il file `lista.txt` contiene quattro righe, la seconda delle quali vuota:

```text
Anna

STOP
Luca
```

### 2. Scenario — Scelta multipla

Che cosa stampa `./lista.sh < lista.txt`?

- **A.** `1`
- **B.** `2`
- **C.** `3`
- **D.** `4`

### 3. Scenario — Domanda aperta

Un collega sostiene che una riga contenente ` STOP `, con uno spazio prima e uno dopo, termina il ciclo esattamente come `STOP`. Valuta la frase: se questa riga sostituisse la terza di lista.txt, quale conteggio si otterrebbe e perché? Rispondi in 2–3 frasi.

<details>
<summary>Mostra la soluzione dell'esercizio 15</summary>

### 1. Teoria — Scelta multipla: C

Il numero di sezione precede il nome della voce nella forma `man sezione nome`.

- **A errata:** non seleziona la sezione 7 con la sintassi richiesta; i nomi seguono il numero di sezione, non lo precedono.
- **B errata:** non è la sintassi del comando man.
- **D errata:** `-n` non è l'opzione per selezionare la sezione del manuale.

### 2. Scenario — Scelta multipla: B

Vengono contate Anna e la riga vuota. STOP termina il ciclo prima dell'incremento, e Luca non viene letto dal ciclo.

- **A errata:** una riga vuota completa viene letta con successo e viene contata.
- **C errata:** STOP non viene incluso nel conteggio.
- **D errata:** l'elaborazione non prosegue fino a Luca.

### 3. Scenario — Domanda aperta

La frase è falsa: con `IFS=` gli spazi iniziali e finali sono conservati e il confronto richiede uguaglianza esatta. La riga ` STOP ` non è il terminatore; viene contata insieme ad Anna, alla riga vuota e a Luca, per un totale di 4.

</details>

## Esercizio 16 — Risultato di una funzione

**Tempo indicativo: 7–9 minuti.**

### 1. Teoria — Scelta multipla

Si copia un file regolare con `cp originale copia`, creando un nuovo file su un normale filesystem Unix. Quale proprietà distingue questa operazione dalla creazione di un hard link?

- **A.** La copia ha un inode distinto; modificare il suo contenuto non modifica automaticamente quello dell'originale.
- **B.** I due nomi devono riferirsi allo stesso inode.
- **C.** La copia è necessariamente un link simbolico.
- **D.** La rimozione dell'originale rende necessariamente illeggibile la copia.

### Scenario

Una funzione calcola il doppio di un intero e stampa anche una segnalazione diagnostica. Il chiamante acquisisce il risultato con una sostituzione di comando, poi lo visualizza tra parentesi quadre. Lo script riceve esattamente un intero decimale non negativo, senza zeri iniziali, abbastanza piccolo da non causare overflow. Le stampe riescono.

I numeri di riga non fanno parte del codice.

```text
 1  #!/bin/bash
 2  double() {
 3    printf 'calcolo\n'
 4    printf '%s\n' "$(( $1 * 2 ))"
 5    return 0
 6  }
 7
 8  value=$(double "$1")
 9  printf '[%s]\n' "$value"
10  exit 0
```

### 2. Scenario — Scelta multipla

Quale output produce `./doppio.sh 6` su stdout?

**A.**
```text
calcolo
[12]
```

**B.**
```text
[12]
```

**C.**
```text
[0]
```

**D.**
```text
[calcolo
12]
```

### 3. Scenario — Riprogettazione

Stabilisci e applica un contratto per cui il risultato numerico della funzione sia acquisibile da value senza includere la diagnostica, mantenendo però visibile quest'ultima su stderr. Indica la sola riga da modificare e spiega il diverso ruolo di stdout e del codice di ritorno. Sono sufficienti una riga e 1–2 frasi.

<details>
<summary>Mostra la soluzione dell'esercizio 16</summary>

### 1. Teoria — Scelta multipla: A

Una normale copia crea un file distinto; un hard link aggiunge invece un nome allo stesso inode.

- **B errata:** è la proprietà dell'hard link, non della copia ordinaria.
- **C errata:** cp senza opzioni particolari non crea un link simbolico al file regolare.
- **D errata:** la copia conserva i propri dati anche dopo la rimozione dell'originale.

### 2. Scenario — Scelta multipla: D

La sostituzione di comando acquisisce entrambe le righe prodotte su stdout dalla funzione. Il newline interno è conservato e viene mostrato dalla stampa quotata.

- **A errata:** la diagnostica è acquisita insieme al risultato, non stampata separatamente dal chiamante.
- **B errata:** anche la riga calcolo è attualmente inviata su stdout.
- **C errata:** return 0 è un codice di esito, non il valore acquisito dalla sostituzione.

### 3. Scenario — Riprogettazione

Sostituire la riga 3 con:

```bash
printf 'calcolo\n' >&2
```

Il contratto riserva stdout al dato numerico e stderr alla diagnostica, che la sostituzione non acquisisce. Il codice di ritorno comunica il successo o fallimento dell'operazione, non il numero calcolato.

</details>

## Esercizio 17 — Confronto dei valori

**Tempo indicativo: 7–9 minuti.**

### 1. Teoria — Scelta multipla

Qual è il ruolo tipico di `/proc` in Linux?

- **A.** Contenere soltanto i programmi eseguibili installati dall'utente.
- **B.** Conservare le copie di backup delle password in chiaro.
- **C.** Ospitare la home di tutti gli utenti.
- **D.** Esporre informazioni su processi e kernel attraverso un filesystem virtuale.

### Scenario

Uno script riceve due rappresentazioni decimali di interi compresi tra 0 e 100, con eventuali zeri iniziali. Il requisito è stabilire se rappresentano lo stesso **valore numerico**. Gli input sono sempre validi e non contengono segni o spazi.

I numeri di riga non fanno parte del codice.

```text
 1  #!/bin/bash
 2  if [ "$#" -ne 2 ]; then
 3    printf 'servono due valori\n' >&2
 4    exit 1
 5  fi
 6
 7  if [ "$1" = "$2" ]; then
 8    printf 'uguali\n'
 9  else
10    printf 'diversi\n'
11  fi
```

### 2. Scenario — Scelta multipla

Che cosa stampa `./confronta.sh 7 7`?

- **A.** `diversi`
- **B.** `uguali`
- **C.** Un messaggio di errore perché `=` non è ammesso tra stringhe numeriche.
- **D.** `servono due valori`

### 3. Scenario — Domanda aperta

Questo caso basta a distinguere una corretta implementazione del requisito da un confronto testuale? Fornisci un controesempio negli input ammessi, indicando risultato richiesto e risultato effettivo dello script. Spiega quale tipo di confronto servirebbe, senza riscrivere il programma. Rispondi in 2–3 frasi.

<details>
<summary>Mostra la soluzione dell'esercizio 17</summary>

### 1. Teoria — Scelta multipla: D

/proc è un'interfaccia virtuale con cui Linux rende consultabili informazioni sul sistema e sui processi.

- **A errata:** non è una directory di installazione dei programmi utente.
- **B errata:** non è un archivio di password in chiaro.
- **C errata:** le home non vengono normalmente memorizzate in /proc.

### 2. Scenario — Scelta multipla: B

Le due stringhe sono identiche, quindi il confronto testuale riesce.

- **A errata:** i testi sono uguali.
- **C errata:** `=` è un operatore valido di confronto tra stringhe, anche quando contengono cifre.
- **D errata:** il numero di argomenti è esattamente due.

### 3. Scenario — Domanda aperta

No: con `07` e `7` il requisito richiede `uguali`, ma lo script stampa `diversi` perché i testi differiscono. Serve un confronto numerico, ad esempio `[ "$1" -eq "$2" ]`, che nel builtin test di Bash interpreta questi operandi come interi decimali. Sono valide anche altre coppie con lo stesso valore e diversa quantità di zeri iniziali.

</details>

## Esercizio 18 — Accesso a una directory

**Tempo indicativo: 7–9 minuti.**

### 1. Teoria — Scelta multipla

Qual è l'effetto principale di SGID su una directory condivisa?

- **A.** Tutti i programmi al suo interno vengono eseguiti come root.
- **B.** I nuovi file creati al suo interno ereditano il gruppo della directory.
- **C.** I nuovi file diventano automaticamente leggibili da tutti.
- **D.** Solo il proprietario di un file può cancellarlo, indipendentemente dagli altri permessi.

### Scenario

Uno script verifica se una directory è attraversabile dall'utente che lo esegue. Non deve verificare la possibilità di elencarne il contenuto. Si riceve esattamente un percorso; non si opera come root e non intervengono ACL né privilegi speciali. Le directory lungo il percorso sono accessibili e non ci sono modifiche concorrenti.

I numeri di riga non fanno parte del codice.

```text
 1  #!/bin/bash
 2  usable() {
 3    [ -d "$1" ] && [ -x "$1" ]
 4  }
 5
 6  if usable "$1"; then
 7    printf 'attraversabile\n'
 8  else
 9    printf 'non attraversabile\n'
10  fi
```

La directory `riservata` appartiene all'utente corrente e ha permessi `0100`.

### 2. Scenario — Scelta multipla

Che cosa stampa `./accesso.sh riservata`?

- **A.** `non attraversabile`, perché manca r.
- **B.** `non attraversabile`, perché manca w.
- **C.** `attraversabile`, perché è una directory e l'utente ha x.
- **D.** Nessun messaggio, perché una funzione non può essere usata come condizione.

### 3. Scenario — Domanda aperta

L'esito positivo di usable garantisce che l'utente possa elencare i nomi contenuti nella directory? Valuta la garanzia riferendoti al contratto della funzione e ai permessi r e x, distinguendo un requisito aggiuntivo da un errore dello script. Rispondi in 2–3 frasi.

<details>
<summary>Mostra la soluzione dell'esercizio 18</summary>

### 1. Teoria — Scelta multipla: B

SGID sulle directory facilita la collaborazione facendo ereditare ai nuovi file il gruppo della directory.

- **A errata:** non equivale a SUID root sui programmi.
- **C errata:** il bit non assegna da solo i permessi di lettura per tutti.
- **D errata:** richiama il ruolo dello sticky bit, non quello di SGID.

### 2. Scenario — Scelta multipla: C

La directory esiste e il proprietario ha il bit x, necessario all'attraversamento. La funzione restituisce il codice della catena di test.

- **A errata:** r riguarda l'elenco dei nomi, non l'attraversamento.
- **B errata:** w non è richiesto per il solo attraversamento.
- **D errata:** if può valutare il codice di ritorno di una funzione.

### 3. Scenario — Domanda aperta

No: r consente di leggere l'elenco dei nomi, mentre x consente l'attraversamento e l'accesso alle voci note, soggetto anche ai loro permessi. La directory data non ha r, ma soddisfa il contratto dichiarato. Richiedere anche l'elenco introdurrebbe un requisito aggiuntivo, da verificare con un test di lettura.

</details>

## Esercizio 19 — Percentuale dei risultati

**Tempo indicativo: 7–9 minuti.**

### 1. Teoria — Scelta multipla

Quale affermazione descrive correttamente la memoria virtuale nei sistemi Unix moderni?

- **A.** Ogni processo dispone di uno spazio di indirizzamento virtuale; il sistema gestisce la relazione con la memoria fisica, principalmente tramite paginazione.
- **B.** Tutti i processi devono utilizzare gli stessi indirizzi fisici senza isolamento.
- **C.** La memoria virtuale elimina la necessità di avere RAM.
- **D.** La memoria virtuale è soltanto lo spazio occupato dai file nella home.

### Scenario

Uno script riceve una sequenza di risultati: `1` indica un successo e `0` un insuccesso. Deve stampare la percentuale intera di successi, scartando la parte frazionaria; se la sequenza è vuota, stampa `nessun dato`. Sono ammessi soltanto 0 e 1 e il numero di argomenti è abbastanza piccolo da evitare overflow anche moltiplicando per 100.

I numeri di riga non fanno parte del codice.

```text
 1  #!/bin/bash
 2  total=$#
 3  passed=0
 4  for result in "$@"; do
 5    passed=$((passed + result))
 6  done
 7  if [ "$total" -eq 0 ]; then
 8    printf 'nessun dato\n'
 9    exit 0
10  fi
11  percent=$((passed / total * 100))
12  printf '%s%%\n' "$percent"
```

Nel formato di printf, `%%` produce un carattere `%` letterale.

### 2. Scenario — Scelta multipla

Che cosa stampa `./percentuale.sh 1 0 1`?

- **A.** `66%`
- **B.** `67%`
- **C.** `0%`
- **D.** Un errore di divisione per zero.

### 3. Scenario — Riprogettazione

Il formato richiesto diventa `successi=K/T percentuale=P%`, mantenendo il messaggio `nessun dato` per la sequenza vuota. P deve essere la percentuale matematica troncata all'intero, senza usare programmi esterni né numeri in virgola mobile.

Sostituisci soltanto le righe 11–12 e spiega l'ordine delle operazioni. Sono sufficienti due righe e 1–2 frasi.

<details>
<summary>Mostra la soluzione dell'esercizio 19</summary>

### 1. Teoria — Scelta multipla: A

Lo spazio virtuale è distinto dalla memoria fisica; il sistema ne gestisce la mappatura e la protezione.

- **B errata:** ignora separazione e protezione degli spazi di indirizzamento.
- **C errata:** la RAM rimane necessaria per eseguire il sistema.
- **D errata:** confonde memoria virtuale e spazio di archiviazione dei file utente.

### 2. Scenario — Scelta multipla: C

passed vale 2 e total vale 3. La divisione intera viene eseguita prima della moltiplicazione: 2 / 3 produce 0, poi 0 * 100 rimane 0.

- **A errata:** è il valore richiesto, non quello prodotto dall'espressione presente.
- **B errata:** non viene effettuato un arrotondamento all'intero più vicino.
- **D errata:** total vale 3 ed è inoltre controllato prima della divisione.

### 3. Scenario — Riprogettazione

Sostituire le righe 11–12 con:

```bash
percent=$((passed * 100 / total))
printf 'successi=%s/%s percentuale=%s%%\n' "$passed" "$total" "$percent"
```

La moltiplicazione precede la divisione, evitando di perdere prematuramente la parte frazionaria del rapporto. Per numeri non negativi la divisione intera finale realizza il troncamento richiesto; il caso vuoto continua a essere gestito prima di queste righe.

</details>

## Esercizio 20 — Ricerca di una segnalazione

**Tempo indicativo: 7–9 minuti.**

### 1. Teoria — Scelta multipla

Qual è la differenza principale tra ps e top nell'uso descritto dal corso?

- **A.** ps modifica le priorità dei processi, mentre top le password.
- **B.** ps mostra soltanto file ordinari e top soltanto directory.
- **C.** ps può essere eseguito esclusivamente da root, top da qualsiasi utente.
- **D.** ps mostra un'istantanea dei processi selezionati; top aggiorna periodicamente una vista dei processi e delle risorse.

### Scenario

Uno script cerca la stringa letterale `ERROR` nel file ricevuto. Deve distinguere una corrispondenza, l'assenza di corrispondenze e un errore di lettura. Riceve esattamente un percorso che non inizia con `-`; i file non cambiano durante l'esecuzione e le stampe riescono.

Si usa GNU grep senza altre opzioni: con `-F` cerca una stringa letterale, restituisce 0 se trova almeno una riga, 1 se non trova corrispondenze e 2 in caso di errore. Stdout di grep viene scartato; gli eventuali errori rimangono su stderr.

I numeri di riga non fanno parte del codice.

```text
 1  #!/bin/bash
 2  grep -F -- 'ERROR' "$1" > /dev/null
 3  status=$?
 4  case "$status" in
 5    0) printf 'trovato\n' ;;
 6    1) printf 'assente\n' ;;
 7    *) printf 'lettura fallita\n' >&2
 8       exit 2 ;;
 9  esac
10  exit 0
```

`pulito.log` è un file leggibile contenente soltanto la riga `INFO avvio`, terminata da newline.

### 2. Scenario — Scelta multipla

Quali sono stdout e codice di uscita di `./cerca.sh pulito.log`?

- **A.** Stdout: `assente`; codice: 0.
- **B.** Stdout: `assente`; codice: 1.
- **C.** Stdout vuoto; codice: 2.
- **D.** Stdout: `trovato`; codice: 0.

### 3. Scenario — Domanda aperta

Un collega propone di eliminare la variabile status e usare soltanto `if grep ...; then ...; else ...; fi`, stampando `assente` nel ramo else e terminando sempre con 0. Preserva la distinzione richiesta? Indica un caso in cui le due versioni si comportano diversamente, specificando messaggi dello script e codice di uscita, senza dover riprodurre il testo diagnostico di grep. Rispondi in 2–3 frasi.

<details>
<summary>Mostra la soluzione dell'esercizio 20</summary>

### 1. Teoria — Scelta multipla: D

ps produce una vista statica, mentre top fornisce una vista interattiva aggiornata nel tempo.

- **A errata:** non descrive la funzione principale di nessuno dei due strumenti.
- **B errata:** entrambi riguardano i processi, non l'elenco dei file.
- **C errata:** ps è normalmente utilizzabile anche da utenti non privilegiati, nei limiti di visibilità del sistema.

### 2. Scenario — Scelta multipla: A

grep restituisce 1, il case stampa assente e lo script termina con il proprio `exit 0`. Il contratto considera l'assenza un risultato regolare della ricerca.

- **B errata:** il codice di grep viene letto ma non restituito automaticamente dallo script.
- **C errata:** l'assenza di corrispondenze non è un errore di lettura.
- **D errata:** la stringa ERROR non compare nel file.

### 3. Scenario — Domanda aperta

La proposta confonde tutti i codici diversi da zero. Per un percorso inesistente, lo script originale non scrive risultati su stdout, aggiunge `lettura fallita` su stderr e termina con 2; la versione proposta stampa invece `assente` su stdout e termina con 0. Entrambe possono inoltre mostrare la diagnostica di grep su stderr, ma solo la prima conserva la distinzione richiesta.

</details>
