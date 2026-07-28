#include <stdio.h>
#include <stdlib.h>
struct Book {
    int id;
    char title[100];
    char author[100];
    int isIssued;   
};
struct Member {
    int id;
    char name[100];
    char phone[20];
};
struct IssuedBook {
    int bookId;
    int memberId;
    char issueDate[11];   
    char dueDate[11];
};
void saveBooks(struct Book books[], int count) {
    FILE *fp = fopen("books.dat", "wb");
    if (fp == NULL) {
        printf("Error: could not open file for saving.\n");
        return;
    }

    fwrite(&count, sizeof(int), 1, fp);      
    fwrite(books, sizeof(struct Book), count, fp);  

    fclose(fp);
    printf("Books saved successfully.\n");
}
int loadBooks(struct Book books[]) {
    FILE *fp = fopen("books.dat", "rb");
    if (fp == NULL) {
        printf("No saved books found.\n");
        return 0;   
    }

    int count;
    fread(&count, sizeof(int), 1, fp);       
    fread(books, sizeof(struct Book), count, fp);  
    fclose(fp);
    printf("Books loaded successfully.\n");
    return count;   
}void saveMembers(struct Member members[], int count) {
    FILE *fp = fopen("members.dat", "wb");
    if (fp == NULL) {
        printf("Error: could not open file for saving.\n");
        return;
    }

    fwrite(&count, sizeof(int), 1, fp);
    fwrite(members, sizeof(struct Member), count, fp);

    fclose(fp);
    printf("Members saved successfully.\n");
}
int loadMembers(struct Member members[]) {
    FILE *fp = fopen("members.dat", "rb");
    if (fp == NULL) {
        printf("No saved members found.\n");
        return 0;
    }

    int count;
    fread(&count, sizeof(int), 1, fp);
    fread(members, sizeof(struct Member), count, fp);

    fclose(fp);
    printf("Members loaded successfully.\n");
    return count;
}
void saveIssuedBooks(struct IssuedBook issued[], int count) {
    FILE *fp = fopen("issued.dat", "wb");
    if (fp == NULL) {
        printf("Error: could not open file for saving.\n");
        return;
    }

    fwrite(&count, sizeof(int), 1, fp);
    fwrite(issued, sizeof(struct IssuedBook), count, fp);

    fclose(fp);
    printf("Issued books saved successfully.\n");
}
int loadIssuedBooks(struct IssuedBook issued[]) {
    FILE *fp = fopen("issued.dat", "rb");
    if (fp == NULL) {
        printf("No issued book records found.\n");
        return 0;
    }

    int count;
    fread(&count, sizeof(int), 1, fp);
    fread(issued, sizeof(struct IssuedBook), count, fp);

    fclose(fp);
    printf("Issued books loaded successfully.\n");
    return count;
}
void pauseScreen() {
    int dummy;
    printf("\nEnter any number to continue...");
    scanf("%d", &dummy);
}
void clearScreen() {
    system("cls");
}
int getValidInt(int min, int max) {
    int value;
    int result;

    do {
        printf("Enter a number between %d and %d: ", min, max);
        result = scanf("%d", &value);

        if (result != 1) {
            printf("Invalid input. Please enter a number.\n");
        } else if (value < min || value > max) {
            printf("Out of range. Try again.\n");
        }

    } while (result != 1 || value < min || value > max);

    return value;
}
int main() {
    struct Book books[100];
    int bookCount = 0;

    bookCount = loadBooks(books);
    printf("Currently have %d book(s) loaded.\n", bookCount);

    printf("Enter Book ID: ");
    scanf("%d", &books[bookCount].id);

    printf("Enter Book Title: ");
    scanf(" %[^\n]", books[bookCount].title);   // reads full line including spaces

    printf("Enter Book Author: ");
    scanf(" %[^\n]", books[bookCount].author);

    books[bookCount].isIssued = 0;   // new book starts as not issued
    bookCount++;

    saveBooks(books, bookCount);

    pauseScreen();
    clearScreen();

    struct Book loadedBooks[100];
    int loadedCount = loadBooks(loadedBooks);

    printf("\n--- Books loaded from file ---\n");
    for (int i = 0; i < loadedCount; i++) {
        printf("ID: %d | Title: %s | Author: %s | Issued: %s\n",
               loadedBooks[i].id,
               loadedBooks[i].title,
               loadedBooks[i].author,
               loadedBooks[i].isIssued ? "Yes" : "No");
    }

    return 0;
}