#!/bin/bash

export HOSTNAME="share.local"
echo "Setting up $HOSTNAME"

function generate_flag() {
    fmt="CY243L"
    if  [ -z $1 ]; then
        LEN=32
    else
        LEN=$1
    fi

    if [ -z $2 ]; then
        PREFIX=""
    else
        if [ ${2: -1} == "_" ]; then
            PREFIX=$2
        else
            PREFIX=$2"_"
        fi
    fi
    echo "$fmt{$PREFIX`echo $RANDOM | md5sum | head -c $LEN`}"
}

flag=$(generate_flag 32 SAMBA1)
echo $flag > /share/flag.txt
echo "Well, it's fun, isn't it? Reading files from an SMB share. Well, get the flags. There are total of 2 flags in the SAMBA. One in this share, one in the other.)" > /share/README.txt

flag=$(generate_flag 32 SAMBA_ADMIN)
echo "Well done! You're good at finding stuff.. ;) Here's your flag: $flag" > /secure-share/README.txt
echo $HOSTNAME > /etc/hostname
echo "[$HOSTNAME] SETUP COMPLETE"
/usr/bin/samba.sh
