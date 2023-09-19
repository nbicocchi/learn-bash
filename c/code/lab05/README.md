# Programmazione di Sistema - DIEF/UNIMORE

## Esercizi C (File ed integrazione con la shell)

Si propone un gruppo di esercizi per imparare ad utilizzare l'accesso ai file e l'integrazione del C con la shell. In
particolare, viene proposta una serie di implementazioni semplificate di famosi comandi shell.

--- 

Esercizio 1. Implementare una versione semplificata del comando *echo*

```shell
$ echo [string ...]
```

dove:

* **[string ...]** rappresenta un gruppo di stringhe;
* il comando visualizza a monitor le stringhe passate come argomenti.

---

Esercizio 2. Implementare una versione semplificata del comando *touch*

```shell
$ touch filename
```

dove:

* **filename** rappresenta un nome di file da creare (vuoto).

---

Esercizio 3. Implementare una versione semplificata del comando *size*

```shell
$ size filename
```

dove:

* **filename** rappresenta un nome di file di cui mostrare la dimensione in byte.

---

Esercizio 4. Implementare una versione semplificata del comando *cmp*

```shell
$ cmp filename_1 filename_2
```

dove:

* **filename_1, filename_2** rappresentano due nomi di file da confrontare;
* il comando informa l'utente se i 2 file sono uguali o diversi. Se sono diversi, indica byte e linea del primo
  carattere diverso.

---

Esercizio 5. Implementare una versione semplificata del comando *cp*

```shell
$ cp filename_1 filename_2
```

dove:

* **filename_1 filename_2** rappresentano sorgente e destinazione della copia;
* il comando copia il contenuto di filename_1 all'interno di filename_2.

---

Esercizio 6. Implementare una versione semplificata del comando *cat*

```shell
$ cat [filename ...]
```

dove:

* **[filename ...]** rappresenta un gruppo di percorsi a file. In caso filename non venga indicato, il comando legge da stdin;
* il comando visualizza il contenuto dei file passati come parametro.

---

Esercizio 7. Implementare una versione semplificata del comando *head*

```shell
$ head n [filename]
```

dove:

* **filename** rappresenta un nome di file di cui mostrare le prime **n** linee. In caso filename non venga indicato, il comando legge da stdin.

---

Esercizio 8. Implementare una versione semplificata del comando *tail*

```shell
$ tail n [filename]
```

dove:

* **filename** rappresenta un nome di file di cui mostrare le ultime **n** linee. In caso filename non venga indicato, il comando legge da stdin.

---

Esercizio 9. Implementare una versione semplificata del comando *wc*.

```shell
$ wc [filename]
```

dove:

* **filename** rappresenta un nome di file di cui mostrare su stdout sia il numero di bytes che di linee contenute. In caso filename non venga indicato, il comando legge da stdin.

---

Esercizio 10. Implementare una versione semplificata del comando *grep* (vedi funzione di libreria strstr())

```shell
$ grep string [filename]
```

dove:

* **filename** rappresenta un nome di file di cui mostrare tutte le linee che contengono string. In caso filename non venga indicato, il comando legge da stdin.
