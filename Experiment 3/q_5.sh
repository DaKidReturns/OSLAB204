#! /bin/bash

if [ ! $# -eq 2 ] ; then
    echo "Two arguments are needed"
else 
    if test $1 = $2  ; then
        echo "The strings are equal"
    else
        echo "The strings are not equal"
    fi
fi
