#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    setuid(0);
    setgid(0);

    printf("I have a simple program that can do the following: ");
    printf("1. Show the current time\n");
    printf("2. Show the current date\n");
    
    printf("What would you like to do? (1 or 2): ");
    int choice;

    scanf("%d", &choice);

    if (choice == 1) {
        system("date +%T");
    } else if (choice == 2) {
        system("date +%D");
    } else {
        printf("Invalid choice!\n");
    }
}