#! /bin/bash

echo -ne "Enter your name: "
read -r l
echo -ne "Name reversed: "
echo -e $l | rev
echo -ne "Number of Charecters: "
echo -e $l | wc -m
