#!/bin/bash

## Author: @TheFlash2k

echo -e  "[\e[34m*\e[0m] Checking if docker is installed"
if ! command -v docker &> /dev/null; then
    echo -e "[\e[31m!\e[0m] Docker is not found on your system. Please install using 'sudo apt install docker.io docker-compose'"
    exit 1
fi

echo -e -n "[\e[32m+\e[0m] Found "
docker -v

echo -e  "[\e[34m*\e[0m] Checking if user is part of docker group"

getent group docker | grep $(whoami) &>/dev/null

if [ $? != 0 ]; then
    echo -e  "[\e[31m!\e[0m] User $(whoami) not part of docker group! Please add the user using 'usermod -aG docker $(whoami)' command and re-login."
    exit 1
fi

echo -e  "[\e[34m*\e[0m] Preparing the lab..."
docker build -t cy243l-lab1 ./data &>/dev/null
echo -e  "[\e[32m+\e[0m] Done!. Spawning an interactive shell into the lab environment"
docker run -it --rm --name "cy243l-lab1-instance" --hostname "lab1" "cy243l-lab1"