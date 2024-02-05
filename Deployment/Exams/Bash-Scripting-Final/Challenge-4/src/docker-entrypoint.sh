#!/bin/bash

loremipsum () {
    if [ "${1}" = "" ] || [ "${2}" = "" ]; then
        echo "Usage: loremipsum [paragraphs, sentences] [integer]"
    else
        _s -s http://metaphorpsum.com/"${1}"/"${2}"
    fi
}

loremipsum paragraphs 50 > /opt/random-data.txt

rm -- "$0"
echo -e "CHAL_ID=$CHALLENGE_ID\nTEAM_ID=$TEAM_ID" >> /etc/environment
service ssh start
while [ 1 ]; do sleep 1000; done # Don't judge me. I'm lazy.
