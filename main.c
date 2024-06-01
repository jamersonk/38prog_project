/*
COPYRIGHT (C) 2024 JAMES KUANG ZHONGCHUAN

THIS WORK IS LICENSED UNDER THE GNU GENERAL PUBLIC LICENSE v3.0.
View the full license text here: https://www.gnu.org/licenses/gpl-3.0.en.html#license-text

v1.0 INDEV
*/

// libraries
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// struct for modules array
typedef struct {
    char name[64];
    int credits;
} Module;

// struct for student array.
typedef struct {
    char name[64];
    int hasLastName;
    char lastName [32];
    int id, credits;
    float gpa;
} Student; // potential to include modules

// prototypes
void cmds(int pg);
float gpaCalculator(float gpa, int credits);
int getPage();
void cmdsList();
void cmdsAdd();
int moduleExists(char givenName[]);
void addStudent(Student *, int);
void addModule(Module *, int);
void cmdsDel(Student *);
void cmdsEdit(Student *);
void editFirstName(Student *students, int pos);
void editLastName(Student *students, int pos);
void editGPA(Student *students, int pos);
void linkModule(Student *students, int pos);
void cmdsView(Student *);

// global variables
// modules array
Module modules[48] = {
    {.name = "Module 1", .credits = 4},
}; // DELETE ALL ELEMENTS BEFORE SUBMISSION

// students array
Student students[64] = { 
    {.name = "Owein", .hasLastName = 1, .lastName = "Wong", .id = 1, .gpa = 3.9, .credits = 6},
}; // DELETE ALL ELEMENTS BEFORE SUBMISSION

int studentsAllocated = 1; // SET TO 0.
int modulesAllocated = 1; // SET TO 0.

