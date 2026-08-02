#ifndef LIBRARY_H
#define LIBRARY_H

#define MAX_RECORDS   100
#define MAX_ID_LEN    16
#define MAX_LEN       100

typedef struct {
    char id[MAX_ID_LEN];
    char title[MAX_LEN];
    char author[MAX_LEN];
    char isbn[MAX_LEN];
    char category[MAX_LEN];
    char type[MAX_LEN];
    char status[20];       /* "Available" or "Issued" */
} Book;

typedef struct {
    char id[MAX_ID_LEN];
    char name[MAX_LEN];
    char phone[20];
} Member;

typedef struct {
    char bookId[MAX_ID_LEN];
    char memberId[MAX_ID_LEN];
    char issueDate[16];
    char dueDate[16];
} IssuedBook;

/* Shared in-memory tables, defined in file_handling.c */
extern Book books[MAX_RECORDS];
extern int bookCount;

extern Member members[MAX_RECORDS];
extern int memberCount;

extern IssuedBook issued[MAX_RECORDS];
extern int issuedCount;

/* file_handling.c */
void readLine(char *buffer, int size);
void save_books(void);
void load_books(void);
void save_members(void);
void load_members(void);
void save_issued(void);
void load_issued(void);
void pauseScreen(void);
void clearScreen(void);
int  getValidInt(int min, int max);

/* main.c */
int  findBookIndex(const char *id);
int  findMemberIndex(const char *id);

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

#endif
