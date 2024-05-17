/*
(C) 2024 JAMES KUANG ZHONGCHUAN
38PROG Programming: Student Record System
v1.1-alpha 
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// struct for modules array
struct Module {
    char name[64];
    int credits;
};

// struct for student array.
struct Student {
    char name[64];
    int hasLastName;
    char lastName [32];
    int id;
    float gpa;
};

// declarations
void cmds(int pg);
int getPage();
void cmdsList();
void cmdsAdd();
int moduleExists(char name[]);

// global
struct Student students[128] = { 
        {.name = "Owein", .hasLastName = 1, .lastName = "BISMARK III", .id = 000001, .gpa = 3.9},
        {.name = "Bob", .hasLastName = 0, .id = 000002, .gpa = 2.0},
        {.name = "Owein", .hasLastName = 0, .id = 000003, .gpa = 2.94}
};
int noStudents = 3; // figure out how to automatically increment later.


int main() 
{
    // students array.
    char input[128] = "void";
    int page;

    printf("WELCOME TO THE STUDENT RECORD SYSTEM v1.1-alpha!");

    while (strcmp(input, "quit") != 0) {
        printf("\nPlease enter a command. Enter \"cmds\" for a list of commands; \"quit\" to exit.\n> ");
        scanf(" %s", input);

        if (strcmp(input, "quit") == 0 || strcmp(input, "close") == 0 || strcmp(input, "exit") == 0) {
            printf("Quitting!\n");
            printf("=================\n");
            return 0;
        }
        else if (strcmp(input, "cmds") == 0) {
            page = getPage();
            cmds(page);
        }
        else if (strcmp(input, "list") == 0) {
            cmdsList();
        }
        else if (strcmp(input, "add") == 0) {
            cmdsAdd();
        } 
        else {
            printf("Invalid Command.\n");
        }
    }    
} 

void cmds(int pg)
{
    if (pg >= 2) {
        printf("Maximum page is 1!");
        return 1;
    }
    printf("=================\n");
    printf("COMMAND LIST\n");
    printf("=================\n");
    if (pg == 1) {
        printf("quit - exits the program. (sudos: close, exit)\n");
        printf("cmds - lists all available commands.\n");
        printf("list - lists all students.\n");
        printf("add - add a new student/module.\n");
    }
    printf("=================\n");

}

int getPage()
{
    int page;
    printf("Please enter your desired page: ");
    scanf(" %d", &page);
    return page;
}

void cmdsList()
{
    int i = 0;
    printf("ID: NAME\n");
    while (i != noStudents) {
        if (students[i].hasLastName == 1) {
            printf("%d: %s, %s | cGPA: %.2f \n", students[i].id, students[i].lastName, students[i].name, students[i].gpa);
        } 
        else {
            printf("%d: %s | cGPA: %.2f \n", students[i].id, students[i].name, students[i].gpa);
        }
        i += 1;
    }
}

int moduleExists(char name[])
{
    int moduleExist = 1;
    if (name) {
        moduleExist = 1;
    }
    printf("module exists placeholder\n");
    return moduleExist;
}

void cmdsAdd()
{
    char selectAdd[2];
    printf("Select STUDENT [S] or MODULE [M]: ");
    scanf(" %s", selectAdd);

    if (strcmp(selectAdd, "S") == 0) {
        char firstName[64], lastName[64], moduleName[64];
        char lastNameState;
        float GPA = 0.00;
        int exitState = 0;

        printf("Enter the FIRST NAME: ");
        scanf(" %[^\n]s", firstName);
        printf("Does this student have a LAST NAME? [Y/N] ");
        scanf("  %c", &lastNameState);
        if (lastNameState == 'y' || lastNameState == 'Y') {
            printf("Enter the LAST NAME: ");
            scanf("  %s", lastName);
        }
        else if (lastNameState != 'n' || lastNameState == 'N') {
            printf("Your input is invalid. Please try again.");
            return 1;
        }
        printf("You will now be prompted to enter MODULE INFORMATION.\n");
        while (exitState != 1) {
            printf("Enter Module NAME: ");
            scanf("  %s", moduleName);                
            if (moduleExists(moduleName) == 1) {  
                char exitRequest;  
                printf("Enter the student's GPA: ");
                scanf("  %f", GPA);
                printf("You have added %s with GPA %.2f. \n", moduleName, GPA);
                printf("Do you have any other modules to add? [Y/N] ");
                scanf(" %c", &exitRequest);
                if (exitRequest = 'N') {
                    exitState = 1;
                }
            } else {
                printf("Module could not be found. Please try again.\n");
            }
        }
        
        /*
        while (user not exit) {
            prompt user for module name
            check if module exists in system
            if (not exist) {
                error out
            }
            prompt user for gpa
            ask user if they want to add another module
        }
        */
    } 
    else if (strcmp(selectAdd, "M") == 0) {
        /*
        prompt user for module name
        prompt user for module credit unit
        */
        printf("selected module\n"); //del
    }
    else {
        printf("Invalid input. Please try again.\n");
    }
}

