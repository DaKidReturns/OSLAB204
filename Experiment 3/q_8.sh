#! /bin/bash

if [ $# -lt 2 ] 
then
    echo "At least two arguments required"
    echo "$0 file1 file2"
else
    if [ -f $2 ]; then
       cat $1 >> $2 
    else
       cat $1 > $2 
    fi
fi
