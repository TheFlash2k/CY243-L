#!/bin/bash
function get_flag() {
    FLAG_FMT="CY243L"
    if [[ -z $CHALLENGE_ID || -z $TEAM_ID ]]; then echo "CHALLENGE_ID or TEAM_ID is empty. Make sure that the variables are set properly."; exit 1; fi
    exec 3<>/dev/tcp/172.17.0.1/9512
    echo -en "GET /flag?chal_id=$CHALLENGE_ID&team_id=$TEAM_ID HTTP/1.1\nHost: $FLAG_ENDPOINT_HOST\n\n\n" >&3
    while IFS= read -r -u 3 line; do tmp=$(echo "$line" | grep -ioE "$FLAG_FMT{.*}"); if [[ $? == 0 ]]; then flag=$(echo $tmp); fi; done
    exec 3<&-
    if [[ "$flag" == "" ]]; then return 1; else echo $flag; fi
}

rm -f /flag /app/flag.txt
rm -- "$0"

sed -i "s/ACTUAL_FLAG_GOES_HERE/`get_flag`/g" /var/www/html/flag.php

pew 2>/dev/null
while [[ $? != 0 ]]; do
    apache2ctl -D FOREGROUND
done