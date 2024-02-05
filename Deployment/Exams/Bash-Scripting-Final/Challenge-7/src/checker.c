#include "checker.h"

/**************************************************/
const char* env = "ashfaq";
const char* env_val = "nadeem";
/**************************************************/

void logger(int msgCode, enum Mode mode) {
    printf("\t");
    switch(msgCode) {
        case 11:
            PRINT("Environment variable %s set", env);
            break;
        case 12:
            PRINT("env %s has value %s", env, env_val);
            break;
    }
}

int main(int argc, char* argv[]) {

    int done = -1;
    setuid(0);
    setgid(0);

    printf("=> \e[4mQuestion 7\033[0m:\n");
    
    char* _env = getenv("ashfaq");

    if(!_env) {
        logger(11, ERROR);
    }
    else {
        logger(11, SUCCESS); ++done;
    }

    if(_env && strcmp(_env, env_val) == 0) {
        logger(12, SUCCESS); ++done;
    } else {
        logger(12, ERROR);
    }

    if(done == 1) {
        printFlag();
    }

}

