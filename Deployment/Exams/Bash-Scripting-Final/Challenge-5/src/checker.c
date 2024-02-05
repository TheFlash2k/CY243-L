#include "checker.h"

/**************************************************/
const char* script_path = "/usr/share/even_odd.sh";
/**************************************************/

char* even_odd_str(int _v) {
    return ((_v % 2 == 0) ? "even" : "odd");
}

void testcase(int casenumber, int val, enum Mode mode) {
    printf("\t");
    PRINT("TEST-CASE: %d -> Value: %d [%s]", casenumber, val, even_odd_str(val))
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
            PRINT("Script takes data from command-line via argument i.e. $1");
            break;
        case 14:
            PRINT("Script performs check for even/odd using %%");
            break;
    }
}

int main(int argc, char* argv[]) {

    int done = -1;
    srand(time(NULL));
    setuid(0);
    setgid(0);

    printf("=> \e[4mQuestion 5\033[0m:\n");
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

    if(!file_contains(script_path, "$1")) {
        logger(13, ERROR);
    } else {
        logger(13, SUCCESS); ++done;
    }

    if(!file_contains(script_path, "%")) {
        logger(14, ERROR);
    } else {
        logger(14, SUCCESS); ++done;
    }

    char cmd[0xFF];
    char output[0xFF];
    char buf[10];
    int rnd = -1;

    for(int i = 0; i < 5; ++i) {
        rnd = rand() % 150;
        sprintf(cmd, "%s %d 2>/dev/null", script_path, rnd);
        getcmdoutput(cmd, output, 0xFF);
        if(strcmp(output, even_odd_str(rnd)) == 0) {
            testcase(i+1, rnd, SUCCESS); ++done;
        } else {
            testcase(i+1, rnd, ERROR);
        }
    }

    if(done == 8) {
        printFlag();
    }

}