#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'
tests=0
t_tests=7

function passed () { printf "${GREEN}PASSED${NC} - "; ((tests++)); }
function failed () { printf "${RED}FAILED${NC} - "; }

username="kali-auto-user"
grpname="kali-auto-group"

user="$(getent passwd $username)"
grp="$(getent group $grpname)"

if [[ $user == "" ]]; then failed; else passed; fi
echo "User $username created"

if [[ $grp == "" ]]; then failed; else passed; fi
echo "Group $grpname created"

# -d can be used but case-insesitive checking?
shopt -s nocaseglob
_dir=`ls -l *cy243-l* &>/dev/null`
_res_dir="$?"
_dir_git=`ls -l *cy243-l/.git* &>/dev/null`
_res_dir_git="$?"
shopt -u nocaseglob
if [ $_res_dir != 0 ] || [ $_res_dir_git != 0 ]; then failed; else passed; fi
echo "CY243-L Repository cloned locally"

if [ -d /tmp/test-2* ] && [ -f /tmp/test-2*/test2.txt ]; then
    (cat /tmp/test-2*/test2.txt | grep 'This file is created by') &>/dev/null
    if [[ $? != 0 ]]; then failed; else passed; fi
else
    failed
fi
echo "Checking /tmp/test-<roll-number> and test2.txt inside the folder and checking the file contents."

folder_owner=`stat -c %U /tmp/test-2* 2>/dev/null`
file_group=`stat -c %G /tmp/test-2*/test2.txt 2>/dev/null`

if [[ $folder_owner != $username ]]; then failed; else passed; fi
echo -n "Checking if $username is owner of /tmp/test-<roll-number>"
if [ -d /tmp/test-2* ]; then echo " [Actual owner: $folder_owner]"; else echo; fi

if [[ $file_group != $grpname ]]; then failed; else passed; fi
echo -n "Checking if $grpname is group-owner of /tmp/test-<roll-number>/test2.txt"
if [ -f /tmp/test-2*/test2.txt ]; then echo " [Actual group: $file_group]"; else echo; fi

perms=`stat -c %A /tmp/test-2*/test2.txt 2>/dev/null`

if [[ $perms != "-rwxr-x---" ]]; then failed; else passed; fi
echo -n "Checking the permissions on the file (if they match the criteria defined in the task.)"
if [ -f /tmp/test-2*/test2.txt ]; then echo " [Actual Permissions: $perms]"; else echo; fi

if [[ tests -ne t_tests ]]; then
    exit 1
fi

printf "\n${GREEN}Done!${NC} - All the tasks have been completed!\n"
