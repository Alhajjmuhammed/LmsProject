#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lmsHeaderfile.h"

// Define constants for user types
#define STUDENT 1
#define LIBRARIAN 2
#define ADMIN 3
#define USER_LEN 50

// Define the structure for users
struct User {
    char fullname[USER_LEN];
    char username[USER_LEN];
    char password[USER_LEN];
    int userType;
    union {
        struct {
            char regnumber[USER_LEN];
            char course[USER_LEN];
        } student;
        struct {
            char empnumber[USER_LEN];
        } librarian;
    } userInfo;
    struct User* next;
};

// Function for creating node for admin
struct User* admin(const char* fullname, const char* username, const char* password) {
    struct User* newUser = (struct User*)malloc(sizeof(struct User));
    strncpy(newUser->fullname, fullname, sizeof(newUser->fullname));
    strncpy(newUser->username, username, sizeof(newUser->username));
    strncpy(newUser->password, password, sizeof(newUser->password));
    newUser->userType = ADMIN;
    newUser->next = NULL;
    return newUser;
}

// Function for add admin
void addadmin(struct User** head, const char* fullname, const char* username, const char* password) {
    struct User* current = *head;

    while (current != NULL) {
        if (strcmp(current->username, username) == 0) {
            printf("Username '%s' already exists.\n", username);
            return;
        }
        current = current->next;
    }

    struct User* newUser = admin(fullname, username, password);
    newUser->next = *head;
    *head = newUser;
}

// Function for creating node for student
struct User* student(const char* fullname, const char* username, const char* password, const char* regnumber, const char* course) {
    struct User* newUser = (struct User*)malloc(sizeof(struct User));

    strcpy(newUser->fullname, fullname);
    strcpy(newUser->username, username);
    strcpy(newUser->password, password);
    newUser->userType = STUDENT;
    strcpy(newUser->userInfo.student.regnumber, regnumber);
    strcpy(newUser->userInfo.student.course, course);
    newUser->next = NULL;
    return newUser;
}

// Method for add student
void addstudent(struct User** head, const char* fullname, const char* username, const char* password, const char* regnumber, const char* course) {
    struct User* current = *head;

    while (current != NULL) {
        if (strcmp(current->username, username) == 0) {
            printf("Username '%s' already exists.\n", username);
            return;
        }
        current = current->next;
    }

    struct User* newUser = student(fullname, username, password, regnumber, course);
    newUser->next = *head;
    *head = newUser;
}

// Function for creating node for librarian
struct User* librarian(const char* fullname, const char* username, const char* password, const char* empnumber) {
    struct User* newUser = (struct User*)malloc(sizeof(struct User));

    strcpy(newUser->fullname, fullname);
    strcpy(newUser->username, username);
    strcpy(newUser->password, password);
    newUser->userType = LIBRARIAN;
    strcpy(newUser->userInfo.librarian.empnumber, empnumber);
    newUser->next = NULL;
    return newUser;
}

// Function for add librarian
void addlibrarian(struct User** head, const char* fullname, const char* username, const char* password, const char* empnumber) {
    struct User* current = *head;

    while (current != NULL) {
        if (strcmp(current->username, username) == 0) {
            printf("Username '%s' already exists.\n", username);
            return;
        }
        current = current->next;
    }

    struct User* newUser = librarian(fullname, username, password, empnumber);
    newUser->next = *head;
    *head = newUser;
}

void displayUsers(struct User* userList) {
    printf("SN  | FULLNAME     | USERNAME   | PASSWORD | ROLE\n");
    printf("=============================================================\n");

    struct User* currentUser = userList;
    int sn = 1;

    while (currentUser != NULL) {
        if (currentUser->userType == STUDENT)
            printf("%d   | %s    | %s   | %s   | %s \n", sn, currentUser->fullname, currentUser->username, currentUser->password, "Student");
        else if (currentUser->userType == LIBRARIAN)
            printf("%d   | %s    | %s   | %s   | %s \n", sn, currentUser->fullname, currentUser->username, currentUser->password, "Librarian");
        else 
            printf("%d   | %s    | %s   | %s   | %s \n", sn, currentUser->fullname, currentUser->username, currentUser->password, "Admin");
        currentUser = currentUser->next;
        sn++;
    }
}

