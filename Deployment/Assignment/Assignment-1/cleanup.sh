#!/bin/bash
source .common
check_docker

echo "[NOTE]: Only run this script when you've completed all the tasks as it will remove all the downloaded files and you'll have to download everything again..."

read -p "Are you sure you want to continue? [Y/N] " -n 1 -r REPLY

if [[ $REPLY != 'Y' ]] && [[ $REPLY != 'y' ]]; then
    echo -e "\n[!] Aborting..."
    exit 1
fi

echo -e "Removing all the downloaded images"
ids=$(get_image_id 'theflash2k\|cy243l\|recon')
docker rmi -f $ids

echo "[*] Done!"
