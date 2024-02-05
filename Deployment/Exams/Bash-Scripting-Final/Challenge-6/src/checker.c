#include "checker.h"

/**************************************************/
const char* script_path = "/usr/share/looper.sh";
const char* out_file = "/opt/data.log";
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
            PRINT("Script takes data from command-line via argument i.e. $1 and $2");
            break;
        case 14:
            PRINT("Script performs check for even/odd using %%");
            break;
        case 15:
            PRINT("Script makes use of `for` and `seq` keywords");
            break;
        case 16:
            PRINT("Script stores output in %s", out_file);
            break;
        case 17:
            PRINT("%s contains the correct output", out_file);
            break;
    }
}

void cleanup() {
    system("rm -f /opt/data.log 2>/dev/null");
}

int main(int argc, char* argv[]) {

    int done = -1;
    srand(time(NULL));
    setuid(0);
    setgid(0);

    printf("=> \e[4mQuestion 6\033[0m:\n");
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

    if(!file_contains(script_path, "$1") || !file_contains(script_path, "$2") ) {
        logger(13, ERROR);
    } else {
        logger(13, SUCCESS); ++done;
    }

    if(!file_contains(script_path, "%")) {
        logger(14, ERROR);
    } else {
        logger(14, SUCCESS); ++done;
    }

    if(!file_contains(script_path, "for") || !file_contains(script_path, "seq")) {
        logger(15, ERROR);
    } else {
        logger(15, SUCCESS); ++done;
    }

    int loop_begin = rand() % 100;
    int loop_end = loop_begin + rand() % 50;
    char cmd[0xFF];
    char output[0xFF];

    sprintf(cmd, "%s %d %d 2>/dev/null", script_path, loop_begin, loop_end);
    getcmdoutput(cmd, output, 0xFF);

    if(!isfile(out_file)) {
        logger(16, ERROR);
    } else {
        logger(16, SUCCESS); ++done;
    }

    FILE* fp = fopen(out_file, "r");
    if(fp == NULL) {
        logger(17, ERROR);
        return 0;
    }

    char line[10];
    int curr = loop_begin;
    enum Mode mode;
    bool success = true;
    while(fgets(line, sizeof(line), fp) != NULL) {
        char chk[10];
        line[strcspn(line, "\n")] = 0;
        line[strcspn(line, " ")] = 0;
        sprintf(chk, "%d:%s", curr, even_odd_str(curr));
        if(strcmp(chk, line) != 0) {
            mode = ERROR;
            PRINT("Test-case failed: %s", line);
            success = false;
            break;
        }
        ++curr;
    }

    if(curr < loop_end) {
        logger(17, ERROR);
    }
    else {
        logger(17, SUCCESS);
    }

    if(success) {
        printFlag();
    }
    cleanup();
}