#include <stdio.h>
#include <unistd.h>
#ifndef ENSEASH_H
#define ENSEASH_H

#define BUFFER_SIZE 128

void print_message(const char *message);

ssize_t read_input(char *buffer, size_t size);

#endif // ENSEASH_H
