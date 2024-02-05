#include <stdio.h>

void win(void) {
    FILE *file;
    char line[100];
    file = fopen("/flag", "r");
    if (file == NULL) {
        puts("[FAIL] Contact an admin.\n");
        exit(1);
    }
    while (fgets(line, sizeof(line), file) != NULL) {
        puts(line);
    }
    fclose(file);
}

void vuln() {
	int isAdmin = 0;
	char buffer[25];
    char _admin;
	fflush(stdout);

    printf("Hi, are you an admin? (y/n)? ");
    fflush(stdout);
    scanf("%c", &_admin);

    if (_admin == 'y') {
        printf("Ok, you are an admin. What's the password? ");
        fflush(stdout);
        scanf("%s", buffer);
        if (isAdmin == 0xdeadc0de) {
            win();
        } else {
            printf("Sorry, you are not an admin.\n");
        }
    } else {
        printf("Ok, you are not an admin.\n");
    }
}

int main() {
    setbuf(stdin, NULL);
	setbuf(stdout, NULL);
	setbuf(stderr, NULL);
	vuln();
}