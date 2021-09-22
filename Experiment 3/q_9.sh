#! /bin/bash

if [ $# -lt 3 ]
then 
    echo "Enter three file names"
else
    head $1 > $3
    head $2 >> $3
fi
