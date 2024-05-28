/*
COPYRIGHT (C) 2024 JAMES KUANG ZHONGCHUAN

THIS WORK IS LICENSED UNDER THE GNU GENERAL PUBLIC LICENSE v3.0.
View the full license text here: https://www.gnu.org/licenses/gpl-3.0.en.html#license-text

38PROG Programming: Student Record System
v1.0 INDEV 
*/

// libraries
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

// prototypes
void cmds(int pg);
int getPage();
void cmdsList();
void cmdsAdd();
int moduleExists(char givenName[]);

// global variables
// modules array
struct Module modules[48] = {
    {.name = "ABCDEFGHIJKLMNOPQRSTUVWXYZ 1234567890"},
    {.name = "Module 1", .credits = 4},
    {.name = "Module 2", .credits = 1}
};

// students array
struct Student students[128] = { 
    {.name = "Owein", .hasLastName = 1, .lastName = "BISMARK III", .id = 000001, .gpa = 3.9},
    {.name = "Bob", .hasLastName = 0, .id = 000002, .gpa = 2.0},
    {.name = "Owien", .hasLastName = 0, .id = 000003, .gpa = 2.94}
};

int noStudents = 3;
int noModules = 1;

// BEGIN MAIN
int main()
{
    // students array.
    char input[128] = "void";
    int page;

    printf("WELCOME TO THE STUDENT RECORD SYSTEM!");

    while (strcmp(input, "quit") != 0) {
        printf("\nPlease enter a command. Enter \"cmds\" for a list of commands; \"quit\" to exit.\n> ");
        scanf(" %s", input);

        if (strcmp(input, "quit") == 0 || strcmp(input, "close") == 0 || strcmp(input, "exit") == 0) {
            printf("Quitting!\n");
            printf("=================\n");
            printf("THANK YOU FOR USING THE STUDENT RECORD SYSTEM.")
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
} // END MAIN

// functions
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

int moduleExists(char givenName[])
{
    int i = 0;
    int moduleExist = 0;
    while (i != noModules) {
        char* moduleName = modules[i].name;
        if (moduleName == givenName) {
            moduleExist = 1;
            printf("System: moduleExists returned TRUE");
            return moduleExist;
        }
    }
    printf("System: moduleExists returned FALSE")
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
        scanf(" %[^\n]s", firstName); // %[^\n]d allows for the acceptance of multi word inputs.
        printf("Does this student have a LAST NAME? [Y/N] ");
        scanf("  %c", &lastNameState);
        if (lastNameState == 'y' || lastNameState == 'Y') {
            printf("Enter the LAST NAME: ");
            scanf(" %[^\n]s", lastName);        
        }
        else if (lastNameState != 'n' || lastNameState == 'N') {
            printf("Your input is invalid. Please try again.");
            return 1;
        }
        printf("You will now be prompted to enter MODULE INFORMATION.\n");
        while (exitState != 1) {
            printf("Enter Module NAME: ");
        scanf(" %[^\n]s", moduleName);             
            if (moduleExists(moduleName) == 1) {  
                char exitRequest;  
                printf("Enter the student's GPA: ");
                scanf("  %f", GPA);
                printf("You have added %s with GPA %.2f. \n", moduleName, GPA);
                printf("Do you have any other modules to add? [Y/N] ");
                scanf(" %c", &exitRequest);
                if (exitRequest == 'N' || exitRequest == 'n') {
                    exitState = 1;
                }
            } else {
                printf("Module could not be found. Please try again.\n");
            }
        }
        // append to STUDENTS array.
    } 
    else if (strcmp(selectAdd, "M") == 0) {
        char moduleName;
        int credits;
        printf("Enter module NAME: ");
        scanf(" %[^\n]s", moduleName);
        printf("Enter no. of CREDITS: ");
        scanf("%d", credits);
        if (moduleExists == 1) {
            printf("ERROR: A module with that name already exists.");
        } else {
            // append to MODULES array
            printf("Created %s, with %d credits.", moduleName, credits);
        }
    }
    else {
        printf("Invalid input. Please try again.\n");
    }
}
