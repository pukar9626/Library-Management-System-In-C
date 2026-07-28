#include <stdio.h>
int main(void) {
    int choice;

    do {
        printf("\n===== LIBRARY MENU =====\n");
        printf("1. Issue a book\n");
        printf("2. Return a book\n");
        printf("3. Display issued books\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("You chose ISSUE. (not built yet)\n");
                break;
            case 2:
                printf("You chose RETURN. (not built yet)\n");
                break;
            case 3:
                printf("You chose DISPLAY. (not built yet)\n");
                break;
            case 4:
                printf("Goodbye!\n");
                break;
            default:
                printf("Wrong choice! Type 1 to 4.\n");
        }

    } while (choice != 4);

    return 0;
}
#include <stdio.h>
#define MAX_BOOKS 1000

/* The blueprint for ONE borrowed book */
struct IssuedBook {
    char bookName[50];
    char studentName[50];
    char issueDate[15];
};

/* The actual storage: 1000 empty rows, and a counter */
struct IssuedBook issuedBooks[MAX_BOOKS];
int totalIssued = 0;

int main(void) {
    int choice;

    do {
        printf("\n===== LIBRARY MENU =====\n");
        printf("1. Issue a book\n");
        printf("2. Return a book\n");
        printf("3. Display issued books\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Issue is not built yet.\n");
                break;
            case 2:
                printf("Return is not built yet.\n");
                break;
            // case 2:
            //    returnBook();
            //     break;
            case 3:
                /* Proof that our counter exists! */
                printf("Books currently issued: %d\n", totalIssued);
                break;
            case 4:
                printf("Goodbye!\n");
                break;
            default:
                printf("Wrong choice! Type 1 to 4.\n");
        }

    } while (choice != 4);

    return 0;
}
// Issue and Display now really work.

#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 1000

struct IssuedBook {
    char bookName[50];
    char studentName[50];
    char issueDate[15];
};

struct IssuedBook issuedBooks[MAX_BOOKS];
int totalIssued = 0;

/* Write one new row into the array */
void issueBook(void) {
    if (totalIssued >= MAX_BOOKS) {
        printf("The record is full!\n");
        return;
    }

    printf("\n--- Issue a Book ---\n");

    printf("Enter book name: ");
    scanf("%s", issuedBooks[totalIssued].bookName);

    printf("Enter student name: ");
    scanf("%s", issuedBooks[totalIssued].studentName);

    printf("Enter issue date: ");
    scanf("%s", issuedBooks[totalIssued].issueDate);

    printf("Success! Book issued.\n");

    totalIssued++;   /* move to the next empty row */
}

/* Print every filled row */
void displayIssuedBooks(void) {
    int i;

    if (totalIssued == 0) {
        printf("\nNo books are currently issued.\n");
        return;
    }

    printf("\n--- Currently Issued Books ---\n");
    for (i = 0; i < totalIssued; i++) {
        printf("%d. %s | %s | %s\n",
               i + 1,
               issuedBooks[i].bookName,
               issuedBooks[i].studentName,
               issuedBooks[i].issueDate);
    }
    printf("Total: %d\n", totalIssued);
}
void returnBook(void) {
    int i, found = 0;
    char bookName[50];

    if (totalIssued == 0) {
        printf("\nNo books are currently issued.\n");
        return;
    }

    printf("\n--- Return a Book ---\n");
    printf("Enter book name to return: ");
    scanf("%s", bookName);

    for (i = 0; i < totalIssued; i++) {
        if (strcmp(bookName, issuedBooks[i].bookName) == 0) {

            int j;
            for (j = i; j < totalIssued - 1; j++) {
                issuedBooks[j] = issuedBooks[j + 1];
            }

            totalIssued--;
            found = 1;

            printf("Book returned successfully!\n");
            break;
        }
    }

    if (!found) {
        printf("Book not found.\n");
    }
}
int main(void) {
    int choice;

    do {
        printf("\n===== LIBRARY MENU =====\n");
        printf("1. Issue a book\n");
        printf("2. Return a book\n");
        printf("3. Display issued books\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: issueBook();           break;
            case 2: printf("Not built yet.\n"); break;
            case 3: displayIssuedBooks();  break;
            case 4: printf("Goodbye!\n");  break;
            default: printf("Wrong choice!\n");
        }

    } while (choice != 4);

    return 0;
}
