# Learn Bash

## Software
* [VirtualBox](https://www.virtualbox.org/wiki/Downloads)
* [EndeavourOS](https://endeavouros.com/) 

[Guida installazione EndeavourOS](EndeavourOS%20Installation/README.md)

## Libri
* Garrels - Bash Guide for Beginners
* Ramey, Fox - Bash reference manual

## Video
* [YouTube Bash](https://www.youtube.com/watch?v=62-hJarauK4&list=PLhlcRDRHVUzR-5TKDC1VPMtyhEyyQ5uwy)

## Tutorial, Esercizi Online
* https://www.tutorialspoint.com/unix/
* https://explainshell.com/

## Materiale didattico
Una volta terminata l'installazione di EndeavourOS, aprire un terminale ed inserire i seguenti comandi. 

```
$ yay -Syyu
$ sh -c "$(curl -fsLS get.chezmoi.io)" -- init --apply nbicocchi
$ ./install_scripts/install_script.sh --zsh --base-cli --base-gui --aur
$ git clone https://github.com/nbicocchi/learn-bash.git
```

## Moduli
[M1] Introduzione a Unix
* Varianti e caratteristiche Unix 
* Fondamenti per l'utilizzo pratico
* Utenti e gruppi
* Filesystem
* Processi
* Comandi rilevanti

[M2] Bash Shell
* Utilizzo interattivo
* Ridirezione
* Combinazione di comandi
* Variabili
* Espansioni

[M3] Bash Scripting
* Scrittura ed esecuzione
* Costrutti condizionali
* Costrutti iterativi
* Funzioni
* Trattamento argomenti avanzato (getopts)
* Script multi-file
* Buone pratiche
