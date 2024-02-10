#include <stdio.h>
#include "lmsHeaderfile.h"
int main() {
    struct User* userList = NULL;
    struct Book* book = NULL;
    struct Queue* queue = createQueue();
    addadmin(&userList, "Husna Ali", "Husna", "123");
    addadmin(&userList, "Mohd Juma", "Alhajj", "123");
    addstudent(&userList, "Makame Haji", "mapesa", "123", "Bcs", "Bcs/17/22/018/tz");
    addbook(&book, "ISBN_number", "title", "author", "publisher", 2000, 500, 5);
    addbook(&book, "8888-555", "Java", "author", "publisher", 2000, 500, 5);
    printf("LIBRARY MANAGEMENT SYSTEM\n");
    printf("=========================\n");
    int log;
    while (1) {
        printf("1. Login\n");
        printf("2. Exit\n");
        printf("Enter Your option: ");
        scanf("%d", &log);
        if (log == 1) {
            login(userList, &userList, &book,queue);
        } else {
            break;
        }
        printf("You Logged Out Welcome Again !!\n");
    }
    printf("WELCOME AGAIN!!!!");
    return 0;
}


