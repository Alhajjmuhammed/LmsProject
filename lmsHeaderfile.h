#ifndef LMSHEADERFILE_H
#define LMSHEADERFILE_H
struct Book;
struct User;
struct Node;
struct Queue;
struct Queue* createQueue();
int isEmpty(struct Queue* queue);
void borrow(struct Queue* queue, const char* ISBN_number, const char* title, const char* author, const char* publisher, int pub_year, double price);
void borrowBook(struct Queue* queue, struct Book* head);
void returnBook(struct Queue* queue);
void viewBook(struct Queue* queue);
void bookHistory(struct Queue* queue);

struct User* admin(const char* fullname, const char* username, const char* password);
void addadmin(struct User** head, const char* fullname, const char* username, const char* password);
struct User* student(const char* fullname, const char* username, const char* password, const char* regnumber, const char* course);
void addstudent(struct User** head, const char* fullname, const char* username, const char* password, const char* regnumber, const char* course);
struct User* librarian(const char* fullname, const char* username, const char* password, const char* empnumber);
void addlibrarian(struct User** head, const char* fullname, const char* username, const char* password, const char* empnumber);
void displayUsers(struct User* userList);
void regStudent(struct User** head);
void reglibrarian(struct User** head);
void adminMenu(struct User** head);
void login(struct User* userList, struct User** head, struct Book** book, struct Queue* queue);


struct Book* book(const char* ISBN_number, const char* title, const char* author, const char* publisher, int pub_year, double price, int numberofCopy);
void addbook(struct Book** head, const char* ISBN_number, const char* title, const char* author, const char* publisher, int pub_year, double price, int numberofCopy);
void regBook(struct Book** head);
void displayBook(struct Book* head);
void librarianMenu(struct Book** head, struct Queue* queue);
void studentMenu(struct Book** head, struct Queue* queue);
void seachBook(struct Book* head);

char userSession[50];
#endif
