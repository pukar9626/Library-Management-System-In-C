struct IssuedBook {
    int  bookId;             /* matches Member 1's book id   */
    char bookName[50];
    int  memberId;           /* matches Member 2's member id */
    char studentName[50];
    char issueDate[15];      /* dd-mm-yyyy */
};
 
struct IssuedBook issuedBooks[MAX_ISSUED];
int totalIssued = 0;
 
 
/* ---------- Issue a book ---------- */
 
void issueBook(void) {
 
    if (totalIssued >= MAX_ISSUED) {
        printf("\nThe issue record is full. Cannot issue more books.\n");
        return;
    }
 
    printf("\n--- Issue a Book ---\n");
 
    printf("Enter book ID     : ");
    scanf("%d", &issuedBooks[totalIssued].bookId);
 
    printf("Enter book name   : ");
    scanf("%49s", issuedBooks[totalIssued].bookName);
 
    printf("Enter member ID   : ");
    scanf("%d", &issuedBooks[totalIssued].memberId);
 
    printf("Enter student name: ");
    scanf("%49s", issuedBooks[totalIssued].studentName);
 
    printf("Enter issue date  : ");
    scanf("%14s", issuedBooks[totalIssued].issueDate);
 
    totalIssued++;
 
    printf("Done. Book issued successfully.\n");
}
 
 
/* ---------- Return a book ---------- */
 
void returnBook(void) {
    char bookName[50];
    int i, j;
    int found = 0;
 
    if (totalIssued == 0) {
        printf("\nNo books are issued right now.\n");
        return;
    }
 
    printf("\n--- Return a Book ---\n");
    printf("Enter book name to return: ");
    scanf("%49s", bookName);
 
    for (i = 0; i < totalIssued; i++) {
 
        if (strcmp(bookName, issuedBooks[i].bookName) == 0) {
 
            printf("'%s' returned by %s. Thank you!\n",
                   issuedBooks[i].bookName, issuedBooks[i].studentName);
 
            /* move every record after this one back by one position */
            for (j = i; j < totalIssued - 1; j++) {
                issuedBooks[j] = issuedBooks[j + 1];
            }
 
            totalIssued--;
            found = 1;
            break;
        }
    }
 
    if (!found) {
        printf("That book is not in the issued list.\n");
    }
}
 
 
/* ---------- Display all issued books ---------- */
 
void displayIssuedBooks(void) {
    int i;
 
    if (totalIssued == 0) {
        printf("\nNo books are currently issued.\n");
        return;
    }
 
    printf("\n--- Currently Issued Books ---\n");
    printf("%-4s %-6s %-20s %-8s %-16s %-12s\n",
           "SN", "BOOKID", "BOOK NAME", "MEMBID", "STUDENT", "DATE");
 
    for (i = 0; i < totalIssued; i++) {
        printf("%-4d %-6d %-20s %-8d %-16s %-12s\n",
               i + 1,
               issuedBooks[i].bookId,
               issuedBooks[i].bookName,
               issuedBooks[i].memberId,
               issuedBooks[i].studentName,
               issuedBooks[i].issueDate);
    }
 
    printf("Total issued: %d\n", totalIssued);
}