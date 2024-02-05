#include "checker.h"

/**************************************************/
const char* username = "ashfaq";
const char* user_dir = "/usr/share/ashfaq";
const char* user_shell = "/bin/bash";
const char* script_path = "/home/cy102l/question-1/q1.sh";
/**************************************************/

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
            PRINT("Script creates a new user called %s (case-sensitive)", username);
            break;
        case 14:
            PRINT("The new user, %s has the home dir %s", username, user_dir);
            break;
        case 15:
            PRINT("The new user, %s has the shell set to %s", username, user_shell);
            break;
    }
}


void cleanup() {
    system("userdel -r ashfaq 2>/dev/null");
    system("groupdel ashfaq 2>/dev/null");
    system("rm -rf /usr/share/ashfaq 2>/dev/null");
}

int main(int argc, char* argv[]) {

    int done = -1;
    setuid(0);
    setgid(0);

    printf("=> \e[4mQuestion 1\033[0m:\n");
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

    cleanup(); // important
    execscript(script_path); // invoking the script...

    if(!isuser(username)) {
        logger(13, ERROR);
    } else {
        logger(13, SUCCESS); ++done;
    }

    if(!checkuserdir(username, user_dir)) {
        logger(14, ERROR);
    }
    else {
        logger(14, SUCCESS); ++done;
    }

    if(!checkusershell(username, user_shell)) {
        logger(15, ERROR);
    }
    else {
        logger(15, SUCCESS); ++done;
    }

    if(done == 4) {
        printFlag();
    }

    cleanup();
}
