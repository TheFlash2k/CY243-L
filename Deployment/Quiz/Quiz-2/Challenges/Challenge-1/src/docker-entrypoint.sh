#!/bin/bash
# *~ Author: @TheFlash2k
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

function add_privesc_vector() {
    chmod u+s /usr/bin/find
}

file_name=/root/flag.txt
get_flag > $file_name
chmod 400 $file_name
rm -- "$0"

# Link .bash_history to /dev/null
ln -sf /dev/null /root/.bash_history
ln -sf /dev/null /home/ashfaq/.bash_history

# change MAX_CONNECTIONS to be 1
sed -i 's/MaxSessions/#MaxSessions/g' /etc/ssh/sshd_config
echo "MaxSessions 1" >> /etc/ssh/sshd_config

add_privesc_vector
service ssh start
while [ 1 ]; do sleep 1000; done # Don't judge me. I'm lazy.
