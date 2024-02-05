#include "checker.h"

/**************************************************/
const char* script_path = "/home/cy102l/find_occurances.sh";
const char* data_file = "/opt/random-data.txt";
/**************************************************/

int get_count() {
    FILE *file;
    char line[4096];
    int counter = 0;

    file = fopen(data_file, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    while (fgets(line, sizeof(line), file) != NULL) {
        char *token = strtok(line, " \t\n");

        while (token != NULL) {
            if (strlen(token) == 3) {
                counter++;
            }
            token = strtok(NULL, " \t\n");
        }
    }

    fclose(file);
    return counter;
}


void logger(int msgCode, enum Mode mode) {
    printf("\t");
    switch(msgCode) {
        case 11:
            PRINT("File %s exists", script_path);
            break;
        case 12:
            PRINT("File %s has execution permissions", script_path);
            break;
        case 13:
            PRINT("Script reads in data from %s", data_file);
            break;
        case 14:
            PRINT("Script makes use of `read` command");
            break;
        case 15:
            PRINT("Script gives correct output: (%d)", get_count());
            break;
    }
}

int main(int argc, char* argv[]) {

    int done = -1;
    setuid(0);
    setgid(0);

    printf("=> \e[4mQuestion 4\033[0m:\n");
    if(!isfile(script_path)) {
        logger(11, ERROR);
    } else {
        logger(11, SUCCESS); ++done;
    }

    if(!hasexecutionperms(script_path)) {
        logger(12, ERROR);
    } else {
        logger(12, SUCCESS); ++done;
    }

    if(!file_contains(script_path, data_file)) {
        logger(13, ERROR);
    } else {
        logger(13, SUCCESS); ++done;
    }
    
    if(!file_contains(script_path, "read")) {
        logger(14, ERROR);
    } else {
        logger(14, SUCCESS); ++done;
    }

    char cmd[0xFF];
    char output[0xFF];
    char buf[10];
    sprintf(cmd, "%s 2>/dev/null", script_path);
    getcmdoutput(cmd, output, 0xFF);
    int rcv_count = atoi(output);

    if(rcv_count != get_count()) {
        logger(15, ERROR);
    } else {
        logger(15, SUCCESS); ++done;
    }

    if(done == 4) {
        printFlag();
    }

}
