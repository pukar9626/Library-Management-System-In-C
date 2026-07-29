#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ================= CONFIG / LIMITS ================= */
#define MAX_BOOKS   100
#define MAX_MEMBERS 100
#define MAX_ISSUED  100

/* ================= STRUCTS ================= */
struct Book {
    int  id;
    char title[100];
    char author[100];
    int  isIssued;   /* 0 = available, 1 = issued */
};

struct Member {
    int  id;
    char name[50];
    char address[50];
    char phone[15];
};

struct IssuedBook {
    int  bookId;
    int  memberId;
    char issueDate[15];
};

/* ================= GLOBAL DATA ================= */
struct Book        books[MAX_BOOKS];
int bookCount = 0;

struct Member       members[MAX_MEMBERS];
int memberCount = 0;

struct IssuedBook   issuedBooks[MAX_ISSUED];
int issuedCount = 0;

/* ================= FUNCTION DECLARATIONS ================= */
int  login(void);
void mainMenu(void);

void addBook(void);
void deleteBook(void);
void searchBook(void);
void displayAllBooks(void);
int  findBookIndex(int id);

void addMember(void);
void deleteMember(void);
void displayAllMembers(void);
int  findMemberIndex(int id);

void issueBook(void);
void returnBook(void);
void displayIssuedBooks(void);

void saveBooks(void);
int  loadBooks(void);
void saveMembers(void);
int  loadMembers(void);
void saveIssuedBooks(void);
int  loadIssuedBooks(void);

