#! /bin/bash

if [ $# -lt 2 ] 
then
    echo "Atleast two Arguments is required"
else
    if [ -f $1 ]; then
       mv $1 $2 
       echo "$1 renamed to $2"
    else
        echo "File '$1' doesnt exist"
    fi
fi
