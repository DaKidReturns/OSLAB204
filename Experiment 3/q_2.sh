#! /bin/bash

echo -n "Enter number 1: "
read a
echo -n "Enter number 2: "
read b
let "c = $a+$b"
echo "Sum = $c"
