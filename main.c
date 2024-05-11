/*
(C) 2024 JAMES KUANG ZHONGCHUAN
38PROG Programming: Student Record System
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void main(void) 
{
    char *students[] = { "owien, hitler, owein" };
    char input[128] = "void";

    while (strcmp(input, "quit") != 0) {
        printf("\nPlease enter a command. \"cmds\" for a list of commands. \"quit\" to exit the program.\n> ");
        scanf("%s", input);

        if (strcmp(input, "quit") == 0)
        {
            printf("Quitting!\n");
            return 0;
        }
        else if (strcmp(input, "cmds") == 0)
        {
            printf("Placeholder\n");
        }
        else
        {
            printf("ERROR: INVALID COMMAND.\n");
        }
    }    
} 