// BEGIN MAIN
int main()
{
    char input[128] = "void";
    int page;

    printf("WELCOME TO THE STUDENT RECORD SYSTEM!");

    while (strcmp(input, "quit") != 0) {
        printf("\nPlease enter a command. Enter \"cmds\" for a list of commands; \"quit\" to exit.\n> ");
        scanf(" %s", input);

        // input processing
        if (strcmp(input, "quit") == 0 || strcmp(input, "close") == 0 || strcmp(input, "exit") == 0) {
            printf("Quitting!\n");
            printf("THANK YOU FOR USING THE STUDENT RECORD SYSTEM.\n");
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
        else if (strcmp(input, "del") == 0) {
            cmdsDel(students);
        }
        else if (strcmp(input, "edit") == 0) {
            cmdsEdit(students);
        }
        else if (strcmp(input, "view") == 0) {
            cmdsView(students);
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
    }
    else {
        printf("=================\n");
        printf("COMMAND LIST\n");
        printf("=================\n");
        if (pg == 1) {
            printf("quit - exits the program. (sudos: close, exit)\n");
            printf("cmds - lists all available commands.\n");
            printf("list - lists all students.\n");
            printf("add - add a new student/module.\n");
            printf("del - delete a student.\n");
            printf("edit - edit a student.\n");
            printf("view - view a student in detail.\n");
        }
        printf("=================\n");
    }
    
}

float gpaCalculator(float gpa, int credits)
{
    float weightedGPA = gpa * (float)credits;
    return weightedGPA;
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
    while (i != studentsAllocated) {
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
    while (i != modulesAllocated) {
        char* moduleName = modules[i].name;
        if (strcmp(moduleName, givenName) == 0) {
            moduleExist = i;
            printf("(System: moduleExists returned TRUE)\n");
            return moduleExist;
        }
        i += 1;
    }
    moduleExist = -1;
    printf("(System: moduleExists returned FALSE)\n");
    return moduleExist;
}

void cmdsAdd()
{
    char selectAdd = 'p';
    
    printf("Select STUDENT [S] or MODULE [M]: ");
    scanf(" %c", &selectAdd);

    if (selectAdd == 'S') {
        addStudent(students, studentsAllocated);
    } 
    else if (selectAdd == 'M') {
        addModule(modules, modulesAllocated);
    } 
}

void addStudent(Student *students, int num) 
{
    students[num].id = num + 1;
    char moduleName[64];
    char lastNameState = 'p';
    float GPA = 0.00, tGPA = 0.00, cGPA = 0.00, wGPA = 0.00; // GPA is for each new module; cGPA is total GPA; wGPA is weighted GPA for each new module.
    int exitState = 0, credits, tCredits = 0, pos = 0; // creduts is for each new module; tCredits is for total credits.

    printf("Enter the FIRST NAME: ");
    scanf(" %[^\n]s", students[num].name); // %[^\n]d allows for the acceptance of multi word inputs.
    printf("Does this student have a LAST NAME? [Y/N] ");
    scanf(" %c", &lastNameState);

    // to check if user wants to include a last name.
    if (lastNameState == 'y') {
        // for user to input last name.
        printf("Enter the LAST NAME: ");
        scanf(" %[^\n]s", students[num].lastName);        
        students[num].hasLastName = 1;
    }

    // for calculating student gpa
    printf("You will now be prompted to enter MODULE INFORMATION.\n");
    while (exitState != 1) {
        printf("Enter Module NAME: ");
        scanf(" %[^\n]s", moduleName);             
        if (moduleExists(moduleName) >= 0) {  
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
            if (exitRequest == 'N' || exitRequest == 'n') { // to check for user exit input.
                    exitState = 1;
            }
        } else {
            // if user adds in a module that dosen't exist.
            printf("Module could not be found. Please try again.\n");
        }
    }
    studentsAllocated += 1;
    cGPA += tGPA / tCredits;
    students[num].gpa = cGPA;
}

void addModule(Module *modules, int num)
{
    char moduleName[64];
    int credits = 0, arraySize;
    printf("Enter module NAME: ");
    scanf(" %[^\n]s", moduleName);
    printf("Enter no. of CREDITS: ");
    scanf("%d", credits);
    if (moduleExists(moduleName) == -1) {
        printf("ERROR: A module with that name already exists.");
    } else {
        // appending newModule to modules array.
        strcpy(modules[num].name, moduleName);
        modules[num].credits = credits;
        printf("Created %s, with %d credits.", moduleName, credits);
    }
}

void cmdsDel(Student *students)
{
    int id = 0, pos = 0, i = 0, j = 0;
    char state;
    printf("Enter ID of Student you want to delete: ");
    scanf(" %d", &id);
    pos = id - 1;

    printf("Please confirm you want to DELETE the below student [y/n]\n");
    printf("%s %s | ID: %d\n", students[pos].name, students[pos].lastName, students[pos].id);
    scanf(" %c", &state);

    if (state == 'y') {
        while (i < studentsAllocated) {
            if (students[i].id == id) {
                j = i;
                while (j < studentsAllocated) {
                    students[j] = students[j + 1];
                    j += 1; 
                    students[j].id = students[j].id - 1;
                }
                studentsAllocated = studentsAllocated - 1;
            }
            i += 1;
        }
        printf("Deleted!\n");
    }
}

void cmdsEdit(Student *students)
{
    int id = 0, pos = 0, i = 0;
    char input[16];

    printf("Enter the ID of the student: ");
    scanf("  %d", &id);
    pos = id - 1;

    printf("First Name: %s\n", students[pos].name);
    if (students[pos].hasLastName == 1) {
        printf("Last Name: %s\n", students[pos].lastName);
    }
    printf("GPA: %.2f\n", students[pos].gpa);

    while (strcmp(input, "n") != 0) {
        printf("What do you want to change? \nEnter \"name\" to edit First Name.\nEnter \"last\" to edit Last Name.\nEnter \"gpa\" to edit modules & grades.\n");
        printf("To exit, enter \"n\"\n");
        printf("> ");
        scanf("  %s", input);
        if (strcmp(input, "name") == 0) {
            editFirstName(students, pos);
        }
        else if (strcmp(input, "last") == 0) {
            editLastName(students, pos);
        }
        else if (strcmp(input,"gpa") == 0) {
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
    
    if (confirm == 'y') {
        strcpy(students[pos].name, newInput);
    } 
    else {
        printf("Cancelled.");
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
    
    if (confirm == 'y') {
        strcpy(students[pos].lastName, newInput);
    } 
    else {
        printf("Cancelled.");
    }
}

void editGPA(Student *students, int pos) 
{
    linkModule(students, pos); // potential for inclusion of delinking modules
}

void linkModule(Student *students, int pos) 
{
    char name[64];
    float GPA = 0.00, wGPA = 0.00, tGPA = 0.00;
    int credits = 0, tCredits;
    printf("You are editing the modules associated with %s.\n", students[pos].name);
    printf("Enter the module NAME: ");
    scanf("  %[^\n]s", name);
    printf("Enter the student's GPA: ");
    scanf("  %f", &GPA);

    if (moduleExists(name) >=  0) {
        credits = modules[moduleExists(name)].credits;  
        tCredits = students[pos].credits + credits;
        wGPA = gpaCalculator(GPA, modules[moduleExists(name)].credits);
        tGPA = ((students[pos].gpa * students[pos].credits) + (wGPA * credits));
        students[pos].gpa = tGPA / tCredits;
    } else {
        printf("Module does not exist.\n");
    }
}

/*
void delinkModule() 
{
    // NOT IN USE
}
*/

void cmdsView(Student *students) 
{
    int id, pos;

    printf("Enter desired student's ID: ");
    scanf(" %d", &id);
    pos = id - 1;

    if (id > studentsAllocated) {
        printf("ID entered is greater than number of students allocated.")
    }
    else {
        if (students[id].hasLastName == 0) {
            printf("%s\n", students[pos].name);
        } 
        else {
            printf("%s, %s\n", students[pos].lastName, students[pos].name);
        }
        printf("GPA: %.2f\n", students[pos].gpa);
        printf("Credits: %d\n", students[pos].credits);
    }
}