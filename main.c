/*
(C) 2024 JAMES KUANG ZHONGCHUAN
38PROG Programming: Student Record System
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/* struct student // wow student details (figure out how to implement)
{
    char studentName[16];
    int id[8];
    float gpa;
}; */

void main(void) 
{
    char *students[] = { "owien", "hitler", "owein", NULL };
    int noStudents = 3; // figure out how to automatically increment later.
    char input[128] = "void";

    printf("WELCOME TO THE STUDENT RECORD SYSTEM v0.1");

    while (strcmp(input, "quit") != 0) {
        printf("\nPlease enter a command. Enter \"cmds\" for a list of commands; \"quit\" to exit.\n> ");
        scanf("%s", input);

        if (strcmp(input, "quit") == 0 || strcmp(input, "close") == 0 || strcmp(input, "exit") == 0)
        {
            printf("Quitting!\n");
            return 0;
        }
        else if (strcmp(input, "cmds") == 0)
        {
            printf("quit - exits the program. (sudos: close, exit)\n");
            printf("cmds - lists all available commands.\n");
            printf("list - lists all students in the record.\n");
        }
        else if (strcmp(input, "list") == 0)
        {
            int i = 0;
            int count = 1;
            while (i != noStudents) {
                printf("%d %s \n", count, students[i]);
                i += 1; count += 1;
            }
        }
        else
        {
            printf("ERROR: INVALID COMMAND.\n");
        }
    }    
} 