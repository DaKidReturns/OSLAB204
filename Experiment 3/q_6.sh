#! /bin/bash

if [ $# -eq 0 ] 
then
    echo "Atleast one Argument is required"
else
    if [ -f $1 ]; then
        echo "File ${1} Exists"
    else
        echo "File doesnt exist"
    fi
fi
