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


## Question 2 :

A)
une chaîne dynamique welcome est utilisée pour personnaliser le message affiché en fonction de l'entrée (input). on était forcé a utiliser la fonction sprintf  pour formater le message en insérant la valeur de input, qui correspond à ce que l'utilisateur a saisi. Le message formaté, tel que "vous avez écrit,input\n", est ensuite affiché à l'aide de print_write, une fonction utilitaire qui simplifie l'appel au bas niveau de write qu'on a crée dans shell.c
```c title="function.c"

char * welcome;
    sprintf(welcome,"vous avez écrit %s/n",input);
    print_write(welcome);
```
Dans function.c

B) La fonction execute_command est conçue pour exécuter une commande en créant un nouveau processus. Elle utilise fork pour dupliquer le processus actuel. Dans le processus enfant, execlp est utilisé pour exécuter la commande spécifiée. Si execlp échoue, un message d'erreur est affiché et le processus enfant se termine. Le processus parent utilise waitpid pour attendre la fin du processus enfant et vérifie si celui-ci s'est terminé normalement. Finalement, la fonction retourne le code de retour du processus enfant pour indiquer si la commande a réussi ou échoué, où un code de retour de 0 indique un succès et un code non nul indique un échec.On l'a bien sur ajouté dans le function.h

```c title="function.c"

int execute_command(char *command) {
    pid_t pid = fork();
    // Processus enfant
    if (pid <= 0) {
        if (pid < 0) {
            perror("Erreur lors du fork");
        } 
        else {
            execlp(command, command, NULL);
            perror("Erreur lors de l'exécution de la commande");
        }
        exit(EXIT_FAILURE);
    } 
    // Processus parent
    else {
        int status;
        waitpid(pid, &status, 0);
        if (!WIFEXITED(status)) {
            print_shell("La commande a échoué.\n");
        }
        return WEXITSTATUS(status); // Retourne 0 si succès, sinon le code d'erreur
    }
}

```
Dans function.c

C)D'aprés le sujet on peut utiliser une functioon REPL pour afficher le prompt_message, lire l'input de l'utilisateur, executer la commande et recommencer.Dans cette fonction REPL,on a  mis en place une boucle infinie pour gérer l’interaction continue entre le shell et l’utilisateur. À chaque itération, le prompt est affiché à l’aide de la fonction print_write, puis j’utilise read_shell pour lire la commande saisie par l’utilisateur et la stocker dans le tableau input. Ensuite, la commande est exécutée avec execute_command, qui retourne un code de sortie pour indiquer si l’exécution a réussi ou échoué. Si la commande échoue (retourne EXIT_FAILURE), un message d’erreur est affiché pour demander à l’utilisateur de réessayer. On la met dans le enseash.c et on modifie le main parce que la fonction print_welcome_message ne sert plus à grand chose.

```c title="enseash.c"

#define MAX_INPUT_SIZE 1024
char exit_command[] = "exit";
char prompt_message[] = "enseash % ";


int REPL(){
    while(1){
        char input[MAX_INPUT_SIZE];
        
        print_write(prompt_message);
        read_shell(input);

        int exit_code_cmd = execute_command(input);
        if(exit_code_cmd == EXIT_FAILURE){
            print_shell("La commande a échoué, réessayez\n");
        }
        
    }
}

int main(){
    char *welcome_msg = "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n";
    char tkt;
    sprintf(tkt,welcome_msg,exit_command);  
    print_write(tkt);   
    return REPL();
}

```
Dans enseash.c



