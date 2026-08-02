#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"

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
        while (getchar() != '\n') { }

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

static void printmemberheader(void){
    printf("%-10s %-25s %-15s\n", "Member ID", "Name", "Phone");
    printf("------------------------------------------------------\n");
}

static void printmemberrow(const Member *m){
    printf("%-10s %-25s %-15s\n", m->id, m->name, m->phone);
}

int findbookindex(const char *id){
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].id, id) == 0) {
            return i;
        }
    }
    return -1;
}
int findBookIndex(const char *id){ return findbookindex(id); }

int findMemberIndex(const char *id){
    for (int i = 0; i < memberCount; i++) {
        if (strcmp(members[i].id, id) == 0) {
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



void addmember(void){
    if (memberCount >= MAX_RECORDS) {
        printf("Member storage is full.\n");
        return;
    }

    Member m;
    printf("Member ID: ");
    readLine(m.id, sizeof(m.id));
    printf("Name: ");
    readLine(m.name, sizeof(m.name));
    printf("Phone: ");
    readLine(m.phone, sizeof(m.phone));

    if (strlen(m.id) == 0 || strlen(m.name) == 0) {
        printf("Member ID and Name are required. Member not added.\n");
        return;
    }

    if (findMemberIndex(m.id) != -1) {
        printf("A member with this ID already exists.\n");
        return;
    }

    members[memberCount++] = m;
    save_members();
    printf("Member added successfully!\n");
}

void deletemember(void){
    char id[MAX_ID_LEN];
    printf("Enter Member ID to delete: ");
    readLine(id, sizeof(id));

    int idx = findMemberIndex(id);
    if (idx == -1) {
        printf("No member found with that ID.\n");
        return;
    }

    for (int i = idx; i < memberCount - 1; i++) {
        members[i] = members[i + 1];
    }
    memberCount--;
    save_members();
    printf("Member deleted successfully.\n");
}

void displayallmembers(void){
    printmemberheader();
    if (memberCount == 0) {
        printf("(no members registered)\n");
        return;
    }
    for (int i = 0; i < memberCount; i++) {
        printmemberrow(&members[i]);
    }
}


void issuebook(void){
    char bookId[MAX_ID_LEN], memberId[MAX_ID_LEN];

    printf("Enter Book ID to issue: ");
    readLine(bookId, sizeof(bookId));
    int bIdx = findBookIndex(bookId);
    if (bIdx == -1) {
        printf("No book found with that ID.\n");
        return;
    }
    if (strcmp(books[bIdx].status, "Issued") == 0) {
        printf("This book is already issued.\n");
        return;
    }

    printf("Enter Member ID: ");
    readLine(memberId, sizeof(memberId));
    if (findMemberIndex(memberId) == -1) {
        printf("No member found with that ID.\n");
        return;
    }

    if (issuedCount >= MAX_RECORDS) {
        printf("Issued-record storage is full.\n");
        return;
    }

    IssuedBook rec;
    strcpy(rec.bookId, bookId);
    strcpy(rec.memberId, memberId);

    printf("Issue date (DD-MM-YYYY): ");
    readLine(rec.issueDate, sizeof(rec.issueDate));
    printf("Due date (DD-MM-YYYY): ");
    readLine(rec.dueDate, sizeof(rec.dueDate));

    issued[issuedCount++] = rec;
    strcpy(books[bIdx].status, "Issued");

    save_issued();
    save_books();
    printf("Book issued successfully!\n");
}

void returnbook(void){
    char bookId[MAX_ID_LEN];
    printf("Enter Book ID to return: ");
    readLine(bookId, sizeof(bookId));

    int recIdx = -1;
    for (int i = 0; i < issuedCount; i++) {
        if (strcmp(issued[i].bookId, bookId) == 0) {
            recIdx = i;
            break;
        }
    }

    if (recIdx == -1) {
        printf("No active issue record found for this Book ID.\n");
        return;
    }

    for (int i = recIdx; i < issuedCount - 1; i++) {
        issued[i] = issued[i + 1];
    }
    issuedCount--;

    int bIdx = findBookIndex(bookId);
    if (bIdx != -1) {
        strcpy(books[bIdx].status, "Available");
    }

    save_issued();
    save_books();
    printf("Book returned successfully!\n");
}

void displayissuedbooks(void){
    printf("%-10s %-10s %-12s %-12s\n", "Book ID", "Member ID", "Issue Date", "Due Date");
    printf("--------------------------------------------------\n");
    if (issuedCount == 0) {
        printf("(no books currently issued)\n");
        return;
    }
    for (int i = 0; i < issuedCount; i++) {
        printf("%-10s %-10s %-12s %-12s\n",
               issued[i].bookId, issued[i].memberId,
               issued[i].issueDate, issued[i].dueDate);
    }
}



int main(void){
    load_books();
    load_members();
    load_issued();

    if(login() == 1){
        int choice, running = 1;
        while(running){
            clearScreen();
            MainMenu();
            choice = getValidInt(0, 10);

            switch (choice) {
                case 1:  addbook();            break;
                case 2:  deletebook();         break;
                case 3:  searchbook();         break;
                case 4:  displayallbooks();    break;
                case 5:  addmember();          break;
                case 6:  deletemember();       break;
                case 7:  displayallmembers();  break;
                case 8:  issuebook();          break;
                case 9:  returnbook();         break;
                case 10: displayissuedbooks(); break;
                case 0:
                    running = 0;
                    printf("Exiting the program. Goodbye!\n");
                    break;
                default:
                    printf("Invalid option. Please try again.\n");
            }

            if (running == 1) {
                pauseScreen();
            }
        }
    }
    return 0;
}