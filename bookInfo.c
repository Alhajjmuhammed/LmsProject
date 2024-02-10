#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lmsHeaderfile.h"

#define USER_LEN 50

struct Book{
	char ISBN_number[USER_LEN];
	char title[USER_LEN];
	char author[USER_LEN];
	char publisher[USER_LEN];
	int pub_year;
	double price;
	int  numberofCopy;
	struct Book* next;
};

// Structure representing a node in the queue
struct Node {
    char username[USER_LEN];
    char ISBN_number[USER_LEN];
	char title[USER_LEN];
	char author[USER_LEN];
	char publisher[USER_LEN];
	int pub_year;
	double price;
	char status[USER_LEN];
    struct Node* next;
};
// Structure representing the queue
struct Queue {
    struct Node *front, *rear;
};
// Function to create an empty queue
struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = queue->rear = NULL;
    return queue;
}
// Function to check if the queue is empty
int isEmpty(struct Queue* queue) {
    return (queue->front == NULL);
}
// Function to enqueue an element into the queue
void borrow(struct Queue* queue, const char* ISBN_number, const char* title, const char* author, const char* publisher, int pub_year, double price) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strncpy(newNode->username, userSession, sizeof(newNode->username));
    strncpy(newNode->ISBN_number, ISBN_number, sizeof(newNode->ISBN_number));
    strncpy(newNode->title, title, sizeof(newNode->title));
    strncpy(newNode->author, author, sizeof(newNode->author));
    strncpy(newNode->publisher, publisher, sizeof(newNode->publisher));
    newNode->pub_year = pub_year;
    newNode->price = price;
    strncpy(newNode->status, "Borrowed", sizeof(newNode->status));
    newNode->next = NULL;
    if (isEmpty(queue)) {
        queue->front = queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

void borrowBook(struct Queue* queue, struct Book* head) {
    char ISBN_number[USER_LEN];
    printf("Enter Book by ISBN number: ");
    scanf(" %[^\n]", ISBN_number);
    getchar(); 
    struct Node* current = queue->front;
    while (current != NULL) {
        if (strcmp(current->ISBN_number, ISBN_number) == 0 && strcmp(current->username, userSession) == 0 && strcmp(current->status, "Borrowed") == 0) {
            printf("You have already borrowed this book.\n");
            return;
        }
        current = current->next;
    }

    struct Book* currentBook = head;
    while (currentBook != NULL) {
        if (strcmp(currentBook->ISBN_number, ISBN_number) == 0) {
            borrow(queue, currentBook->ISBN_number, currentBook->title, currentBook->author, currentBook->publisher, currentBook->pub_year, currentBook->price);
            printf("Book borrowed successfully.\n");
            return;
        }
        currentBook = currentBook->next;
    }

    printf("Book with ISBN '%s' not found.\n", ISBN_number);
}

void returnBook(struct Queue* queue) {
    struct Node* current = queue->front;
    char ISBN_number[USER_LEN];
    printf("Enter Book by ISBN number: ");
    scanf(" %[^\n]", ISBN_number);
    getchar();

    while (current != NULL) {
        if (strcmp(current->ISBN_number, ISBN_number) == 0 && strcmp(current->username, userSession) == 0) {
            strncpy(current->status, "Returned", sizeof(current->status));
            printf("Book returned successfully.\n");
            return;
        }
        current = current->next;
    }
    printf("Book with ISBN '%s' not found.\n", ISBN_number);
}


void viewBook(struct Queue* queue) {
    struct Node* current = queue->front;
    int borrowedBooksExist = 0; 
    while (current != NULL) {
        if (strcmp(current->username, userSession) == 0 && strcmp(current->status, "Borrowed") == 0) {
            borrowedBooksExist = 1;
            break; 
        }
        current = current->next;
    }

    if (!borrowedBooksExist) { 
        printf("No borrowed Books\n");
        return;
    }

    current = queue->front;
    while (current != NULL) {
        if (strcmp(current->username, userSession) == 0 && strcmp(current->status, "Borrowed") == 0)
            printf("Username: %s, ISBN: %s, Title: %s, Author: %s, Status: %s\n", current->username, current->ISBN_number, current->title, current->author, current->status);
        current = current->next;
    }

    int num;
    printf("Press 1 if you want to return and 2 to exit\n");
    printf("Enter Your option: ");
    scanf("%d", &num);
    if (num == 1) {
        returnBook(queue);
    }
}




// Function for creating node for book
struct Book* book(const char* ISBN_number, const char* title, const char* author, const char* publisher, int pub_year, double price, int numberofCopy) {
	struct Book* newBook = (struct Book*)malloc(sizeof(struct Book));
    strncpy(newBook->ISBN_number, ISBN_number, sizeof(newBook->ISBN_number));
    strncpy(newBook->title, title, sizeof(newBook->title));
    strncpy(newBook->author, author, sizeof(newBook->author));
    strncpy(newBook->publisher, publisher, sizeof(newBook->publisher));
    newBook->pub_year = pub_year;
    newBook->price = price;
    newBook->numberofCopy = numberofCopy;
    newBook->next = NULL;
    return newBook;
}

void addbook(struct Book** head, const char* ISBN_number, const char* title, const char* author, const char* publisher, int pub_year, double price, int numberofCopy) {
    struct Book* current = *head;

    while (current != NULL) {
        if (strcmp(current->ISBN_number, ISBN_number) == 0) {
            printf("The book already exists.\n");
            return;
        }
        current = current->next;
    }

    struct Book* newBook = book(ISBN_number, title, author, publisher, pub_year, price, numberofCopy);
    newBook->next = *head;
    *head = newBook;
}

// Function for Register Book
void regBook(struct Book** head) {
    char ISBN_number[USER_LEN];
	char title[USER_LEN];
	char author[USER_LEN];
	char publisher[USER_LEN];
	int pub_year;
	double price;
	int  numberofCopy;

    printf("Enter ISBN number: ");
    scanf(" %[^\n]", ISBN_number);
    printf("Enter Title of the book: ");
    scanf(" %[^\n]", title);
    printf("Enter Author of the book: ");
    scanf(" %[^\n]", author);
    printf("Enter Publisher of the book: ");
    scanf(" %[^\n]", publisher);
    printf("Enter publication year: ");
    scanf("%d", &pub_year);
    printf("Enter Price of the book: ");
    scanf("%lf", &price);
    printf("Enter number of Copy: ");
    scanf("%d", &numberofCopy);
    
    addbook(head, ISBN_number, title, author, publisher, pub_year, price, numberofCopy);
    getchar();

    while (1) {
        printf("Press 1 to add again or 2 to stop: ");
        int ask;
        scanf("%d", &ask);

        if (ask == 1) {
            printf("Enter ISBN number: ");
		    scanf(" %[^\n]", ISBN_number);
		    printf("Enter Title of the book: ");
		    scanf(" %[^\n]", title);
		    printf("Enter Author of the book: ");
		    scanf(" %[^\n]", author);
		    printf("Enter Publisher of the book: ");
		    scanf(" %[^\n]", publisher);
		    printf("Enter publication year: ");
		    scanf("%d", &pub_year);
		    printf("Enter Price of the book: ");
		    scanf("%lf", &price);
		    printf("Enter number of Copy: ");
		    scanf("%d", &numberofCopy);
		    
		    addbook(head, ISBN_number, title, author, publisher, pub_year, price, numberofCopy);
    		getchar();
        } else {
            break;
        }
    }
}

void displayBook(struct Book* head) {
	struct Book* current = head;
    int sn = 1;
	while(current != NULL) {
		printf("%d| ISBN Number: %s| Title: %s| Author: %s| Publisher: %s| Year %d| Price %lf \n", sn++, current->ISBN_number, current->title, current->author, current->publisher, current->pub_year, current->price);
		current = current->next;
	}
}


// librarian menu
void librarianMenu(struct Book** head, struct Queue* queue) {
    while (1) {
        printf("Choose by enter Number\n");
        printf("=======================\n");
        int num;
        printf("1. Add book \n");
        printf("2. View all book \n");
        printf("3. Search book \n");
        printf("4. View book history \n");
        printf("5. Update book \n");
        printf("6. Remove book \n");
        printf("7. LogOut \n");
        printf("Enter Your option: ");
        scanf("%d", &num);
        if (num == 1) {
            printf("ADD BOOK \n");
            printf("========\n");
            regBook(head);
        } else if (num == 2) {
            printf("VIEW ALL BOOKS \n");
            printf("==============\n");
            displayBook(*head); 
        } else if (num == 3) {
            printf("SEARCH BOOK \n");
            printf("==============\n");
            seachBook(*head);
        } else if (num == 4) {
            printf("VIEW BOOKS HISTORY \n");
            printf("==============\n");
            bookHistory(queue); 
        } else if (num == 5) {
            printf("UPDATE BOOK \n");
            printf("==============\n");  
        }else if (num == 6) {
            printf("REMOVE BOOK \n");
            printf("==============\n");  
        } else if (num == 7) {
            break;
        } else {
            printf("You pressed wrong input %d \n", num);
        }
    }
}

// student menu
void studentMenu(struct Book** head, struct Queue* queue) {
    while (1) {
        printf("Choose by enter Number\n");
        printf("=======================\n");
        int num;
        printf("1. View all book \n");
        printf("2. Search book \n");
        printf("3. View borrowed books \n");
        printf("4. LogOut \n");
        printf("Enter Your option: ");
        scanf("%d", &num);
        if (num == 1) {
            printf("VIEW ALL BOOKS \n");
            printf("========\n");
            displayBook(*head);
            printf("==========================================================================\n");
            while(1) {
                printf("Press 1 if you want to borrow and 2 to exit");
                printf("Enter Your option: ");
                scanf("%d", &num); 
                if (num == 1) {borrowBook(queue, *head);}
                else {break;} 
            }
            
        } else if (num == 2) {
            printf("SEARCH BOOK \n");
            printf("==============\n");
            seachBook(*head); 
        } else if (num == 3) {
            printf("VIEW BORROWED BOOKS \n");
            printf("==============\n"); 
            viewBook(queue);
        } else if (num == 4) {
            break;
        } else {
            printf("You pressed the wrong input %d \n", num);
        }
    }
}


void seachBook(struct Book* head) {
    struct Book* current = head;  
    char isbn[USER_LEN];
    int found = 0;
    printf("Search Book by ISBN number: ");
    scanf(" %[^\n]", isbn);
    getchar(); 

    while (current != NULL) {
        if (strcmp(current->ISBN_number, isbn) == 0) {
            found = 1;
            break;
        }
        current = current->next;
    }
    if (found) {
		printf("ISBN Number: %s| Title: %s| Author: %s| Publisher: %s| Year %d| Price %lf \n", current->ISBN_number, current->title, current->author, current->publisher, current->pub_year, current->price);
    } 
    else { printf("The book is not found.\n");}

}


void bookHistory(struct Queue* queue) {
    struct Node* current = queue->front;
    printf("Borrowed Books:\n");
    printf("====================\n");
    while (current != NULL) {
        if (strcmp(current->status, "Borrowed") == 0)
            printf("Username: %s, ISBN: %s, Title: %s, Author: %s, Status: %s\n", current->username, current->ISBN_number, current->title, current->author, current->status);
        current = current->next;
    }
    
    current = queue->front; 
    
    printf("\nReturned Books:\n");
    printf("====================\n");
    while (current != NULL) {
        if (strcmp(current->status, "Returned") == 0)
            printf("Username: %s, ISBN: %s, Title: %s, Author: %s, Status: %s\n", current->username, current->ISBN_number, current->title, current->author, current->status);
        current = current->next;
    }
    printf("=========================================================================================================");
}




