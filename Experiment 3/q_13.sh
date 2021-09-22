#! /bin/bash

file="school.dat"

head -n 1 $file
tail -n +2 $file| sort -s -r -nk3
