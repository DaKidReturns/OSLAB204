#! /bin/bash

echo "----Day Of The Week----"

let RUN=true
while [ $RUN ]
do 
    echo -n "Enter a number between 1 and 7: "
    read -r n

    case $n in
        1)
            echo "Day is Monday";;
        2)
            echo "Day is Tuesday";;
        3)
            echo "Day is Wednesday";;
        4)
            echo "Day is Thursday";;
        5)
            echo "Day is Friday";;
        6)
            echo "Day is Saturday";;
        7)
            echo "Day is Sunday";;
        *)
            echo "Error: Enter a proper input" 1>&2
    esac

    echo -ne "Do you want to continue? (n to exit)"
    read ch
    if [ "$ch" = "n" ] || [ "$ch" = "N" ]; then
        exit 0
    fi
    echo ""

done
