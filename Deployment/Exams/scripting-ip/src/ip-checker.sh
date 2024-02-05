#!/bin/bash

ifconfig "$1" | grep -oE 'inet (.*?)' | cut -d ' ' -f 2