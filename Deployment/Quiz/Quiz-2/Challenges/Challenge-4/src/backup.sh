#!/bin/bash

BACKUPTIME=`date +%b-%d-%y`
DESTINATION=/var/backups/$BACKUPTIME
SOURCEFOLDER=/etc/ssh/sshd_config

mkdir -p $DESTINATION
tar -cpzf $DESTINATION/$BACKUPTIME-bkup.tar.gz $SOURCEFOLDER