/* ================= LOGIN ================= */
int login(void) {
    char username[15], password[15];
    int attempts = 3;

    printf("=========================================\n");
    printf("   LIBRARY MANAGEMENT SYSTEM - LOGIN\n");
    printf("=========================================\n");

    while (attempts > 0) {
        printf("Enter username: ");
        scanf("%14s", username);
        printf("Enter password: ");
        scanf("%14s", password);

        if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
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

/* ================= MENU ================= */
void mainMenu(void) {
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

/* ================= BOOK FUNCTIONS ================= */
int findBookIndex(int id) {
    int i;
    for (i = 0; i < bookCount; i++) {
        if (books[i].id == id) return i;
    }
    return -1;
}

void addBook(void) {
    if (bookCount >= MAX_BOOKS) {
        printf("Book storage is full.\n");
        return;
    }

    struct Book b;
    printf("\n----- ADD NEW BOOK -----\n");
    printf("Enter Book ID: ");
    scanf("%d", &b.id);

    if (findBookIndex(b.id) != -1) {
        printf("A book with this ID already exists.\n");
        return;
    }

    printf("Enter Title: ");
    scanf(" %[^\n]", b.title);
    printf("Enter Author: ");
    scanf(" %[^\n]", b.author);

    b.isIssued = 0;
    books[bookCount] = b;
    bookCount++;
    saveBooks();
    printf("Book added successfully!\n");
}

void deleteBook(void) {
    int id, idx, j;
    if (bookCount == 0) {
        printf("\nThere are no books to delete.\n");
        return;
    }
    printf("\n----- DELETE BOOK -----\n");
    printf("Enter Book ID to delete: ");
    scanf("%d", &id);

    idx = findBookIndex(id);
    if (idx == -1) {
        printf("No book found with that ID.\n");
        return;
    }

    for (j = idx; j < bookCount - 1; j++) {
        books[j] = books[j + 1];
    }
    bookCount--;
    saveBooks();
    printf("Book deleted successfully.\n");
}

void searchBook(void) {
    char term[100];
    int i, found = 0;
    printf("\n----- SEARCH BOOK -----\n");
    printf("Enter Title or Author to search: ");
    scanf(" %[^\n]", term);

    printf("%-8s %-25s %-20s %-10s\n", "ID", "TITLE", "AUTHOR", "STATUS");
    printf("--------------------------------------------------------------\n");
    for (i = 0; i < bookCount; i++) {
        if (strstr(books[i].title, term) != NULL || strstr(books[i].author, term) != NULL) {
            printf("%-8d %-25s %-20s %-10s\n", books[i].id, books[i].title, books[i].author,
                   books[i].isIssued ? "Issued" : "Available");
            found++;
        }
    }
    if (found == 0) {
        printf("(no matching books found)\n");
    }
}

void displayAllBooks(void) {
    int i;
    if (bookCount == 0) {
        printf("\n(no books in the catalog)\n");
        return;
    }
    printf("\n%-8s %-25s %-20s %-10s\n", "ID", "TITLE", "AUTHOR", "STATUS");
    printf("--------------------------------------------------------------\n");
    for (i = 0; i < bookCount; i++) {
        printf("%-8d %-25s %-20s %-10s\n", books[i].id, books[i].title, books[i].author,
               books[i].isIssued ? "Issued" : "Available");
    }
}

/* ================= MEMBER FUNCTIONS ================= */
int findMemberIndex(int id) {
    int i;
    for (i = 0; i < memberCount; i++) {
        if (members[i].id == id) return i;
    }
    return -1;
}

void addMember(void) {
    if (memberCount >= MAX_MEMBERS) {
        printf("\nSorry! Member list is full.\n");
        return;
    }

    struct Member m;
    printf("\n----- ADD NEW MEMBER -----\n");
    printf("Enter Member ID: ");
    scanf("%d", &m.id);

    if (findMemberIndex(m.id) != -1) {
        printf("\nThis ID is already used. Please use another ID.\n");
        return;
    }

    printf("Enter Name: ");
    scanf(" %[^\n]", m.name);
    printf("Enter Address: ");
    scanf(" %[^\n]", m.address);
    printf("Enter Phone Number: ");
    scanf(" %[^\n]", m.phone);

    members[memberCount] = m;
    memberCount++;
    saveMembers();
    printf("\nMember added successfully!\n");
}

void deleteMember(void) {
    int id, idx, j;
    if (memberCount == 0) {
        printf("\nThere is no member to delete.\n");
        return;
    }
    printf("\n----- DELETE MEMBER -----\n");
    printf("Enter Member ID to delete: ");
    scanf("%d", &id);

    idx = findMemberIndex(id);
    if (idx == -1) {
        printf("\nMember with ID %d is not found.\n", id);
        return;
    }

    printf("\nDeleting member: %s\n", members[idx].name);
    for (j = idx; j < memberCount - 1; j++) {
        members[j] = members[j + 1];
    }
    memberCount--;
    saveMembers();
    printf("Member deleted successfully!\n");
}

void displayAllMembers(void) {
    int i;
    if (memberCount == 0) {
        printf("\nNo members are registered yet.\n");
        return;
    }
    printf("\n%-8s %-20s %-20s %-15s\n", "ID", "NAME", "ADDRESS", "PHONE");
    printf("---------------------------------------------------------------\n");
    for (i = 0; i < memberCount; i++) {
        printf("%-8d %-20s %-20s %-15s\n", members[i].id, members[i].name,
               members[i].address, members[i].phone);
    }
    printf("Total Members: %d\n", memberCount);
}

/* ================= ISSUE / RETURN FUNCTIONS ================= */
void issueBook(void) {
    int bookId, memberId, bIdx, mIdx;

    if (issuedCount >= MAX_ISSUED) {
        printf("\nThe issue record is full. Cannot issue more books.\n");
        return;
    }

    printf("\n----- ISSUE A BOOK -----\n");
    printf("Enter Book ID: ");
    scanf("%d", &bookId);
    bIdx = findBookIndex(bookId);
    if (bIdx == -1) {
        printf("No book found with that ID.\n");
        return;
    }
    if (books[bIdx].isIssued) {
        printf("This book is already issued.\n");
        return;
    }

    printf("Enter Member ID: ");
    scanf("%d", &memberId);
    mIdx = findMemberIndex(memberId);
    if (mIdx == -1) {
        printf("No member found with that ID.\n");
        return;
    }

    printf("Enter Issue Date (dd-mm-yyyy): ");
    scanf("%14s", issuedBooks[issuedCount].issueDate);

    issuedBooks[issuedCount].bookId = bookId;
    issuedBooks[issuedCount].memberId = memberId;
    issuedCount++;

    books[bIdx].isIssued = 1;

    saveBooks();
    saveIssuedBooks();
    printf("Book issued successfully!\n");
}

void returnBook(void) {
    int bookId, i, j, bIdx, found = 0;

    if (issuedCount == 0) {
        printf("\nNo books are issued right now.\n");
        return;
    }

    printf("\n----- RETURN A BOOK -----\n");
    printf("Enter Book ID to return: ");
    scanf("%d", &bookId);

    for (i = 0; i < issuedCount; i++) {
        if (issuedBooks[i].bookId == bookId) {
            found = 1;
            bIdx = findBookIndex(bookId);
            if (bIdx != -1) {
                books[bIdx].isIssued = 0;
            }
            for (j = i; j < issuedCount - 1; j++) {
                issuedBooks[j] = issuedBooks[j + 1];
            }
            issuedCount--;
            break;
        }
    }

    if (found) {
        saveBooks();
        saveIssuedBooks();
        printf("Book returned successfully!\n");
    } else {
        printf("That book is not in the issued list.\n");
    }
}

void displayIssuedBooks(void) {
    int i;
    if (issuedCount == 0) {
        printf("\nNo books are currently issued.\n");
        return;
    }
    printf("\n%-8s %-10s %-12s\n", "BOOKID", "MEMBERID", "ISSUEDATE");
    printf("---------------------------------------\n");
    for (i = 0; i < issuedCount; i++) {
        printf("%-8d %-10d %-12s\n", issuedBooks[i].bookId, issuedBooks[i].memberId,
               issuedBooks[i].issueDate);
    }
    printf("Total Issued: %d\n", issuedCount);
}

/* ================= FILE PERSISTENCE ================= */
void saveBooks(void) {
    FILE *fp = fopen("books.dat", "wb");
    if (fp == NULL) return;
    fwrite(&bookCount, sizeof(int), 1, fp);
    fwrite(books, sizeof(struct Book), bookCount, fp);
    fclose(fp);
}

int loadBooks(void) {
    FILE *fp = fopen("books.dat", "rb");
    if (fp == NULL) return 0;
    fread(&bookCount, sizeof(int), 1, fp);
    fread(books, sizeof(struct Book), bookCount, fp);
    fclose(fp);
    return bookCount;
}

void saveMembers(void) {
    FILE *fp = fopen("members.dat", "wb");
    if (fp == NULL) return;
    fwrite(&memberCount, sizeof(int), 1, fp);
    fwrite(members, sizeof(struct Member), memberCount, fp);
    fclose(fp);
}

int loadMembers(void) {
    FILE *fp = fopen("members.dat", "rb");
    if (fp == NULL) return 0;
    fread(&memberCount, sizeof(int), 1, fp);
    fread(members, sizeof(struct Member), memberCount, fp);
    fclose(fp);
    return memberCount;
}

void saveIssuedBooks(void) {
    FILE *fp = fopen("issued.dat", "wb");
    if (fp == NULL) return;
    fwrite(&issuedCount, sizeof(int), 1, fp);
    fwrite(issuedBooks, sizeof(struct IssuedBook), issuedCount, fp);
    fclose(fp);
}

int loadIssuedBooks(void) {
    FILE *fp = fopen("issued.dat", "rb");
    if (fp == NULL) return 0;
    fread(&issuedCount, sizeof(int), 1, fp);
    fread(issuedBooks, sizeof(struct IssuedBook), issuedCount, fp);
    fclose(fp);
    return issuedCount;
}

/* ================= MAIN ================= */
int main(void) {
    if (login() != 1) {
        return 0;
    }

    loadBooks();
    loadMembers();
    loadIssuedBooks();

    int choice, running = 1;
    while (running) {
        mainMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:  addBook();            break;
            case 2:  deleteBook();         break;
            case 3:  searchBook();         break;
            case 4:  displayAllBooks();    break;
            case 5:  addMember();          break;
            case 6:  deleteMember();       break;
            case 7:  displayAllMembers();  break;
            case 8:  issueBook();          break;
            case 9:  returnBook();         break;
            case 10: displayIssuedBooks(); break;
            case 0:
                running = 0;
                printf("Exiting the program. Goodbye!\n");
                break;
            default:
                printf("Invalid option. Please try again.\n");
        }
    }
    return 0;
}

 