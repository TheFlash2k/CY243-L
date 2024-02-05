#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>

enum Mode { SUCCESS, ERROR };
#define PASS(msg, ...) { if(mode == SUCCESS) { printf("[\033[0;32mPASSED\033[0m] "); printf(msg, ##__VA_ARGS__); printf("\n");}}
#define FAIL(msg, ...) { if(mode == ERROR) { printf("[\033[0;31mFAILED\033[0m] "); printf(msg, ##__VA_ARGS__); printf("\n");} }
#define DEBUG(msg, ...) { printf("[\033[0;33mDEBUG\033[0m] "); printf(msg, ##__VA_ARGS__); printf("\n"); }
#define PRINT(msg, ...) { PASS(msg, ##__VA_ARGS__); FAIL(msg, ##__VA_ARGS__); } // VERY BAAAAAAAAAD CODING

// Make a simple get request to the server:
void printFlag() {
    char* chal_id = getenv("CHAL_ID");
    if (chal_id == NULL) {
        printf("CHAL_ID not set\n");
        return;
    }
    char *team_id = getenv("TEAM_ID");
    if (team_id == NULL) {
        printf("TEAM_ID not set\n");
        return;
    }

    char url[0xFF];
    char cmd[0xFF];
    char base[] = { 0x68,0x74,0x74,0x70,0x3a,0x2f,0x2f,0x31,0x37,0x32,0x2e,0x31,0x37,0x2e,0x30,0x2e,0x31,0x3a,0x39,0x35,0x31,0x32,0x2f,0x66,0x6c,0x61,0x67,0x00 };
    sprintf(url, "%s?chal_id=%s&team_id=%s", base, chal_id, team_id);
    printf("\033[0;32mGood job!\033[0m.");
    sprintf(cmd, "_s -sL \'%s\'; echo", url);
    int _s = system(cmd);
    if (_s == -1) {
        printf("[0;31mERROR\033[0m - Did not successfully exit.");
        exit(-1);
    }
}

bool isfile(char* path) {
    struct stat st;
    if (stat(path, &st) == -1) {
        return false;
    }
    return S_ISREG(st.st_mode);
}

bool file_contains(char* file, char* str) {
    char buf[0xFF];
    int fd = open(file, O_RDONLY);
    if (fd == -1) {
        return false;
    }
    while (read(fd, buf, 0xFF) != 0) {
        if (strstr(buf, str) != NULL) {
            return true;
        }
    }
    return false;
}

bool isuser(char* username) {
    return getpwnam(username) != NULL;
}

bool isgroup(char* groupname) {
    return getgrnam(groupname) != NULL;
}

bool isuseringroup(const char* username, const char* groupname) {
    bool _ret = false;
    struct passwd *pw = getpwnam(username);
    if (pw == NULL) {
        return _ret;
    }
    struct group *gr = getgrnam(groupname);
    if (gr == NULL) {
        return _ret;
    }
    gid_t *groups = pw->pw_gid;
    if(groups == NULL) {
        return _ret;
    }
    
    int ngroups = 0;
    gid_t *grouplist = NULL;
    if (getgrouplist(username, pw->pw_gid, grouplist, &ngroups) == -1) {
        grouplist = malloc(ngroups * sizeof(gid_t));
        if (getgrouplist(username, pw->pw_gid, grouplist, &ngroups) == -1) {
            return _ret;
        }
    }
    for (int i = 0; i < ngroups; i++) {
        if (grouplist[i] == gr->gr_gid) {
            _ret = true;
            break;
        }
    }
    return _ret;
}

bool hasbadstrings(const char* file) {
    if(!isfile(file)) {
        return false;
    }
    return (
        file_contains(file, "|bash") || 
        file_contains(file, "|sh") ||
        file_contains(file, "sh;") ||
        file_contains(file, "bash;") ||
        file_contains(file, "sh&") ||
        file_contains(file, "bash&") ||
        file_contains(file, "sh&&") ||
        file_contains(file, "bash&&") ||
        file_contains(file, "sh||") ||
        file_contains(file, "bash||") ||
        file_contains(file, "sh ") ||
        file_contains(file, "bash ")
    );
}

bool exec(char* cmd) {
    char buffer[0xFF];
    sprintf(buffer, "\"%s\" 2>&1 1>/dev/null </dev/null", cmd);
    return system(buffer) == 0;
}

bool execscript(char* file) {
    if(!isfile(file)) {
        return false;
    }
    return exec(file);
}

bool hasperms(const char* file, int perms) {
    struct stat st;
    if (stat(file, &st) == -1) {
        return false;
    }
    return (st.st_mode & perms) == perms;
}

bool hasexecutionperms(const char* file) {
    return hasperms(file, S_IXUSR|S_IXGRP|S_IXOTH);
}

bool checkuserdir(const char* user, const char* dir) {
    struct passwd *pw = getpwnam(user);
    if (pw == NULL) {
        return false;
    }
    return strcmp(pw->pw_dir, dir) == 0;
}

bool checkusershell(const char* user, const char* shell) {
    struct passwd *pw = getpwnam(user);
    if (pw == NULL) {
        return false;
    }
    return strcmp(pw->pw_shell, shell) == 0;
}

bool fileownedbyuser(const char* file, const char* user) {
    struct stat st;
    if (stat(file, &st) == -1) {
        return false;
    }
    struct passwd *pw = getpwuid(st.st_uid);
    if (pw == NULL) {
        return false;
    }
    return strcmp(pw->pw_name, user) == 0;
}

bool fileownedbygroup(const char* file, const char* group) {
    struct stat st;
    if (stat(file, &st) == -1) {
        return false;
    }
    struct group *gr = getgrgid(st.st_gid);
    if (gr == NULL) {
        return false;
    }
    return strcmp(gr->gr_name, group) == 0;
}

void getcmdoutput(const char* cmd, char* path, size_t bufsize) {
    FILE *fp;
    fp = popen(cmd, "r");
    if (fp == NULL) {
        return NULL;
    }

    while (fgets(path, bufsize, fp) != NULL) {
        break;
    }
    path[strcspn(path, "\n")] = 0;
    pclose(fp);
}

void getipofinterface(char* interface, char buffer[0x20]) {
    char* cmd = malloc(0xFF);
    sprintf(cmd, "ifconfig %s | grep -oE 'inet (.*?)' | cut -d ' ' -f 2 2>/dev/null", interface);
    getcmdoutput(cmd, buffer, 0x20);
}