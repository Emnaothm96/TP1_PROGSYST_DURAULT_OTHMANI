#include <unistd.h>
#include <string.h>
#include "enseash.h"

void print_message(const char *message) {
    write(STDOUT_FILENO, message, strlen(message));
}

ssize_t read_input(char *buffer, size_t size) {
    return read(STDIN_FILENO, buffer, size);
}

int main() {
    char buffer[BUFFER_SIZE];

    print_message("Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n");

    while (1) {
        print_message("enseash % ");

        ssize_t n = read_input(buffer, sizeof(buffer) - 1);
        if (n <= 0) break;

        buffer[n - 1] = '\0';
        if (strcmp(buffer, "exit") == 0) break;
    }

    print_message("Bye bye...\n");
    return 0;
}
