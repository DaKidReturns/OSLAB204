#! /bin/bash

echo -n "Enter a Charecter: "
read -r ch

if [ -z "$ch" ]; then
    echo "Enter a vaild charecter"
else
    #ls --file-type $ch | grep -iE "[^@|^/]$" | wc -l 
    echo -ne "Number of files starting with '$ch': "
    ls -dF ${ch}* 2>/dev/null | grep -E '[^@|^/]$' | wc -l
fi
