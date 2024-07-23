/*
    Copyright (C) 2024  JAMES KUANG ZHONGCHUAN
    v1.0 
*/

// LIBRARIES
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

//CONSTANTS
#define MAX_STUDENTS 64
#define MAX_MODULES 16
#define MAX_STUDENTS 64
#define MAX_MODULES 16

// STRUCTS
typedef struct {
    char name[64];
    int credits;
} Module; // defines "module" struct datatype.

typedef struct {
    char name[64];
    int hasLastName;
    char lastName [32];
    int id, credits;
    float gpa;
} Student; // defines "student" struct datatype.

// PROTOTYPES
void PrintBars(); //prints a seperator
int check(int input);
void cmds(); // prints out commands.
float gpaCalculator(float gpa, int credits); // calculates student current gpa and returns value.
void cmdsList(); // list all students
void cmdsAdd(); // add a new student/module
int moduleExists(char givenName[]); // checks if the module name already exists
void addStudent(Student *students, int); // adding new student
void addModule(Module *students, int); // adding new module
void cmdsDel(Student *students); // delete student
void cmdsEdit(Student *students); // edit student
void editFirstName(Student *students, int pos); // edit first name for student
void editLastName(Student *students, int pos); // edit last name for student
void editGPA(Student *students, int pos); // edit GPA for student
void cmdsView(Student *); // view detailed info about student

// GLOBAL VARIABLES
Module modules[MAX_MODULES] = {
}; // DELETE ALL ELEMENTS BEFORE SUBMISSION

Student students[MAX_STUDENTS] = { 
}; // DELETE ALL ELEMENTS BEFORE SUBMISSION

int studentsAllocated = 0; // SET TO 0.
int modulesAllocated = 0; // SET TO 0.

// BEGIN MAIN
int main()
{
    char input[128] = "void";
    int i = 0, j = 0;

    // opening files & validating that they've been opened.
    FILE *modulesList, *studentsList, *numStudents, *numModules;

    printf("Loading...\n");

    modulesList = fopen("modules.txt", "rb");
    if (modulesList == NULL)
    {
        modulesList = fopen("modules.txt", "wb+");
        if (modulesList == NULL)
        {
            printf("Error: Unable to create modules.txt\n");
            return EXIT_FAILURE;
            return EXIT_FAILURE;
        }
    }
    studentsList = fopen("students.txt", "rb");
    if (studentsList == NULL)
    {
        studentsList = fopen("students.txt", "wb+");
        if (studentsList == NULL)
        {
            printf("Error: Unable to create students.txt\n");
            return EXIT_FAILURE;
            return EXIT_FAILURE;
        }
    }
    numStudents = fopen("numStudents.txt", "r+");
    if (numStudents == NULL)
    {
        numStudents = fopen("numStudents.txt","w+");
        if (numStudents == NULL)
        {
            printf("Error: Unable to create numStudents.txt\n");
            return EXIT_FAILURE;
            return EXIT_FAILURE;
        }
    }


    numModules = fopen("numModules.txt", "r+");
    if (numModules == NULL)
    {
        numModules = fopen("numModules.txt", "w+");
        if (numModules == NULL)
        {
            printf("Error: Unable to create numModules.txt\n");
            return EXIT_FAILURE;
            return EXIT_FAILURE;
        }
    }

    fread(&studentsAllocated, sizeof(int), 1, numStudents);
    fread(&modulesAllocated, sizeof(int), 1, numModules);
    while (i < modulesAllocated)
    {
        fread(&modules[i], sizeof(Module), 1, modulesList);
        i++;
    }
    }
    while (j < studentsAllocated)
    {
        fread(&students[j], sizeof(Student), 1, studentsList);
        j++;
    }
    fclose(modulesList);
    fclose(studentsList);
    fclose(numStudents);
    fclose(numModules);

    // begining actual program
    system("cls");
    while (strcmp(input, "quit") != 0) 
    {
        printf("Enter a command. \"cmds\" for a list of commands; \"quit\" to exit.\n> ");
        scanf("  %s", input);

        // input processing
        if (strcmp(input, "cmds") == 0) 
        {
            cmds();
        }
        else if (strcmp(input, "list") == 0) 
        {
            cmdsList();
        }
        else if (strcmp(input, "add") == 0) 
        {
            cmdsAdd();
        } 
        else if (strcmp(input, "del") == 0) 
        {
            cmdsDel(students);
        }
        else if (strcmp(input, "edit") == 0) 
        {
            cmdsEdit(students);
        }
        else if (strcmp(input, "view") == 0) 
        {
            cmdsView(students);
        }
        else if (strcmp(input, "clear") == 0)
        {
            system("cls");
        }
        else if (strcmp(input, "quit") != 0)
        {
            printf("Invalid command. Type \"cmds\" for a list of commands.\n");
        }
    }
    numStudents = fopen("numStudents.txt", "wb");
    fwrite(&studentsAllocated, sizeof(int), 1, numStudents);

    numModules = fopen("numModules.txt", "wb");
    fwrite(&modulesAllocated, sizeof(int), 1, numModules);

    modulesList = fopen("modules.txt", "wb");
    fwrite(&modules, sizeof(Module), modulesAllocated, modulesList);

    studentsList = fopen("students.txt", "wb");
    fwrite(&students, sizeof(Student), studentsAllocated, studentsList);
    
    // close all files.
    fclose(numStudents);
    fclose(numModules);
    fclose(modulesList);
    fclose(studentsList);
} 
// END MAIN

