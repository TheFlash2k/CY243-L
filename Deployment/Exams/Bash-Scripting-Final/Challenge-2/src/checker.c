#include "checker.h"

/**************************************************/
const char* username1 = "ashfaq";
const char* username2 = "bajwa";
const char* gp_1 = "cats";
const char* gp_2 = "goats";
const char* script_path = "/opt/q2.sh";
const char* new_file = "/opt/posted";
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
            PRINT("Script creates a group called %s (case-sensitive)", gp_1);
            break;
        case 14:
            PRINT("Adds %s to %s and sudo", username1, gp_1);
            break;
        case 15:
            PRINT("Creates a new user %s", username2);
            break;
        case 16:
            PRINT("Adds %s to %s", username2, gp_1);
            break;
        case 17:
            PRINT("Creates another group called %s", gp_2);
            break;
        case 18:
            PRINT("Adds %s to %s", username1, gp_2);
            break;
        case 19:
            PRINT("Creates a new file called %s", new_file);
            break;
        case 20:
            PRINT("%s contains your roll number", new_file);
            break;
        case 21:
            PRINT("%s is user-owned by %s and group-owned by %s", new_file, username2, gp_2);
            break;
    }
}

void cleanup() {
    system("userdel -r bajwa 1>&2 2>/dev/null");
    system("groupdel bajwa 1>&2 2>/dev/null");
    system("groupdel cats 1>&2 2>/dev/null");
    system("groupdel goats 1>&2 2>/dev/null");
    system("gpasswd -d ashfaq cats 1>&2 2>/dev/null");
    system("gpasswd -d ashfaq goats 1>&2 2>/dev/null");
    system("gpasswd -d bajwa cats 1>&2 2>/dev/null");
    system("rm -f /opt/posted 1>&2 2>/dev/null");
}

int main(int argc, char* argv[]) {

    int done = -1;
    setuid(0);
    setgid(0);

    printf("=> \e[4mQuestion 2\033[0m:\n");
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

    if(!isgroup(gp_1)) {
        logger(13, ERROR);
    } else {
        logger(13, SUCCESS); ++done;
    }
    
    if(!isuseringroup(username1, gp_1) || !isuseringroup(username1, "sudo")) {
        logger(14, ERROR);
    } else {
        logger(14, SUCCESS); ++done;
    }

    if(!isuser(username2)) {
        logger(15, ERROR);
    } else {
        logger(15, SUCCESS); ++done;
    }

    if(!isuseringroup(username2, gp_1)) {
        logger(16, ERROR);
    } else {
        logger(16, SUCCESS); ++done;
    }

    if(!isgroup(gp_2)) {
        logger(17, ERROR);
    } else {
        logger(17, SUCCESS); ++done;
    }

    if(!isuseringroup(username1, gp_2)) {
        logger(18, ERROR);
    } else {
        logger(18, SUCCESS); ++done;
    }

    if(!isfile(new_file)) {
        logger(19, ERROR);
    } else {
        logger(19, SUCCESS); ++done;
    }

    if(!file_contains(new_file, "23")) {
        logger(20, ERROR);
    } else {
        logger(20, SUCCESS); ++done;
    }

    if(!fileownedbyuser(new_file, username2) || !fileownedbygroup(new_file, gp_2)) {
        logger(21, ERROR);
    } else {
        logger(21, SUCCESS); ++done;
    }

    if(done == 10) {
        printFlag();
    }

    cleanup();
}
