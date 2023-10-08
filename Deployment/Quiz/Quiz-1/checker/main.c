#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

// Some macros to log to stdout...
enum Mode { SUCCESS, ERROR };
#define PASS(msg, ...) { if(mode == SUCCESS) { printf("[\033[0;32mPASSED\033[0m] "); printf(msg, ##__VA_ARGS__); printf("\n");}}
#define FAIL(msg, ...) { if(mode == ERROR) { printf("[\033[0;31mFAILED\033[0m] "); printf(msg, ##__VA_ARGS__); printf("\n");} }
#define DEBUG(msg, ...) { printf("[\033[0;33mDEBUG\033[0m] "); printf(msg, ##__VA_ARGS__); printf("\n"); }
#define PRINT(msg, ...) { PASS(msg, ##__VA_ARGS__); FAIL(msg, ##__VA_ARGS__); } // VERY BAAAAAAAAAD CODING

//  ======== Global vars ========
const char* userName = "new-user";
const char* shell = "/bin/sh";
const char* homeDir = "/tmp/new-user";
const char* group = "au-admins";
const char* file = "/tmp/my-file";
const char* userOwnedBy = "kali";
// =============================

void logger(int msgCode, enum Mode mode) {
    printf("\t");
    switch(msgCode) {
        case 11:
            PRINT("User %s is created", userName);
            break;
        case 12:
            PRINT("User %s shell is %s", userName, shell);
            break;
        case 13:
            PRINT("User %s home directory is %s", userName, homeDir);
            break;
        case 14:
            PRINT("Group %s is created", group);
            break;
        case 15:
            PRINT("User %s is in group %s", userName, group);
            break;
        case 21:
            PRINT("%s exists", file);
            break;
        case 22:
            PRINT("%s has some content", file);
            break;
        case 23:
            PRINT("%s is owned by %s", file, userOwnedBy);
            break;
        case 24:
            PRINT("%s is group owned by %s", file, group);
            break;
        case 25:
            PRINT("%s has the correct permissions (rw- r-- ---)", file);
            break;
        case 31:
            PRINT("/tmp/get-ip.sh exists");
            break;
        case 32:
            PRINT("/tmp/get-ip.sh has execution permissions");
            break;
        case 33:
            PRINT("Interface \"lo\" produces 127.0.0.1 as the result from /tmp/get-ip.sh");
            break;
        default:
            printf("Unknown message code: %d\n", msgCode);
    }
}

void question_1() {

    /* Handles for Password */
    struct passwd *pHandle;
    struct passwd *newUser = NULL;

    /* Handles for Groups */
    struct group *gHandle;
    struct group *newGroup = NULL;

    enum Mode gpMode = ERROR;

    while((pHandle = getpwent())) {
        if(strcmp(pHandle->pw_name, userName) == 0) {
            newUser = pHandle;
            break;
        }
    }

    while((gHandle = getgrent())) {
        if(strcmp(gHandle->gr_name, group) == 0) {
            newGroup = gHandle;
            break;
        }
    }

    gpMode = newGroup ? SUCCESS : ERROR;

    if(!newUser) {
        logger(11, ERROR); logger(12, ERROR); logger(13, ERROR); logger(14, gpMode); logger(15, ERROR);
    } else {
        logger(11, SUCCESS);
        if(strcmp(newUser->pw_shell, shell) == 0) {
            logger(12, SUCCESS);
        } else {
            logger(12, ERROR);
        }

        if(strcmp(newUser->pw_dir, homeDir) == 0) {
            logger(13, SUCCESS);
        } else {
            logger(13, ERROR);
        }

        logger(14, gpMode);

        bool _ = false;
        if(gpMode == SUCCESS) {
            bool found = false;
            for(int i = 0; newGroup->gr_mem[i] != NULL; i++) {
                if(strcmp(newGroup->gr_mem[i], userName) == 0) {
                    found = true;
                    break;
                }
            }
            if(found) {
                logger(15, SUCCESS);
                _ = true;
            }
        }
        if(!_) {
            logger(15, ERROR);
        }
    }
    
}

