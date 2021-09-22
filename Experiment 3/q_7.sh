#! /bin/bash

if [ $# -lt 2 ]
then
    echo "Atleast two Argument is required"
    echo "./q_7.sh [file] [string to be searched]"
else
    if [ -f $1 ]; then
        found=$(grep $2 $1)
        if [ -n "$found" ]
        then
           echo "The string $2 exists in the file" 
       else
           echo "The string $2 is not in the file"
        fi
    else
        echo "File doesnt exist"
    fi
fi
