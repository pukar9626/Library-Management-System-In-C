#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main(){
    if(login() == 1){
        printf("Welcome to the Library Management System!\n");
    }
    return 0;
}
