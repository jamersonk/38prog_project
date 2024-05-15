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
    char input[128] = "void";

    printf("WELCOME TO THE STUDENT RECORD SYSTEM v0.1");

    printf("\nPlease enter a command. Enter \"cmds\" for a list of commands; \"quit\" to exit.\n> ");
    scanf("%s", input);
} 

// functions will go here later