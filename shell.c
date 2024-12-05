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