// FUNCTIONS
void PrintBars()
{
    printf("-----------------------------------------------------------------------------\n");
}

int check(int input) // some data validation
{
    if (studentsAllocated == MAX_STUDENTS) // prevents adding more students than total allowed
    {
        printf("ERROR: Reached maximum number of students.\n");
        return 1;
    }
    else if (studentsAllocated == 0) // prevents editing/deleting when students are 0.
    {
        printf("ERROR: Unable to proceed as there are no students.\n");
        return 1;
    }
    else if (input > studentsAllocated || input <= 0) // checks that the ID is valid.
    {
        printf("ERROR: ID entered is invalid.\n");
        return 1;
    }
    return 0;
}

void cmds()
{
    PrintBars();
    printf("AVAILABLE COMMANDS (page 1 of 1)\n");
    PrintBars();
    printf("quit - exits the program.\n");
    printf("cmds - lists all available commands.\n");
    printf("list - lists all students.\n");
    printf("add - add a new student/module.\n");
    printf("del - delete a student.\n");
    printf("edit - edit a student.\n");
    printf("view - view a student in detail.\n");
    printf("clear - clears the termnal.\n");
    PrintBars();
}

float gpaCalculator(float gpa, int credits)
{
    float weightedGPA = gpa * (float)credits;
    return weightedGPA;
}

void cmdsList()
{
    int i = 0;
    printf("ID: NAME\n");
    if (studentsAllocated == 0) 
    {
        printf("No students have been added. There's nothing to list!\n");
        return;
    }

    while (i != studentsAllocated) 
    {
        if (students[i].hasLastName == 1) 
        {
            printf("%d: %s, %s | cGPA: %.2f \n", students[i].id, students[i].lastName, students[i].name, students[i].gpa);
        } 
        else 
        {
            printf("%d: %s | cGPA: %.2f \n", students[i].id, students[i].name, students[i].gpa);
        }
        i += 1;
    }
}

int moduleExists(char givenName[])
{
    int i = 0;
    int moduleExist = 0;
    while (i != modulesAllocated) 
    {
        char* moduleName = modules[i].name;
        if (strcmp(moduleName, givenName) == 0) 
        {
            moduleExist = i;
            return moduleExist;
        }
        i += 1;
    }
    moduleExist = -1;
    return moduleExist;
}

void cmdsAdd()
{
    char selectAdd = 'p';
    printf("Select STUDENT [S] or MODULE [M]: ");
    scanf(" %c", &selectAdd);

    if (selectAdd == 'S') 
    {
        addStudent(students, studentsAllocated);
    } 
    else if (selectAdd == 'M') 
    {
        addModule(modules, modulesAllocated);
    } 
}

