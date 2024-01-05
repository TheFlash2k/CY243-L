#include <stdio.h>
#include <stdlib.h>

void call_my_function(void) {
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
    int allowed = 0;
    char buffer[50];
    printf("Hello, my name is Ali, what is yours? ");
    gets(buffer);
    printf(buffer); // :)
}

int main() {
    setbuf(stdin, NULL);
	setbuf(stdout, NULL);
	setbuf(stderr, NULL);
    vuln();
}