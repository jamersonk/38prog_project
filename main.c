/*
(C) 2024 JAMES KUANG ZHONGCHUAN
38PROG Programming: Student Record System
*/

#include <stdio.h>
#include <string.h>

int main() 
{
    char input[50];
    int cmdsPage = 1;

    printf("Waiting for command... \nRun \"cmds\" for a list of commands.\n");
    scanf("%s", input);    

    if (strcmp(input, "cmds") == 0) { // strcmp compares each character in the input string (an array), to those in the string (array) "char".
        printf("=============================\n");
        printf("LIST OF COMMANDS [Pg %d/1]\n", cmdsPage);
        printf("=============================\n");
        printf("./main - Initialises the main.c program.\n");
        printf("cmds - Provides a list of commands.\n");
        printf("list - Prints a list of students. Usage: list <page>\n");
        printf("=============================\n");
        printf("Run cmds <page> to view other pages.\n");
        printf("=============================\n");
    }
    else printf("%s", input);
}