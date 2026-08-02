#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"

/* ---- shared in-memory tables ---- */
Book books[MAX_RECORDS];
int bookCount = 0;

Member members[MAX_RECORDS];
int memberCount = 0;

IssuedBook issued[MAX_RECORDS];
int issuedCount = 0;

/* ---- input helper ---- */
void readLine(char *buffer, int size) {
    if (fgets(buffer, size, stdin) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
    } else {
        buffer[0] = '\0';
    }
}

/* ---- books ---- */
void save_books(void) {
    FILE *fp = fopen("books.dat", "wb");
    if (fp == NULL) {
        printf("Error: could not open file for saving.\n");
        return;
    }
    fwrite(&bookCount, sizeof(int), 1, fp);
    fwrite(books, sizeof(Book), bookCount, fp);
    fclose(fp);
}

void load_books(void) {
    FILE *fp = fopen("books.dat", "rb");
    if (fp == NULL) {
        bookCount = 0;
        return;
    }
    if (fread(&bookCount, sizeof(int), 1, fp) != 1) {
        bookCount = 0;
    } else {
        fread(books, sizeof(Book), bookCount, fp);
    }
    fclose(fp);
}

/* ---- members ---- */
void save_members(void) {
    FILE *fp = fopen("members.dat", "wb");
    if (fp == NULL) {
        printf("Error: could not open file for saving.\n");
        return;
    }
    fwrite(&memberCount, sizeof(int), 1, fp);
    fwrite(members, sizeof(Member), memberCount, fp);
    fclose(fp);
}

void load_members(void) {
    FILE *fp = fopen("members.dat", "rb");
    if (fp == NULL) {
        memberCount = 0;
        return;
    }
    if (fread(&memberCount, sizeof(int), 1, fp) != 1) {
        memberCount = 0;
    } else {
        fread(members, sizeof(Member), memberCount, fp);
    }
    fclose(fp);
}

/* ---- issued books ---- */
void save_issued(void) {
    FILE *fp = fopen("issued.dat", "wb");
    if (fp == NULL) {
        printf("Error: could not open file for saving.\n");
        return;
    }
    fwrite(&issuedCount, sizeof(int), 1, fp);
    fwrite(issued, sizeof(IssuedBook), issuedCount, fp);
    fclose(fp);
}

void load_issued(void) {
    FILE *fp = fopen("issued.dat", "rb");
    if (fp == NULL) {
        issuedCount = 0;
        return;
    }
    if (fread(&issuedCount, sizeof(int), 1, fp) != 1) {
        issuedCount = 0;
    } else {
        fread(issued, sizeof(IssuedBook), issuedCount, fp);
    }
    fclose(fp);
}

/* ---- misc utilities ---- */
void pauseScreen(void) {
    printf("\nPress Enter to continue...");
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

void clearScreen(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int getValidInt(int min, int max) {
    int value;
    int result;
    do {
        printf("Enter a number between %d and %d: ", min, max);
        result = scanf("%d", &value);
        while (getchar() != '\n') { }
        if (result != 1) {
            printf("Invalid input. Please enter a number.\n");
        } else if (value < min || value > max) {
            printf("Out of range. Try again.\n");
        }
    } while (result != 1 || value < min || value > max);
    return value;
}