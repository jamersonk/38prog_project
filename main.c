/*
(C) 2024 JAMES KUANG ZHONGCHUAN
38PROG Programming: Student Record System
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main() 
{
    char input[128] = "void";

    printf("WELCOME TO THE STUDENT RECORD SYSTEM v0.1");

    printf("\nPlease enter a command. Enter \"cmds\" for a list of commands; \"quit\" to exit.\n> ");
    scanf("%s", input);

    if (strcmp(input, "quit") == 0 || strcmp(input, "close") == 0 || strcmp(input, "exit") == 0)
    {
        printf("Quitting!\n\n");
         return 0;
    }
    else if (strcmp(input, "cmds") == 0)
    {
        int page = 0;
        printf("Please enter the desired page: ");
        scanf("%d", page);
        if (page > 1) {
            printf("Page exceeds maximum.");
            return 1;
        }
        else if (page == 1) {
            printf("quit - exits the program. (sudos: close, exit)\n");
            printf("cmds - lists all available commands.\n");
            printf("list - lists all students in the record.\n");
        }
    }
    else
    {
        printf("Invalid Command.\n");
        return 1;
    }   
} 

// functions will go here later
