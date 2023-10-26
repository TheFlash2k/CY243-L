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

flag_digit=$(printf "%03d\n" $((RANDOM%1000)))
file="flag-$flag_digit.txt"
path_to_store_to="$BASE_DIR/musicnews"
echo $flag > $path_to_store_to/$file

PORT=80
sed -i "s/80/$PORT/g" /etc/apache2/ports.conf
echo "webapp.local" > /etc/hostname
echo "[WEBAPP.LOCAL] SETUP COMPLETE"

pew 2>/dev/null
while [[ $? != 0 ]]; do
    apache2ctl -D FOREGROUND
done
