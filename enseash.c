#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "function.h"
#include "enseash.h"
#include "shell.h"

#define MAX_INPUT_SIZE 1024
char exit_command[] = "exit";
char prompt_message[] = "enseash % ";
char exit_message[]="bye bye\n";


int REPL(){
    while(1){
        char input[MAX_INPUT_SIZE];
        
        print_write(prompt_message);
        read_shell(input);

         if(strncmp(input,exit_command,strlen(input)) == 0 ){
            print_shell(exit_message);
            return EXIT_SUCCESS;
            }
            
        int exit_code_cmd = execute_command(input);
        if(exit_code_cmd == EXIT_FAILURE){
            print_write("La commande a échoué, réessayez\n");
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