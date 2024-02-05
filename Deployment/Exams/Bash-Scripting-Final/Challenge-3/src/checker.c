#include "checker.h"

/**************************************************/
const char* script_path = "/home/cy102l/ip-checker.sh";
char eth0_ip[0x20];
char lo_ip[0x20];
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
            PRINT("Script takes data from command-line via argument i.e. $1");
            break;
        case 14:
            PRINT("Script gives correct output when eth0 is passed as input (%s)", eth0_ip);
            break;
        case 15:
            PRINT("Script gives correct output when lo is passed as input (%s)", lo_ip);
            break;
    }
}

int main(int argc, char* argv[]) {

    int done = -1;
    setuid(0);
    setgid(0);

    getipofinterface("eth0", eth0_ip);
    getipofinterface("lo", lo_ip);

    printf("=> \e[4mQuestion 3\033[0m:\n");
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
    
    if(!file_contains(script_path, "ifconfig")) {
        logger(14, ERROR);
        logger(15, ERROR);
        return;
    }

    char cmd_eth0[0xFF]; char output_eth0[0xFF];
    char cmd_lo[0xFF];   char output_lo[0xFF];
    sprintf(cmd_eth0, "%s eth0 2>/dev/null", script_path);
    sprintf(cmd_lo, "%s lo 2>/dev/null", script_path);

    getcmdoutput(cmd_eth0, output_eth0, 0xFF);
    getcmdoutput(cmd_lo, output_lo, 0xFF);

    if(strcmp(eth0_ip, output_eth0)) {
        logger(14, ERROR);
    } else {
        logger(14, SUCCESS); ++done;
    }

    if(strcmp(lo_ip, output_lo)) {
        logger(15, ERROR);
    } else {
        logger(15, SUCCESS); ++done;
    }

    if(done == 4) {
        printFlag();
    }

}
