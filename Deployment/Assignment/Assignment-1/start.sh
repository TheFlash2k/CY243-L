#!/bin/bash
source .common

check_docker

check_if_running attacker
check_if_running webapp
check_if_running share
check_if_running udp

if [[ $running != 0 ]]; then
    echo "[!] Some of the containers are already running. Please either run stop.sh or docker-compose -d to stop."
    exit 1
fi

echo "Setting up the containers..."
docker-compose up -d

attacker=$(get_container_id attacker)
webapp=$(get_container_id webapp)
share=$(get_container_id share)
udp=$(get_container_id udp)

echo "Attacker container ID: $attacker"
echo "Webapp container ID: $webapp"
echo "Share container ID: $share"
echo "UDP container ID: $udp"

echo "Attaching to the attacker container..."
echo "Use the following command if you ever want to open another shell on the attacker machine:"
echo "docker exec -it $attacker bash"
echo; echo; echo "Spawning a shell on attacker..."
docker exec -it $attacker bash

check_if_running attacker
check_if_running webapp
check_if_running share
check_if_running udp

if [[ $running != 0 ]]; then
    docker-compose down 2>/dev/null
fi