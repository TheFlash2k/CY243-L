#!/bin/bash

rm -- "$0"

echo -e "CHAL_ID=$CHALLENGE_ID\nTEAM_ID=$TEAM_ID" >> /etc/environment
service ssh start
while [ 1 ]; do sleep 1000; done # Don't judge me. I'm lazy.