void addStudent(Student *students, int num) 
{
    students[num].id = num + 1;
    char moduleName[64], lastNameState = 'p';
    float GPA = 0.00, tGPA = 0.00, cGPA = 0.00, wGPA = 0.00; // GPA is for each new module; cGPA is total GPA; wGPA is weighted GPA for each new module.
    int exitState = 0, credits, tCredits = 0, pos = 0; // creduts is for each new module; tCredits is for total credits.

    students[num].id = num + 1;
    char moduleName[64], lastNameState = 'p';
    float GPA = 0.00, tGPA = 0.00, cGPA = 0.00, wGPA = 0.00; // GPA is for each new module; cGPA is total GPA; wGPA is weighted GPA for each new module.
    int exitState = 0, credits, tCredits = 0, pos = 0; // creduts is for each new module; tCredits is for total credits.

    if (studentsAllocated > MAX_STUDENTS)
    {
        printf("ERROR: Reached maximum number of students allowed.\n");
        printf("ERROR: Reached maximum number of students allowed.\n");
        return;
    }
    else if (modulesAllocated == 0)
    {
        printf("ERROR: No modules have been added. Add a module to proceed.\n");
        return;
    }

    printf("Enter the FIRST NAME: ");
    scanf(" %[^\n]s", students[num].name); // %[^\n]d allows for the acceptance of multi word inputs.
    printf("Does this student have a LAST NAME? [Y/N] ");
    scanf(" %c", &lastNameState);

    // to check if user wants to include a last name.
    if (lastNameState == 'y') 
    {
        printf("Enter the LAST NAME: ");
        scanf(" %[^\n]s", students[num].lastName);        
        students[num].hasLastName = 1;
    }

    // for calculating student gpa
    printf("You will now be prompted to enter MODULE INFORMATION.\n");
    while (exitState != 1) 
    {
        printf("Enter Module NAME: [Enter \"exit\" to exit. (case sensitive)] ");
        scanf(" %[^\n]s", moduleName); 
        if (strcmp(moduleName, "exit") == 0)
        {
            return;
        }            
        else if (moduleExists(moduleName) >= 0) 
        else if (moduleExists(moduleName) >= 0) 
        {  
            char exitRequest; // to detect user exit request.
            // User Input
            
            
            printf("Enter the student's GPA: ");
            scanf("  %f", &GPA);

            // GPA Calculation
            pos = moduleExists(moduleName);
            wGPA = gpaCalculator(GPA, modules[pos].credits);

            printf("You have added %s with GPA %.2f. \n", moduleName, GPA);
            credits = modules[pos].credits;
            tCredits += credits;
            tGPA += wGPA;

            // input for user exit
            printf("Would you like to add another module? [Y/N] ");
            scanf(" %c", &exitRequest);
            // check for user exit
            if (exitRequest == 'N' || exitRequest == 'n') // to check for user exit input.
            { 
                exitState = 1;
            }
        } 
        else 
        {
            // if user adds in a module that dosen't exist.
            printf("Module could not be found. Please try again.\n");
        }
    }
    studentsAllocated++;
    cGPA += tGPA / tCredits;
    students[num].gpa = cGPA;
    return;
}

void addModule(Module *modules, int num)
{
    char moduleName[64];
    int credits = 0;

    if (modulesAllocated >= MAX_MODULES)
    {
        printf("ERROR: Reached maximum number of modules allowed.\n");
        return;
    }

    if (modulesAllocated >= MAX_MODULES)
    {
        printf("ERROR: Reached maximum number of modules allowed.\n");
        return;
    }

    printf("Enter module NAME: ");
    scanf(" %[^\n]s", moduleName);
    printf("Enter no. of CREDITS: ");
    scanf("%d", &credits);

    if (moduleExists(moduleName) == 0) 
    {
        printf("ERROR: A module with that name already exists.\n");
        return;
    } 
    else 
    {
        // appending newModule to modules array.
        strcpy(modules[num].name, moduleName);
        modules[num].credits = credits;
        printf("Created %s, with %d credits.", moduleName, credits);
        modulesAllocated++;
    }
}

void cmdsDel(Student *students)
{
    if (studentsAllocated == 0)
    {
        printf("ERROR: No students to delete.\n");
        return;
    }// checks that students actually exist.
    int id = 0, pos = 0, i = 0, j = 0;
    char state;
    printf("Enter ID of Student you want to delete: ");
    scanf(" %d", &id);
    pos = id - 1;

    if (check(id) == 1)
    {
        return;
    }

    printf("Please confirm you want to DELETE the below student [y/n]\n");
    printf("%s %s | ID: %d\n", students[pos].name, students[pos].lastName, students[pos].id);
    printf("> ");
    scanf(" %c", &state);

    if (state == 'y') 
    {
        while (i < studentsAllocated) 
        {
            if (students[i].id == id) 
            {
                j = i;
                while (j < studentsAllocated) 
                {
                    strcpy(students[j].name, students[j + 1].name);
                    strcpy(students[j].lastName, students[j + 1].lastName);
                    students[j].gpa = students[j + 1].gpa;
                    students[j].credits = students[j + 1].credits;
                    students[j].hasLastName = students[j + 1].hasLastName;
                    j++;
                }
                studentsAllocated = studentsAllocated - 1;
                break;
            }
            i += 1;
        }
        printf("Deleted!\n");
    }
}

