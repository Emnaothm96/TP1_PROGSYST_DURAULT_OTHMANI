#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "function.h"

#define MAX_INPUT_SIZE 1024

void print_welcome_message() {
    const char *welcome_msg = "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n";
    const char *prompt_msg = "enseash % ";

    write(STDOUT_FILENO, welcome_msg, strlen(welcome_msg));

    write(STDOUT_FILENO, prompt_msg, strlen(prompt_msg));

    char input[MAX_INPUT_SIZE];
    ssize_t n = read(STDIN_FILENO, input, MAX_INPUT_SIZE - 1);

    // Nettoyer le buffer pour éviter les erreurs
    if (n > 0) {
        input[n] = '\0';
    }
}
