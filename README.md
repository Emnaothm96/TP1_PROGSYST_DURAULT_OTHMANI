# TP1_PROGSYST_DURAULT_OTHMANI

## Question 1 :

voici le code de la question. 
on fait 4 répertoires : 

utils.c:

Ce code simplifie l'utilisation des appels bas niveau write et read en définissant deux fonctions utilitaires : print_write et read_shell. La fonction print_write encapsule write pour afficher des messages sur la sortie standard (console), prenant une chaîne en argument et calculant sa taille avec strlen. Cela facilite l'affichage des messages sans répéter le même appel dans tout le programme. La fonction read_shell, quant à elle, encapsule read pour lire l'entrée utilisateur depuis la console, stockant les données dans un buffer et limitant leur taille à une constante définie (MAX_INPUT_SIZE). Ces deux fonctions améliorent la lisibilité et la maintenance du code en centralisant les interactions avec la console, tout en rendant le shell plus modulaire et structuré.

```c title="shell.c"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "function.h"

#define MAX_INPUT_SIZE 1024 

ssize_t print_write(char *message){
    return write(STDOUT_FILENO, message, strlen(message));
}

ssize_t read_shell(char *input){
    ssize_t input_size = read(STDIN_FILENO,input,MAX_INPUT_SIZE);
    return input_size;
} 
```
*utils.c*

```c title="shell.h"

#include <unistd.h>

ssize_t read_shell(char *input);
ssize_t print_write(char *message); 
```
*utils.h*

enseash.c:

Ce programme implémente un shell simplifié nommé ENSEA Shell (enseash). Le fichier main.c contient le point d'entrée du programme avec un appel à la fonction print_welcome_message, définie dans un autre fichier (probablement functions.c). Cette fonction est responsable d'afficher un message de bienvenue : "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n", suivi d'un prompt personnalisé : "enseash % ", pour inviter l'utilisateur à saisir une commande. Le programme est structuré de manière modulaire, séparant la logique principale (dans main.c) des fonctionnalités spécifiques (dans functions.c qu'on vas expliquer juste aprés), ce qui facilite la maintenance et les futures extensions.
```c title="enseash.c"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "function.h"
#include "enseash.h"

int main(){
    print_welcome_message();        
}
```
*enseash.c*


```c title="enseash.h"

void print_welcome_message();

```
*enseash.h*


function.c:

Ce code implémente une fonction print_welcome_message qui gère l'affichage du message d'accueil et du prompt dans un shell simplifié. La fonction utilise deux chaînes constantes, welcome_msg et prompt_msg, pour stocker respectivement le message de bienvenue ("Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n") et le prompt interactif ("enseash % "). Ces messages sont affichés à l'aide de la fonction print_shell, probablement définie dans un autre fichier (comme utils.c), qui encapsule les appels bas niveau pour écrire sur la sortie standard (write).

```c title="function.c"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "function.h"

#define MAX_INPUT_SIZE 1024

void print_welcome_message() {
    const char *welcome_msg = "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n";
    const char *prompt_msg = "enseash % ";
    char input[MAX_INPUT_SIZE];
    //on utilise la function dans utils
    print_shell(welcome_msg);
    print_shell(prompt_msg);
    read_shell(input,MAX_INPUT_SIZE);
}
```
*function.c*

```c title="function.h"
void print_welcome_message();
```
function.h