void cmdsEdit(Student *students)
{
    int id = 0, pos = 0;
    char input[16];

    printf("Enter the ID of the student: ");
    scanf("  %d", &id);
    pos = id - 1;

    if (check(id) == 1)
    {
        return;
    }

    printf("First Name: %s\n", students[pos].name);

    if (students[pos].hasLastName == 1) 
    {
        printf("Last Name: %s\n", students[pos].lastName);
    }
    printf("GPA: %.2f\n", students[pos].gpa);

    while (strcmp(input, "n") != 0) 
    {
        printf("What do you want to change? \nEnter \"name\" to edit First Name.\nEnter \"last\" to edit Last Name.\nEnter \"gpa\" to edit modules & grades.\n");
        printf("To exit, enter \"n\"\n");
        printf("> ");
        scanf("  %s", input);

        if (strcmp(input, "name") == 0) 
        {
            editFirstName(students, pos);
        }
        else if (strcmp(input, "last") == 0) 
        {
            if (students[id].hasLastName == 0)
            {
                printf("ERROR: Student does not have a last name.\n");
                return;
            }
            editLastName(students, pos);
        }
        else if (strcmp(input,"gpa") == 0) 
        {
            editGPA(students, pos);
        }
    }
    
}

void editFirstName(Student *students, int pos) 
{
    char newInput[64], confirm;
    printf("You are changing the FIRST NAME: %s\n", students[pos].name);
    printf("> ");
    scanf(" %s", newInput);
    printf("You are changing %s >> %s. Type \"y\" to confirm. \"n\" to cancel.\n", students[pos].name, newInput);
    printf("> ");
    scanf(" %c", &confirm);
    
    if (confirm == 'y') 
    {
        strcpy(students[pos].name, newInput);
    } 
    else 
    {
        printf("Cancelled.\n");
    }
}

void editLastName(Student *students, int pos) 
{
    char newInput[64], confirm;
    printf("You are changing the LAST NAME: %s\n", students[pos].lastName);
    printf("> ");
    scanf(" %s", newInput);
    printf("You are changing %s >> %s. Type \"y\" to confirm. \"n\" to cancel.\n", students[pos].lastName, newInput);
    printf("> ");
    scanf(" %c", &confirm);
    
    if (confirm == 'y') 
    {
        strcpy(students[pos].lastName, newInput);
    } 
    else 
    {
        printf("Cancelled.");
    }
}

void editGPA(Student *students, int pos) 
{
    char name[64];
    float GPA = 0.00, wGPA = 0.00, tGPA = 0.00;
    int credits = 0, tCredits;
    printf("You are editing the modules associated with %s.\n", students[pos].name);
    printf("Enter the module NAME: ");
    scanf("  %[^\n]s", name);
    printf("Enter the student's GPA: ");
    scanf("  %f", &GPA);

    if (moduleExists(name) >=  0) 
    {
        credits = modules[moduleExists(name)].credits;  
        tCredits = students[pos].credits + credits;
        wGPA = gpaCalculator(GPA, modules[moduleExists(name)].credits);
        tGPA = ((students[pos].gpa * students[pos].credits) + (wGPA * credits));
        students[pos].gpa = tGPA / tCredits;
    } 
    else 
    {
        printf("Module does not exist.\n");
    }
}

void cmdsView(Student *students) 
{
    int id, pos;

    printf("Enter desired student's ID: ");
    scanf(" %d", &id);
    pos = id - 1;

    if (id > studentsAllocated) 
    {
        printf("ID entered is greater than number of students allocated.\n");
        return;
    }
    else if (id <= 0)
    {
        printf("ID entered is invalid.\n");
        return;
    }
    else 
    {
        if (students[id].hasLastName == 0) 
        {
            printf("%s\n", students[pos].name);
        } 
        else 
        {
            printf("%s, %s\n", students[pos].lastName, students[pos].name);
        }
        
        printf("GPA: %.2f\n", students[pos].gpa);
        printf("Credits: %d\n", students[pos].credits);
    }
}

// END OF FILE