// Function for Register Student
void regStudent(struct User** head) {
    char fullname[USER_LEN];
    char username[USER_LEN];
    char password[USER_LEN];
    char regnumber[USER_LEN];
    char course[USER_LEN];

    printf("Enter Fullname: ");
    scanf(" %[^\n]", fullname);
    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);
    printf("Enter Registration Number: ");
    scanf("%s", regnumber);
    printf("Enter Course: ");
    scanf("%s", course);
    addstudent(head, fullname, username, password, regnumber, course);
    getchar();

    while (1) {
        printf("Press 1 to add again or 2 to stop: ");
        int ask;
        scanf("%d", &ask);

        if (ask == 1) {
            printf("Enter Fullname: ");
            scanf(" %[^\n]", fullname);
            printf("Enter Username: ");
            scanf("%s", username);
            printf("Enter Password: ");
            scanf("%s", password);
            printf("Enter Registration Number: ");
            scanf("%s", regnumber);
            printf("Enter Course: ");
            scanf("%s", course);
            addstudent(head, fullname, username, password, regnumber, course);
            getchar();
        } else {
            break;
        }
    }
}

// Function for Register Librarian
void reglibrarian(struct User** head) {
    char fullname[USER_LEN];
    char username[USER_LEN];
    char password[USER_LEN];
    char empnumber[USER_LEN];

    printf("Enter Fullname: ");
    scanf(" %[^\n]", fullname);
    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);
    printf("Enter Employee Number: ");
    scanf("%s", empnumber);
    addlibrarian(head, fullname, username, password, empnumber);
    getchar();

    while (1) {
        printf("Press 1 to add again or 2 to stop: ");
        int ask;
        scanf("%d", &ask);

        if (ask == 1) {
            printf("Enter Fullname: ");
            scanf(" %[^\n]", fullname);
            printf("Enter Username: ");
            scanf("%s", username);
            printf("Enter Password: ");
            scanf("%s", password);
            printf("Enter Employee Number: ");
            scanf("%s", empnumber);
            addlibrarian(head, fullname, username, password, empnumber);
            getchar();
        } else {
            break;
        }
    } 
}

// Admin menu
void adminMenu(struct User** head) {
    while (1) {
        printf("Choose by enter Number\n");
        printf("=======================\n");
        int num;
        printf("1. Add user \n");
        printf("2. View user \n");
        printf("3. LogOut \n");
        printf("Enter Your option: ");
        scanf("%d", &num);
        if (num == 1) {
            printf("ADD USER \n");
            printf("========\n");
            while (1) {
                int choice;
                printf("1. Add Student \n");
                printf("2. Add Librarian \n");
                printf("3. Back \n");
                printf("Enter Your option: ");
                scanf("%d", &choice);
                if (choice == 1) {
                    printf("Add Student \n");
                    // revoke function
                    regStudent(head);
                } else if (choice == 2) {
                    printf("Add Librarian \n");
                    // revoke function
                    reglibrarian(head);
                } else if (choice == 3) {
                    break;
                } else {
                    printf("Wrong input");
                }
            }
        } else if (num == 2) {
            printf("VIEW USER \n");
            displayUsers(*head);  
        } else if (num == 3) {
            break;
        } else {
            printf("You pressed wrong input %d \n", num);
        }
    }
}

void login(struct User* userList, struct User** head, struct Book** book, struct Queue* queue) {
    char username[USER_LEN];
    char password[USER_LEN];
    
    printf("LOGIN\n");
    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);
    
    struct User* currentUser = userList;
    
    while (currentUser != NULL) {
        if (strcmp(currentUser->username, username) == 0 && strcmp(currentUser->password, password) == 0) {
            //printf("%d ", currentUser->userType);
            strcpy(userSession, currentUser->username);
            if (currentUser->userType == STUDENT) {
                //printf("The user is student\n");
                studentMenu(book, queue);
            } else if (currentUser->userType == LIBRARIAN) {
                //printf("The user is Librarian\n");
                librarianMenu(book, queue);
            } else if (currentUser->userType == ADMIN) {
                //printf("The user is Admin\n");
                adminMenu(head);
            }
            return;
        }
        currentUser = currentUser->next;
    }

    // If the loop completes without finding a matching user
    printf("Login failed. Invalid username or password.\n");
}

