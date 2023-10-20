#!/bin/bash

source scripts/.common
LOCAL_PORT=80
EXPOSED=9512 # The port you want to access this on locally.

check_docker

get_image_id "theflash2k/cy243l-lfi-rce"

if [[ $? != 0 ]]; then
    echo "[*] Building the image..."
    docker build -t theflash2k/cy243l-lfi-rce .

    if [[ $? != 0 ]]; then
        echo "[ERROR] Failed to build the image"
        exit 1
    fi
fi

if check_if_running "lfi-rce"; then
    echo "[*] Starting lfi-rce"
    docker run --rm --name lfi-rce -d -p $EXPOSED:$LOCAL_PORT cy243-lfi-rce
else
    echo "[*] lfi-rce is already running"
fi