void question_2() {

    FILE *fileHandle;
    struct stat file_stat;
    char permissions[22];
    bool perms = false;

    if (fileHandle = fopen(file, "r")) {
        logger(21, SUCCESS);
        // Fill the character array with the file permissions in "rwx rw rw" format
        if (stat(file, &file_stat) == 0) {
            snprintf(permissions, sizeof(permissions), "%c%c%c %c%c%c %c%c%c",
                (file_stat.st_mode & S_IRUSR) ? 'r' : '-',
                (file_stat.st_mode & S_IWUSR) ? 'w' : '-',
                (file_stat.st_mode & S_IXUSR) ? 'x' : '-',
                (file_stat.st_mode & S_IRGRP) ? 'r' : '-',
                (file_stat.st_mode & S_IWGRP) ? 'w' : '-',
                (file_stat.st_mode & S_IXGRP) ? 'x' : '-',
                (file_stat.st_mode & S_IROTH) ? 'r' : '-',
                (file_stat.st_mode & S_IWOTH) ? 'w' : '-',
                (file_stat.st_mode & S_IXOTH) ? 'x' : '-'
            );
            perms = true;
        }

        fseek(fileHandle, 0, SEEK_END);
        if (ftell(fileHandle) == 0) {
            logger(22, ERROR);
        } else {
            logger(22, SUCCESS);
        }
        fclose(fileHandle);
    } else {
        logger(21, ERROR);
        logger(22, ERROR);
    }

    struct stat fs;
    if(stat(file, &fs) >= 0) {
        struct passwd *pHandle = getpwuid(fs.st_uid);
        struct group *gHandle  = getgrgid(fs.st_gid);
        if(strcmp(pHandle->pw_name, userOwnedBy) == 0) {
            logger(23, SUCCESS);
        } else {
            logger(23, ERROR);
        }
        if(strcmp(gHandle->gr_name, group) == 0) {
            logger(24, SUCCESS);
        } else {
            logger(24, ERROR);
        }
        
    }
    else {
        logger(23, ERROR);
        logger(24, ERROR);
    }
    if(perms && strcmp(permissions, "rw- r-- ---") == 0) { logger(25, SUCCESS); } else { logger(25, ERROR); }
}

void question_3() {
    
    const char* script = "/tmp/get-ip.sh";
    const char* iface = "lo";
    char command[256];
    snprintf(command, sizeof(command), "%s %s", script, iface);

    char buffer[128];
    char* result = NULL;
    size_t result_size = 0;
    FILE* pipe;

    if(access(script, F_OK) != -1) {
        logger(31, SUCCESS);
    } else {
        logger(31, ERROR);
    }

    bool _exec = false;
    if(access(script, X_OK) != -1) {
        logger(32, SUCCESS);
        _exec = true;
    } else {
        logger(32, ERROR);
    }

    if(_exec) {
        pipe = popen(command, "r");
        if (!pipe) {
            perror("An Error occured in opening pipe. Please contact your teacher.");
            exit(1);
        }
        memset(buffer, 0, sizeof(buffer));
        while (fgets(buffer, sizeof(buffer), pipe) != NULL) {}
        pclose(pipe);
        if(strcmp(buffer, "127.0.0.1\n") == 0 || strcmp(buffer, "127.0.0.1") == 0) {
            logger(33, SUCCESS);
        } else {
            logger(33, ERROR);
            DEBUG("Script produced result: %s", buffer);
        }
    }
    else {
        logger(33, ERROR);
    }

    free(result);
}

int main(int argc, char* argv[]) {

    printf("=> \e[4mQuestion 1\033[0m:\n");
    question_1();

    printf("\n=> \e[4mQuestion 2\033[0m:\n");
    question_2();

    printf("\n=> \e[4mQuestion 3\033[0m:\n");
    question_3();

    return 0;
}