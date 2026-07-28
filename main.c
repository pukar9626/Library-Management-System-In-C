#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void addbook(void);
void deletebook(void);
void searchbook(void);
void displayallbooks(void);
void addmember(void);
void deletemember(void);
void displayallmembers(void);
void issuebook(void);
void returnbook(void);
void displayissuedbooks(void);

int login(void){
    char username[15], password[15];
    int attempts = 3;

    printf("=========================================\n");
    printf("   LIBRARY MANAGEMENT SYSTEM - LOGIN\n");
    printf("=========================================\n");

    while(attempts > 0){
        printf("Enter username: ");
        scanf("%14s", username);
        printf("Enter password: ");
        scanf("%14s", password);

        if(strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0){
            printf("Login successful!\n");
            return 1;
        } else {
            attempts--;
            printf("Invalid username or password. Attempts left: %d\n", attempts);
        }
    }

    printf("Too many failed attempts. Exiting program.\n");
    return 0;
}

static void MainMenu(void){
    printf("\n=========================================\n");
    printf("     LIBRARY MANAGEMENT SYSTEM\n");
    printf("=========================================\n");
    printf(" 1. Add Book\n");
    printf(" 2. Delete Book\n");
    printf(" 3. Search Book\n");
    printf(" 4. Show All Books\n");
    printf(" 5. Add Member\n");
    printf(" 6. Delete Member\n");
    printf(" 7. Show All Members\n");
    printf(" 8. Issue Book\n");
    printf(" 9. Return Book\n");
    printf("10. Show Issued Books\n");
    printf(" 0. Exit\n");
    printf("-----------------------------------------\n");
    printf("Choose an option: ");
}

static void printbookheader(void){
    printf("%-10s %-25s %-20s %-15s %-15s %-10s\n", "Book ID", "Title", "Author", "ISBN", "Category", "Status");
    printf("--------------------------------------------------------------------------------------------\n");
}

static void printbookrow(const Book *b){
    printf("%-10s %-25s %-20s %-15s %-15s %-10s\n", b->id, b->title, b->author, b->isbn, b->category, b->status);
}

int findbookindex(const char *id){
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].id, id) == 0) {
            return i;
        }
    }
    return -1;
}

void addbook(void){
    if (bookCount >= MAX_RECORDS) {
        printf("Book storage is full.\n");
        return;
    }

    Book b;
    printf("Book ID: ");
    readLine(b.id, sizeof(b.id));
    printf("Title: ");
    readLine(b.title, sizeof(b.title));
    printf("Author: ");
    readLine(b.author, sizeof(b.author));
    printf("ISBN: ");
    readLine(b.isbn, sizeof(b.isbn));
    printf("Category: ");
    readLine(b.category, sizeof(b.category));
    printf("Type (e.g. Fiction/Reference/Textbook): ");
    readLine(b.type, sizeof(b.type));

    if (strlen(b.id) == 0 || strlen(b.title) == 0) {
        printf("Book ID and Title are required. Book not added.\n");
        return;
    }

    if (findBookIndex(b.id) != -1) {
        printf("A book with this ID already exists.\n");
        return;
    }

    strcpy(b.status, "Available");
    books[bookCount++] = b;
    save_books();
    printf("Book added successfully!\n");
}

void deletebook(void){
    char id[MAX_ID_LEN];
    printf("Enter Book ID to delete: ");
    readLine(id, sizeof(id));

    int idx = findBookIndex(id);
    if (idx == -1) {
        printf("No book found with that ID.\n");
        return;
    }

    for (int i = idx; i < bookCount - 1; i++) {
        books[i] = books[i + 1];
    }
    bookCount--;
    save_books();
    printf("Book deleted successfully.\n");
}

void searchbook(void){
    printf("Search by (1) Title  (2) Author  (3) ISBN: ");
    char choiceStr[10];
    readLine(choiceStr, sizeof(choiceStr));
    int choice = choiceStr[0] - '0';

    printf("Search term (leave blank to list all): ");
    char term[MAX_LEN];
    readLine(term, sizeof(term));

    printbookheader();
    int found = 0;
    for (int i = 0; i < bookCount; i++) {
        const char *field;
        switch (choice) {
            case 2:  field = books[i].author; break;
            case 3:  field = books[i].isbn;   break;
            default: field = books[i].title;  break;
        }

        if (term[0] == '\0' || strstr(field, term) != NULL) {
            printbookrow(&books[i]);
            found++;
        }
    }

    if (found == 0) {
        printf("(no matching books found)\n");
    }
}

void displayallbooks(void){
    printbookheader();
    if (bookCount == 0) {
        printf("(no books in the catalog)\n");
        return;
    }
    for (int i = 0; i < bookCount; i++) {
        printbookrow(&books[i]);
    }
}

int main(){
    if(login() == 1){
        int choice, running = 1;
        while(running){
            system("cls");
            MainMenu();
            scanf("%d", &choice);
            switch (choice) {
                case 1:
                    addbook();
                    break;
                case 2:
                    deletebook();
                    break;
                case 3:
                    searchbook();
                    break;
                case 4:
                    displayallbooks();
                    break;
                case 5:
                    addmember();
                    break;
                case 6:
                    deletemember();
                    break;
                case 7:
                    displayallmembers();
                    break;
                case 8:
                    issuebook();
                    break;
                case 9:
                    returnbook();
                    break;
                case 10:
                    displayissuedbooks();
                    break;
                case 0:
                    running = 0;
                    printf("Exiting the program. Goodbye!\n");
                    break;
                default:
                    printf("Invalid option. Please try again.\n");
            }
            if(running == 1){
                getchar(); 
            }
    }
    return 0;
}