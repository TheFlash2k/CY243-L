#!/bin/bash

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

flag=$(generate_flag 32 SETUP)
echo "Well done! You've done the setup correctly. Here's your flag: $flag" > /home/kali/flag.txt

echo -e "HOSTS INFORMATION:"                     >> /home/kali/hosts.txt
echo -e "10.10.18.21 - attacker        - kali"   >> /home/kali/hosts.txt
echo -e "10.10.18.17 - webapp.local    - webapp" >> /home/kali/hosts.txt
echo -e "10.10.18.95 - share.local     - share"  >> /home/kali/hosts.txt
echo -e "10.10.18.47 - udp.local       - udp"    >> /home/kali/hosts.txt

echo "[*] Successfully setup the attacker machine..."
while true; do sleep 10000; done