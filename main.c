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