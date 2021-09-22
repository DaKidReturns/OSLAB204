#! /bin/bash

if [ $# -lt 1 ]; then 
    echo "Pass two file names as command line argument"
else
    read -r l < $1
    echo $l | tr "aeiou" "AEIOU" > $2
fi
