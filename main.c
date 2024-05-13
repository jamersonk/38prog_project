/*
(C) 2024 JAMES KUANG ZHONGCHUAN
38PROG Programming: Student Record System
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// struct for student array.
struct Student
{
    char name[64];
    int hasLastName;
    char lastName [32];
    int id;
    float gpa;
};

int main() 
{
    // student array.
    struct Student students[128] = { 
        {.name = "Owein", .hasLastName = 1, .lastName = "BISMARK III", .id = 1, .gpa = 3.9},
        {.name = "Bob", .hasLastName = 0, .id = 2, .gpa = 2.0},
        {.name = "Owein", .hasLastName = 0, .id = 3, .gpa = 2.94},
        NULL
    };

    int noStudents = 3; // figure out how to automatically increment later.
    char input[128] = "void";

    printf("WELCOME TO THE STUDENT RECORD SYSTEM v0.1");

    while (strcmp(input, "quit") != 0) {
        printf("\nPlease enter a command. Enter \"cmds\" for a list of commands; \"quit\" to exit.\n> ");
        scanf("%s", input);

        if (strcmp(input, "quit") == 0 || strcmp(input, "close") == 0 || strcmp(input, "exit") == 0)
        {
            printf("Quitting!\n\n");
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
            printf("ID: NAME\n");
            while (i != noStudents) {
                if (students[i].hasLastName == 1) {
                printf("%d: %s, %s | cGPA: %.2f \n", students[i].id, students[i].lastName, students[i].name, students[i].gpa);
                } else {
                    printf("%d: %s | cGPA: %.2f \n", students[i].id, students[i].name, students[i].gpa);
                }
                i += 1;
            }
        }
        else
        {
            printf("Invalid Command.\n");
            return 1;
        }
    }    
} 