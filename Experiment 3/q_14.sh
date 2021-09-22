#! /bin/bash

echo -n "Enter a number: "
read -r n

#let s="n*(n+1)/2"
let s=0
let i=0

while [ $i -le $n ]
do 
    let "s=$s+$i"
    let "i=$i+1"
done

echo "Sum of numbers from 0 to ${n} : ${s}"
