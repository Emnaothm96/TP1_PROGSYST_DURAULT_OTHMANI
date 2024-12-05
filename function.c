#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "function.h"
#include "shell.h"
#include "stdio.h"
#include <fcntl.h>
#define MAX_INPUT_SIZE 1024

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


void print_welcome_message() {
    char *welcome_msg = "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n";
    char *prompt_msg = "enseash % ";
    char input[MAX_INPUT_SIZE];
    //on utilise la function dans shell
    print_write(welcome_msg);
    print_write(prompt_msg);
    read_shell(input);
    char * welcome;
    sprintf(welcome,"vous avez écrit %s/n",input);
    print_write(welcome);
    execute_command(input);
}
