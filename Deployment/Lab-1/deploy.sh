#!/bin/bash

## Author: @TheFlash2k

echo "[+] Checking if docker is installed"
if ! command -v docker &> /dev/null; then
    echo "[!] Docker is not found on your system. Please install using 'sudo apt install docker.io docker-compose'"
    exit 1
fi

echo -n "[*] Found "
docker -v

echo "[+] Checking if user is part of docker group"

getent group docker | grep $(whoami) 2>/dev/null

if [[ $? != 0 ]]; then
    echo "[*] User $(whoami) not part of docker group! Please add the user using 'usermod -aG docker $(whoami)' command and re-login."
    exit 1
fi

echo "[*] Preparing the lab..."
docker build -t cy243l-lab1 ./data &>/dev/null
echo "[+] Done!. Spawning an interactive shell into the lab environment"
docker run -it --rm --name "cy243l-lab1-instance" --hostname 'lab1' cy243l-lab1