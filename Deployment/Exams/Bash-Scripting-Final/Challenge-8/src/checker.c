#include "checker.h"

/**************************************************/
const char* script_path = "/opt/test";
const char* perm_set = "537";
/**************************************************/

void logger(int msgCode, enum Mode mode) {
    printf("\t");
    switch(msgCode) {
        case 11:
            PRINT("File %s exists", script_path);
            break;
        case 12:
            PRINT("File %s has the correct permission set", script_path);
            break;
    }
}

bool check_perms(char* file, char* perm) {
    char cmd[0xFF];
    char output[0xFF];
    sprintf(cmd, "stat -c \"%%a\" %s 2>/dev/null", file);
    getcmdoutput(cmd, output, 0xFF);
    return (strcmp(output, perm) == 0);
}


int main(int argc, char* argv[]) {

    int done = -1;
    setuid(0);
    setgid(0);

    printf("=> \e[4mQuestion 8\033[0m:\n");
    
    if(!isfile(script_path)) {
        logger(11, ERROR);
    } else {
        logger(11, SUCCESS); ++done;
    }

    if(check_perms(script_path, perm_set)) {
        logger(12, SUCCESS); ++done;
    } else {
        logger(12, ERROR);
    }

    if(done == 1) {
        printFlag();
    }

}

